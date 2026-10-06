// // // // #include <stdio.h>
// // // // #include <stdint.h>

// // // // int main(void)
// // // // {
// // // //     uint32_t x = 42;

// // // //     printf("x value   = %u\n", x);
// // // //     printf("x address = %p\n", (void *)&x);

// // // //     uint32_t *ptr = &x;

// // // //     printf("ptr = %p\n",ptr);
// // // //     printf("val at ptr = %u\n",*ptr);
// // // //     return 0;
// // // // }
// // // // //*ptr we are declaring a pointer named ptr with *

// // // #include <stdio.h>
// // // #include <stdint.h>

// // // int main(void)
// // // {
// // //     uint32_t x = 42;

// // //     uint32_t *ptr = &x;

// // //     printf("x       = %u\n", x);
// // //     printf("&x      = %p\n", (void *)&x);
// // //     printf("ptr     = %p\n", (void *)ptr); //(void *) is a generic object ptr, and is what %p needs
// // //     printf("*ptr    = %u\n", *ptr);

// // //     *ptr = 100;
// // //     printf("x = %u\n",x);

// // //     return 0;
// // // }

// // // //Note. &x is an address in my machines virtual address space, not an actual address on ram
// // // // but on embedded, mcus are much simpler 
// // // //you mmight see:

// // // //Peripheral register X is located at address 0x40020000.

// // // //uint32_t *reg = (uint32_t *)0x40020000; //casting a hex value to a uint32_t ptr

// // // //*reg = 100 //writes to that register

// // // // We specify the data type at the ptr for the compiler as the compiler needs to know what data type lives at that address.

// // // //Example: If we specify uint32_t *ptr = (uint32_t *)0x0F, the compiler knows the value 0x0F is represented as a 32 bit value at that register

// // #include <stdio.h>
// // #include <stdint.h>

// // int main(void)
// // {
// //     uint32_t x = 0x12345678;

// //     uint32_t *ptr = &x;

// //     printf("x     = 0x%08X\n", x);
// //     printf("&x    = %p\n", (void *)&x);
// //     printf("ptr   = %p\n", (void *)ptr);
// //     printf("*ptr  = 0x%08X\n", *ptr);

// //     *ptr = 0xABCDEF01;

// //     printf("\nafter *ptr = 0xABCDEF01:\n");
// //     printf("x     = 0x%08X\n", x);
// //     printf("*ptr  = 0x%08X\n", *ptr);

// //     return 0;
// // }

// // // uint32_t values[4] = {10, 20, 30, 40};

// // // uint32_t *ptr = values;

// #include <stdio.h>
// #include <stdint.h>

// int main(void)
// {
//     uint32_t values[4] = {10, 20, 30, 40};

//     uint32_t *ptr = values;

//     printf("ptr value at initial location = %u\n",*(ptr+1));
// }

// // ptr + 0 = 0x1000
// // ptr + 1 = 0x1004
// // ptr + 2 = 0x1008
// // ptr + 3 = 0x100C
// //ptr + 4 = 0x1010

#include <stdio.h>
#include <stdint.h>

int main(void)
{
    uint8_t values[4] = {10, 20, 30, 40};

    uint8_t *ptr = values;

    for (int i = 0; i < 4; i++)
    {
        printf("ptr + %d = %p, value = %u\n", //%d for signed decimal, %p for an address, %u for unsigned decimal
               i,
               (void *)(ptr + i),
               *(ptr + i));
    }

    return 0;
}