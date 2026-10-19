
// //ISR: interrupt service routine: interrupts\

// //event occurs
// // CPU stops normal execution
// //we jump to interrupt handler
// // handler runs
// // CPU restores previous state
// //main continues on 


// // void TIM2_IRQHandler(void)
// // {
// //     // handle timer event
// // }

// //on stm32, the function name depends on which interrupt source you are using? 

// //interrupts can happen at any time: 


// // shared_value |= mask; It can happen right in the middle of a register write, which can cause issues 

// //when an intterupt is accepted, the CPU saves enough of the current execution state such that it can go back to it after the interrupt is done 
// //some architextures push a "stack frame


// //it then gets the ISr address from the interrupt/vector machinery and executres the handler 

// //this creates concurrency with just one core 

// //keep isr's bare bones as it can slow down other lower priority processes 

// // void TIM_IRQHandler(void)
// // {
// //     clear_timer_flag();
// //     control_tick = 1;
// // }


// // if (control_tick)
// // {
// //     control_tick = 0;
// //     run_controller();
// // } // and normal code runs the heavier work 


// // void TIM_IRQHandler(void)
// // {
// //     read_adc();
// //     run_controller();
// //     update_pwm();
// // }

// //sometimes the control loop is within the entire ISR
// // You just need to make sure the WCET of ISR << control period 

// //WCET: Worst case execution time


// //note an interrupt event time doesn't equal the isr start time in general, the CPU can be doing many things that cause a delay:

// // finishing current instruction 
// //a higher priority isr is already running
// // memory & bus effects

// //this variation is what causes jitter

// //interrupt priorities: 

// // Timer ISR      priority high
// // UART ISR       priority low

// // UART ISR running
// //       ↓
// // timer interrupt
// //       ↓
// // UART paused
// //       ↓
// // Timer ISR runs
// //       ↓
// // Timer ISR returns
// //       ↓
// // UART resumes

// // This is called nested interrupt handling.
// // Now stack usage increases because one interrupt context exists on top of another.

// //suppose:

// volatile uint32_t control_tick = 0;

// void TIM_IRQHandler(void)
// {
//     control_tick = 1;
// }



// while (1)
// {
//     if (control_tick)
//     {
//         control_tick = 0;
//         run_controller();
//     }
// }

// //we need volatile here because it can change in our handler, not just main. \
// //without volatile, the compiler, depending on the optimization level, can reason that maybe the if statement is not necessary
// //since nothing outside of it changes control_tick

// //Note that although volatile enforces a re-reading of a variable, it does not make it "atomic" in the sense that you
// //can still have overridding of variables in multi step operations like |=


//Module 6B — Shared state between main() and an ISR

//What does atomic mean? 

//It means the ISR would either see before the multistage instruction, or after it, not between 

//My STM32G474 uses a Cortex-M4

// For a normal alligned 32bit load or store, it is normally done as a single native access

//Ex:

// volatile uint32_t sensor_value;

// sensor_value = new_value;

// is very different than sensor_value++;

//not a single native access 

/////////

volatile uint32_t adc_result;

void ADC_IRQHandler(void)
{
    adc_result = ADC_VALUE;
}

uint32_t value = adc_result;

//See how we have 2 separate single instructions, a read and a write, not a combined one./

//these sort of operations are straightforward on our architexture 


volatile uint64_t timestamp;

//consider this, our COrtex M4 is a 32 bit machine 

//A 64 bit value is handled in 2 separate pieces, the upper 32 bits and lower 32 bits 

//so you could have a scenario where main reads teh first 32, the interrupt overrides all 64, then in main it patches the new last 32 with the old first 32

//This is called a torn read 


///////////ISR Design and Timing///////////////// 


timer period      = time between hardware events
interrupt latency = event → ISR starts
ISR execution     = ISR starts → ISR ends

//suppose we have an event, but there is latency + the execution time we have to go through 

//Say the execution time takes 25 microseconds, and the latency was 9 micro 

//Jitter: Say the latency can range anywhere from 4u-8u 

//for control this could matter because theory says we execute every T, but with jitter we have T + deltaT, which is 
//variable 

//can matter for high bandwidth or tightly timed systems 

//we can measure timing of an ISR via:

void TIM_IRQHandler(void)
{
    GPIO_SET();

    // ISR work here

    GPIO_CLEAR();
}

//and time that GPIO set/clear on my oscillioscope 

//you can also do something similar for measuring jitter or latency 

// Critical Sections:

// volatile uint32_t shared;

//Suppose main and our ISR share this variable.

//and main needs to perform a read-write safely:

// disable_interrupts();

// shared |= mask;

// enable_interrupts();

//So critical section legnths need to be taken into account to get WCET 

//practical ISR and shared data patterns:

//SIMPLE EVENT FLAG
// volatile uint32_t data_ready = 0;

// void ADC_IRQHandler(void)
// {
//     data_ready = 1;
// }

// int main(void)
// {
//     while (1)
//     {
//         if (data_ready)
//         {
//             data_ready = 0;
//             process_data();
//         }
//     }
// }

//SINGLE WRITER OWNERSHIP 
//ISR owns teh writing
//Main owns the reading



//Note that for multiple related values, several atomic reads/writes does not produce an atomic read/write of all the data
// Say for example you have a state that is position and velocity.

//Even if you have 2 atomic readings of posittion and veloicty, an ISR coudl still interrupt and you end up with 
//new position and old velocity 

//For this you might need a small critical section or "double buffering"