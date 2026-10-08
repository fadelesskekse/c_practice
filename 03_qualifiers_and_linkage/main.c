
// // // volatile tells the compiler that a value may change for reasons the 
// // // compiler cannot see, so accesses to that object must actually occur.


// // // uint32_t status = 0;

// // // while (status == 0)
// // // {
// // // }

// // //We initialize status as 0, and ntohing in side the loop changes status, so the compiler might think
// // //this look will never end
// // //it also might not need to reload the value of status every loop iteration 

// // //but what if it is a hardware register, and hardware changes it from 0->1

// // //volatile uint32_t status = 0;

// // //volatile says access the value of this variable everytime, as something outside of the code might be changing it 

// // //THIS IS WHY ALL STATUS REGISTERS ARE VOLATILE 
// // #include <stdint.h>
// // #include <stdio.h>

// // typedef struct
// // {
// //     volatile uint32_t CONTROL;
// //     volatile uint32_t STATUS;
// //     volatile uint32_t DATA;
// // } Peripheral_TypeDef;

// // //then make a pointer: 

// // Peripheral_TypeDef *ptr = (Peripheral_TypeDef *)0x40020000;

// // //And ptr->CONTROL would be a volatile access 

// // // while ((PERIPH->STATUS & READY_BIT) == 0u) //Could change outside fo code 
// // // {
// // // }

// // // uint32_t *reg = (uint32_t *)0x40020000;

// // // *reg = 1;
// // // *reg = 2;
// // // *reg = 3;

// // //We are dereferencing and writing to the value at reg 

// // //The compiler might think, nothing uses the *reg=1 and *reg=2, only the last one, so it might optimize that code away 

// // //but what if that address is a hardware command register:

// // // write 1 → reset peripheral
// // // write 2 → configure peripheral
// // // write 3 → start peripheral

// // //so declare this reg volatile

// // // volatile uint32_t *reg = (volatile uint32_t *)0x40020000;

// // //The above means reg is a ptr to a volatile uint32.

// // uint32_t * volatile reg;

// // //the above means the reg ptr itself is volatile, and is pointing to a uint32_t.
// // //This implies that the address the ptr is pointing to might be changing outside of the c code 

// // //Note:

// // //If we do volatile uint32_t test;

// // //test++

// // //That test++ may not be a single instruction, and might be split up into several:
// // //Read the value because something else may have changed it
// // //increment
// // //then write the value

// // // In between these instructions, an interrupt could occur 


// #include <stdint.h>

// uint32_t normal_value;
// volatile uint32_t volatile_value;

// void test_normal(void)
// {
//     normal_value = 1;
//     normal_value = 2;
//     normal_value = 3;
// }

// void test_volatile(void)
// {
//     volatile_value = 1;
//     volatile_value = 2;
//     volatile_value = 3;
// }

// int main(void)
// {
//     test_normal();
//     test_volatile();

//     return 0;
// }
// //to compile with optimization gcc -std=c17 -O2 -S main.c -o main.s

//const: 

//const means the code is not allowed to modify this object "through this name or reference"

//often end up in flash memory 

//So it might be an issue if you use const that accessing flash memory adds latency but conserves ram space
// stm mentions that flash access at high CPU frequency requires latency settings, and the one I bought has an ART
//accelerator with "prefetch" and "branch cache" to reduce performance penalties, and can operate like zero-wait execution in bench
//mark conditions up to 170 MHz 

//common use case: A lookup table 

// const uint16_t calibration_table[4] =
// {
//     100,
//     203,
//     307,
//     415
// };

//const uint32_t *p; //a ptr to a const uint32_t

// uint32_t a = 10;
// uint32_t b = 20;

// const uint32_t *p = &a;

// p = &b;      // just cause p is pointing to a const uint32 doesn't mean you can't change which const uint32 it is
//pointing to

//still can't modify the values through p though: *p = 30 <- not allowed 

//The followign is very common in funciton api's:

// void process_samples(const uint16_t *samples, uint32_t count);


// uint32_t * const p = &a;

//A const ptr to a uint32. the uint_32 can change, the ptr has to stay looking at the same address though


// const volatile uint32_t STATUS;

//Make something const volatile if the value might change from something outside of software, and you don't
//want software to change that value 

#include <stdint.h>

int main(void)
{
    uint32_t a = 10;
    uint32_t b = 20;

    const uint32_t *p1 = &a;
    uint32_t * const p2 = &a;
    const uint32_t * const p3 = &a;

    //*p1 = 30;// will through an error since p1 is saying its pointing to a const uint32, even if a is not a const
    // p1 = &b; //should work fine since p1 is not a const ptr

   //  *p2 = 30; // should be fine since p2 is not claming to point to sa const uint
  //  p2 = &b; //will cause an error since its a const ptr, and we cant change where its pointing to 

    // *p3 = 30;
    // p3 = &b;

    return 0;
}