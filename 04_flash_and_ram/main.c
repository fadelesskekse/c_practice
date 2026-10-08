// FLASH
// ────────────────────────────
// .text       machine instructions
// .rodata     read-only constants
//             initial image for .data

// RAM
// ────────────────────────────
// .data       initialized writable globals/statics
// .bss        zero-initialized globals/statics

// heap        dynamic allocation, if used

//         free RAM

// stack       local variables, function state, etc.
// ────────────────────────────

//Storage duration and mutability strongly dictate where the objects live 

// uint32_t a = 10; // .data
// uint32_t b; //.bss

// const uint32_t c = 20; //.rodata or flash 

// void foo(void)
// {
//     uint32_t d = 30; // stack or cpu register 
//     static uint32_t e = 40; // .data 
// }


//.text: contains mostly your machine instructions
// 
// 
// static const uint32_t gains[3] =
// {
    // 10,
    // 20,
    // 30
// };
// 
// or the string in:
// 
// printf("Controller started\n");  //consts generally live in .rodata or flash
// same with this sort of string that doesn't change 

//A lot of the times, machien instructions and .rodata is in flash

// uint32_t gain = 25;

//most likely in .data as it needs to be writable at runtime, and most likely in flash.

//the initial value though is in flash
//at the beginning of runtime, startup code will copy that data from flash into its proper ram locations 

//uint32_t count; //0 initialized, C guarantees this will be 0
    // in .bss 
    //but it would be wasteful to store 0's in flash, so it doesn't 
    //the firmware basically says, these regions of ram will be zeroed at startup 

   // uint8_t buffer[10000]; //at file scope 

   //WE wont store 10000bytes of 0's in flash 


// void calculate(void)
// {
//     uint32_t x = 10; // often live on the stack , though the compiler might keep them in cpu registers 
//     uint32_t y = 20;
//     uint32_t result = x + y;
// }

// void foo(void)
// {
//     static uint32_t x = 0; //in .bss as its not just local variables anymore and its initialized to 0 
// }

#include <stdio.h>
#include <stdint.h>

uint32_t initialized_global = 10;
uint32_t uninitialized_global;

static uint32_t initialized_static = 20;
static uint32_t uninitialized_static;

static const uint32_t constant_data = 30;

void test(void)
{
    uint32_t local = 40;
    static uint32_t static_local = 50;

    printf("local = %u\n", local);
    printf("static_local = %u\n", static_local);
}

int main(void)
{
    test();

    return 0;
}

//size main
//nm -S main | less

//D - .data (for initalized data with external linkage
//B - .bss  (for uninitialized data with external linkage)
//d - .data (for initalized private data)
//b - .bss (for uninitializede private data )


//What happens before main()?

// for cortex-m mcu like my stm32G474:

// Reset / power-up
//       ↓
// CPU reads vector table
//       ↓
// initial stack pointer loaded
//       ↓
// Reset_Handler begins executing
//       ↓
// .data copied from flash → RAM
//       ↓
// .bss zeroed in RAM
//       ↓
// system/runtime initialization
//       ↓
// main()

// vector table
// 
// entry 0  → initial stack pointer value
// entry 1  → address of Reset_Handler
// entry 2  → NMI handler
// entry 3  → HardFault handler
// ...
        //   interrupt handlers

//Cortex-M firmware images contain a vector table near the beginning of the program image

// Upon reset,  the processor gets 2 pieces of information:
    //Where does my stack start
    //what is my first instruction address i should execute 


// after reset_handler,
// we copy the .data initialization values from flash to ram,
//and we set the values at the .bss unitialized variables to 0 in ram
// Somehow, the startup code knows where to end the .data and .bss initalization in ram, so it knows the boundaries 

//the linker script comes into play here 

// _sdata  = start address of .data in RAM -> linker script stuff
// _edata  = end address of .data in RAM

// _sbss   = start address of .bss in RAM
// _ebss   = end address of .bss in RAM

//the linker script determines where these memory regions reside 

//_sidata you might see this in the linker script which gives the address in flash for the initialization values that will go at the _sdata, _edata, etc 

//takeaway is that the startupcode and the linker script use eachother during startup 

//SystemInit(); you might see this at system initialization, or __libc_init_array();

// depending on the toolchain or project
//responsible for processor/system setup and C/C++ runtime initialization 
//main only runs after C-runtime has been established
//what is runtime? I though thtis was just generally when the program is running? 
//but is it literally something concrete ethat gets started? 

// It just means: Execute the startup machinery such that we can run C code and it behaves like C code

// Suppose someday your board:
// - powers up,
// - debugger connects,
// - but never reaches main().
// A desktop-programming mindset might say:
// "Something is wrong in main()."

// But an embedded engineer asks:
// Did the processor reach Reset_Handler?

// Is the stack pointer valid?

// Is the vector table correct?

// Did startup fault while copying .data?

// Is .bss being cleared correctly?

// Is clock initialization hanging?

// Did a fault occur before main()?

// That's why we're learning this.

// //once my stm32 arrives, you might see: 
// startup_stm32g474xx.s -> vector table and reset/startup code
// STM32G474RETX_FLASH.ld -> linker memory layout, where the .data and .bss (etc) will go in ram, wher eon flash is the actual init data for .data 
// system_stm32g4xx.c -> MCU/System setup  (largely a black box for now     )
// main.c

//Moving onto stack and object lifetime:

// void foo(void)
// {
//     uint32_t a = 10;
//     uint32_t b = 20;
// }

//exist only during this execution of th efunciton 
//often stored in the functions stack frame, although the compiler may keep them in cpu registers instead 

// main()
//   |
//   | calls foo()
//   v

// STACK

// higher addresses
// ┌───────────────────┐
// │ main's state      │
// ├───────────────────┤
// │ foo's saved state │
// │ foo's locals      │
// └───────────────────┘
// lower addresses

//after foo returns, the stack frame is no longer needed 

// uint32_t *bad(void)
// {
//     uint32_t x = 123;

//     return &x;
// }

//Whil this funciton is executing, we can see the address x is temporarily stored at, and if we access that address outside of this 
//function, call, it might still point to the location that x was at. 

//however, there might be something else in that address location at that point t

// uint32_t *less_bad_example(void)
// {
//     static uint32_t x = 123;

//     return &x;
// }

//now x is permannetly being stored at that address.

//this might cause concurrecy or reentrancy issues if multiple threads try to derefernce and assign a value to x at the same time