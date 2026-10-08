// // // // // #include <stdio.h>
// // // // // #include <stdint.h>

// // // // // int main(void)
// // // // // {
// // // // //     uint32_t x = 42;

// // // // //     printf("x value   = %u\n", x);
// // // // //     printf("x address = %p\n", (void *)&x);

// // // // //     uint32_t *ptr = &x;

// // // // //     printf("ptr = %p\n",ptr);
// // // // //     printf("val at ptr = %u\n",*ptr);
// // // // //     return 0;
// // // // // }
// // // // // //*ptr we are declaring a pointer named ptr with *

// // // // #include <stdio.h>
// // // // #include <stdint.h>

// // // // int main(void)
// // // // {
// // // //     uint32_t x = 42;

// // // //     uint32_t *ptr = &x;

// // // //     printf("x       = %u\n", x);
// // // //     printf("&x      = %p\n", (void *)&x);
// // // //     printf("ptr     = %p\n", (void *)ptr); //(void *) is a generic object ptr, and is what %p needs
// // // //     printf("*ptr    = %u\n", *ptr);

// // // //     *ptr = 100;
// // // //     printf("x = %u\n",x);

// // // //     return 0;
// // // // }

// // // // //Note. &x is an address in my machines virtual address space, not an actual address on ram
// // // // // but on embedded, mcus are much simpler 
// // // // //you mmight see:

// // // // //Peripheral register X is located at address 0x40020000.

// // // // //uint32_t *reg = (uint32_t *)0x40020000; //casting a hex value to a uint32_t ptr

// // // // //*reg = 100 //writes to that register

// // // // // We specify the data type at the ptr for the compiler as the compiler needs to know what data type lives at that address.

// // // // //Example: If we specify uint32_t *ptr = (uint32_t *)0x0F, the compiler knows the value 0x0F is represented as a 32 bit value at that register

// // // #include <stdio.h>
// // // #include <stdint.h>

// // // int main(void)
// // // {
// // //     uint32_t x = 0x12345678;

// // //     uint32_t *ptr = &x;

// // //     printf("x     = 0x%08X\n", x);
// // //     printf("&x    = %p\n", (void *)&x);
// // //     printf("ptr   = %p\n", (void *)ptr);
// // //     printf("*ptr  = 0x%08X\n", *ptr);

// // //     *ptr = 0xABCDEF01;

// // //     printf("\nafter *ptr = 0xABCDEF01:\n");
// // //     printf("x     = 0x%08X\n", x);
// // //     printf("*ptr  = 0x%08X\n", *ptr);

// // //     return 0;
// // // }

// // // // uint32_t values[4] = {10, 20, 30, 40};

// // // // uint32_t *ptr = values;

// // #include <stdio.h>
// // #include <stdint.h>

// // int main(void)
// // {
// //     uint32_t values[4] = {10, 20, 30, 40};

// //     uint32_t *ptr = values;

// //     printf("ptr value at initial location = %u\n",*(ptr+1));
// // }

// // // ptr + 0 = 0x1000
// // // ptr + 1 = 0x1004
// // // ptr + 2 = 0x1008
// // // ptr + 3 = 0x100C
// // //ptr + 4 = 0x1010

// #include <stdio.h>
// #include <stdint.h>

// int main(void)
// {
//     uint8_t values[4] = {10, 20, 30, 40};

//     uint8_t *ptr = values;

//     for (int i = 0; i < 4; i++)
//     {
//         printf("ptr + %d = %p, value = %u\n", //%d for signed decimal, %p for an address, %u for unsigned decimal
//                i,
//                (void *)(ptr + i),
//                *(ptr + i));
//     }

//     return 0;
// }

// typedef struct
// {
//     uint32_t control;
//     uint32_t status;
//     uint32_t data;
// } Peripheral;

//Thiss is how you make a struct
//  Peripheral p;
//  p.control

//this is how you access elements within that struct 

//Peripheral *ptr = &p;
// (*ptr).control

// // ptr to the struct p

// (*ptr) deferences the ptr, so we can access the control element
//ptr->control equivalent way to access members of a struct whom we have a pointer pointing to 

// #include <stdio.h>
// #include <stdint.h>

// typedef struct
// {
//     uint32_t control;
//     uint32_t status;
//     uint32_t data;
// } Peripheral;

// int main(void)
// {
//     Peripheral p = {0};

//     Peripheral *ptr = &p;

//     ptr->control = 0x11;
//     ptr->status  = 0x22; //writing to these address via the pointer 
//     ptr->data    = 0x33;

//     printf("control = 0x%08X\n", p.control);
//     printf("status  = 0x%08X\n", p.status); //accessing these elements with the actual struct 
//     printf("data    = 0x%08X\n", p.data);

//     return 0;
// }

// // Peripheral base address = 0x40020000

// // offset 0x00: CONTROL
// // offset 0x04: STATUS
// // offset 0x08: DATA

// //suppose a fictional mcu states this. we have a struct at the base address, where we have 4 byte sequential chunks
// typedef struct
// {
//     uint32_t CONTROL;   // offset 0x00
//     uint32_t STATUS;    // offset 0x04
//     uint32_t DATA;      // offset 0x08
// } Peripheral_TypeDef;


// int main(void){

//     Peripheral_TypeDef *PERIPH =
//     (Peripheral_TypeDef *)0x40020000;

//     //PERIPH->CONTROL accesses the value for that element in that struct

//     return 0;
// }

// #define GPIOA_BASE 0x48000000UL
// #define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)

//the second preprocessor define statement defines a GPIOA as a pointer that is pointing to a segment of memory where a GPIO
//TypeDEf is stored, and the start of this location is GPIOA_BASE

//Say you want to use ptr+1, and ptr is pointing to the Peripheral_TypeDef. 
// If you do ptr+1, it doesn't move to the next elmeent in Peripheral Type def, it would move to the end of the type def, and into another
//peripheral typedef is tehre was one 
#include <stdint.h>
#include <stdio.h>

    typedef struct
{
    uint8_t  A;
    uint32_t B;
} Example;


int main(void){

    printf("%zu\n", sizeof(Example));//the compiler will add padding such that we have 3 extra 1 byte pads between 
    //the 8bit and 32 bit variables, and we end up with 8 total bytes 

    return 0;
}