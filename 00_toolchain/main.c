
#include <stdio.h> // Std C Library: Std I/O declarations
                    // Things like printf();
//#include <stdint.h> // Gives us fixed-width integer types
                    // very important for C
                    
#include "math_utils.h"

// int main(void)
// {
//     uint32_t x = 5;
//     uint32_t y = 3;
//     uint32_t result = x + y;

//     printf("result = %u\n", result);

//     return 0;
// }

//gcc main.c -o main generates the object files and links them  (the executable that you can run)

//instead lets generate the object files but don't link

// -c: compile the files (tells the  "system" not to link but stop at compile)
// -o: name the object file that will be linked

// When linked, we get an executable

// Running file main will give us info on what the executable is:

// ELF 64-bit: File formate used for executables and object files on Linux

//when using the STM32 toolchain, the executable and object files genereated will target my STM32 MCU

// dakota@dakota-Legion-5-16IAX10:~/.local/repos/c_practice/00_toolchain$ size main
//    text	   data	    bss	    dec	    hex	filename
//    1505	    604	     12	   2121	    849	main


//text: program instructions/read-only program code

//data: initialized writable global/static data
    //in .data
//bss: zero initialized global/static data
    //in .bss

//local: stack/register

// uint32_t global_initialized = 123;
// uint32_t global_uninitialized;

//uint32_t global_initialized1 = 123;
// int main(void)
// {
//     uint32_t local = 456;
//   //  uint32_t local1 = 4923;
//    // static uint32_t local2;
    

//     printf("global_initialized = %u\n", global_initialized);
//  //printf("global_initialized = %u\n", global_initialized1);

//     printf("global_uninitialized = %u\n", global_uninitialized);
//     printf("local = %u\n", local);
//   // printf("local1 = %u\n", local1);
//    // printf("local1 = %u\n", local2);


//     return 0;
// }

// add a new local var
// dakota@dakota-Legion-5-16IAX10:~/.local/repos/c_practice/00_toolchain$ size main
//    text	   data	    bss	    dec	    hex	filename
//    1550	    604	     12	   2166	    876	main


//Note if you add a local variable but don't use it, the compiler can automatically remove it
//depending on the level of optimization

// So simply added local1 without calling printf in this case doesn't increase memory usage

//NOw that printf is in, rebuild, and run size main

// dakota@dakota-Legion-5-16IAX10:~/.local/repos/c_practice/00_toolchain$ size main
//    text	   data	    bss	    dec	    hex	filename
//    1550	    604	     12	   2166	    876	main

// Note the printf()call added to text, but nothing added to data or bss

// This is because only global variables add to these, not local, which are typically in a stack or register
//
// Change local1 to global should contribute to data

// dakota@dakota-Legion-5-16IAX10:~/.local/repos/c_practice/00_toolchain$ size main
//    text	   data	    bss	    dec	    hex	filename
//    1546	    608	      8	   2162	    872	main


// Note the increase in data size by 4. This means data is shown as bytes,
//and since 32 bits = 4 bytes, that explains it. 

//But why did bss go down? 
// ALignment book keeping. Move on

int main(void)
{
    uint32_t x = 5;
    uint32_t y = 3;

    uint32_t result = add(x, y);

    printf("result = %u\n", result);

    return 0;
}

// gcc -Wall -Wextra -Wpedantic -Wconversion -g -c math_utils.c
// gcc -Wall -Wextra -Wpedantic -Wconversion -g -c main.c
// gcc -Wall -Wextra -Wpedantic -Wconversion -g main.o -o main


//We can compile separate translation units file
// But when running the linker on only just main, it is missing a reference to add.

//Because we included the math_utils.h into the main.c, we have a declaration. So it will compiel

//now lets try the debugger gbd

// gdb ./main
//break main // adds a break point at the beginning of main

//run 

//next steps line by line
//conitnue goes to the next break
//info registers : shows that teh actual processor has registers and a statemachine that GDB can inspect

//quit