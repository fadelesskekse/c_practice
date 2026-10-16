// // // // // // // // // // // // // // #include <stdio.h>
// // // // // // // // // // // // // // #include <stdint.h>

// // // // // // // // // // // // // // int main(void)
// // // // // // // // // // // // // // {
// // // // // // // // // // // // // //     uint32_t values[4] = {10, 20, 30, 40};

// // // // // // // // // // // // // //     printf("%u\n", values[0]);
// // // // // // // // // // // // // //     printf("%u\n", values[3]);

// // // // // // // // // // // // // //     return 0;
// // // // // // // // // // // // // // }

// // // // // // // // // // // // // //say you did values[4], that will give you a value at the address right next to this array, which could contain something
// // // // // // // // // // // // // //completely unrelated, say its for motor enable... that could cuase weird bugs. 

// // // // // // // // // // // // // #include <stdio.h>
// // // // // // // // // // // // // #include <stdint.h>

// // // // // // // // // // // // // int main(void)
// // // // // // // // // // // // // {
// // // // // // // // // // // // //     uint32_t values[4] = {10, 20, 30, 40};

// // // // // // // // // // // // //     printf("values[4] = %u\n", values[4]);

// // // // // // // // // // // // //     return 0;
// // // // // // // // // // // // // }



// // // // // // // // // // // // ///////uninitialized automatic variables//////////
// // // // // // // // // // // // #include <stdio.h>
// // // // // // // // // // // // #include <stdint.h>

// // // // // // // // // // // // int main(void)
// // // // // // // // // // // // {
// // // // // // // // // // // //     uint32_t x;

// // // // // // // // // // // //     printf("%u\n", x);

// // // // // // // // // // // //     return 0;
// // // // // // // // // // // // }

// // // // // // // // // // // // //Note, for ordinary local variables, doing uint32_t x; doesn't automatically make them 0, they will get whatever
// // // // // // // // // // // // //bit value is stored at that 4 byte location.

// // // // // // // // // // // // //running .main over and over will yield a different value every time

// // // // // // // // // // // // // so always initialize local states before use. 

// // // // // // // // // // // uint32_t result;

// // // // // // // // // // // if (sensor_valid)
// // // // // // // // // // // {
// // // // // // // // // // //     result = sensor_value;
// // // // // // // // // // // }

// // // // // // // // // // // use_result(result);

// // // // // // // // // // // //if sensor is not valid, it could use a bad value


// // // // // // // // // // //////////////signed overflow and dangerous shifts

// // // // // // // // // // uint32_t u = UINT32_MAX;
// // // // // // // // // // u++;
// // // // // // // // // //u wraps to 0 in this case

// // // // // // // // //  int32_t s = INT32_MAX;
// // // // // // // // // s++;

// // // // // // // // //undedfined behavior, ints dont wrap normally. optimizer can assume s will never overflow

// // // // // // // // // int32_t x = ...;

// // // // // // // // // if (x + 1 > x)
// // // // // // // // // {
// // // // // // // // //     ...
// // // // // // // // // }

// // // // // // // // //optimizer might think this is always true, as it might assume x will never overflow '
// // // // // // // // //optimize as always true 

// // // // // // // // #include <stdio.h>
// // // // // // // // #include <stdint.h>
// // // // // // // // #include <limits.h>

// // // // // // // // int main(void)
// // // // // // // // {
// // // // // // // //     uint32_t u = UINT32_MAX;
// // // // // // // //     u++;

// // // // // // // //     printf("unsigned wrapped: %u\n", u);

// // // // // // // //     uint32_t mask = 1u << 31;
// // // // // // // //     printf("mask = 0x%08X\n", mask);

// // // // // // // //     return 0;
// // // // // // // // }


// // // // // // // // /////////alignment amnmd pointer access

// // // // // // // // // A type doesn't only have a size, it  might have alignment requirmenets as well 

// // // // // // // // //ex: on many machines a uint32 (4 bytes) has a size of 4 bytes and start at a location divisible by 4:

// // // // // // // // //0x0000
// // // // // // // // //0x0004
// // // // // // // // //0x008

// // // // // // // #include <stdio.h>
// // // // // // // #include <stdint.h>

// // // // // // // int main(void)
// // // // // // // {
// // // // // // //     printf("uint8_t  size = %zu, alignment = %zu\n",
// // // // // // //            sizeof(uint8_t), _Alignof(uint8_t));

// // // // // // //     printf("uint16_t size = %zu, alignment = %zu\n",
// // // // // // //            sizeof(uint16_t), _Alignof(uint16_t));

// // // // // // //     printf("uint32_t size = %zu, alignment = %zu\n",
// // // // // // //            sizeof(uint32_t), _Alignof(uint32_t));

// // // // // // //     printf("uint64_t size = %zu, alignment = %zu\n",
// // // // // // //            sizeof(uint64_t), _Alignof(uint64_t));

// // // // // // //     return 0;
// // // // // // // }

// // // // // // // //why do we care? 
// // // // // // // //A cpu's memory system is designed around certain transfer sizes and boundaries 

// // // // // // #include <stdio.h>
// // // // // // #include <stdint.h>
// // // // // // #include <stddef.h>

// // // // // // typedef struct
// // // // // // {
// // // // // //     uint8_t  A;
// // // // // //     uint32_t B;
// // // // // // } Example;

// // // // // // int main(void)
// // // // // // {
// // // // // //     printf("sizeof Example = %zu\n", sizeof(Example));
// // // // // //     printf("A offset = %zu\n", offsetof(Example, A));
// // // // // //     printf("B offset = %zu\n", offsetof(Example, B));

// // // // // //     return 0;
// // // // // // }

// // // // // // /////////////aliasing ////////////////
// // // // // // uint32_t x = 0x12345678;

// // // // // // uint32_t *p = &x;
// // // // // // uint32_t *q = &x;

// // // // // // p & q alias each other because they refer to the same object 


// // // // // // uint32_t x = 0x12345678;

// // // // // // float *p = (float *)&x;

// // // // // // both uint32 and float are the same size, but deferencing that p might not be valid. :

// // // // // // float y = *p might not be valid 


// // // // // void example(uint32_t *a, float *b)
// // // // // {
// // // // //     *a = 10;
// // // // //     *b = 5.0f;

// // // // //     printf("%u\n", *a);
// // // // // }

// // // // // //should work, unless you have a and b pointed to the sam ebytes, in which you might get a silent error 

// // // // uint8_t rx[4] = { ... };

// // // // uint32_t value = *(uint32_t *)rx;

// // // // // might cause issues:
// // // // //rx might not have the same alignment requirements as a uint32
// // // // //byte order may not be what you expectg 

// // // // #include <string.h>

// // // // uint8_t rx[4];
// // // // uint32_t value;

// // // // memcpy(&value, rx, sizeof(value));

// // // // //this is a better way to map to different raw representations 


// // // // // uint32_t value =
// // // // //       ((uint32_t)rx[0]      )
// // // // //     | ((uint32_t)rx[1] <<  8)
// // // // //     | ((uint32_t)rx[2] << 16)
// // // // //     | ((uint32_t)rx[3] << 24);

// // // // //or this, as its very direct 


// // // uint32_t x = 0x12345678;

// // // unsigned char *bytes = (unsigned char *)&x;

// // // //C gives character types special access to an objects byte represenataion 

// // // //useful for serialization , checksums , debugging raw memory 
// // // //fundamentally different than treating a uint32 as a float 


// // union
// // {
// //     uint32_t u;
// //     float f;
// // } value;

// // value.u = 0x3F800000;
// // printf("%f\n", value.f);

// #include <stdio.h>
// #include <stdint.h>
// #include <string.h>

// int main(void)
// {
//     uint32_t bits = 0x3F800000;
//     float value;

//     memcpy(&value, &bits, sizeof(value));

//     printf("bits  = 0x%08X\n", bits);
//     printf("float = %f\n", value);

//     return 0;
// }

reg |= (1u << 5);

//actually equates to: 

uint32_t temp = reg;      // READ
temp = temp | (1u << 5);  // MODIFY
reg = temp;               // WRITE

//the worry is something can change reg between the read and right

//suppose initially: reg = 0000 0000

// reg |= (1u << 5);

//cpu first reads: temp = 0000 0000

//before it rwrites back to reg, say an intterupt occurs 

//say the ISR does this: reg |= (1u << 2);

//and we go back, we woudl still write reg = temp, which would override the ISR wriitng     

//does volatile solve this? What is the logic behind this question? 

//volatile makes sure the compiler accesses teh value of reg everytime, but it could still be overridden between the reads 

//SUppose:

volatile uint32_t counter;

//and both main and isr do counter++;

//counter++ is not one operation:

temp = counter;
temp = temp + 1;
counter = temp;

//so we could lose counter values. say counter = 10, we should get counter = 12 with 2 executions of counter++

//but we might only get one

//say we have a register

31                         0
┌───────────────────────────┐
│ status │ config │ control │
└───────────────────────────┘

//and you write mask to reg: REG |= MASK; 

//temp = REG
//temp = temp | MASK

//REG = mASK

//what if some of these bits have special hardware behavior: 
//many registers have "Write 1 to Clear" status bits (W1C)

// Say bit 3 = interrupt flag 

//and the rule is 
//write 0 → leave it alone
//write 1 → clear it

//suppose bit 3 was set because something happened , now lets set a unrelated bit 5:
//reg = 0000 0000 0000 0000 0000 0000 0000 1000
reg |= (1u<<5);
//temp = reg = 0000 0000 0000 0000 0000 0000 0000 1000
//temp = temp | (1u<<5)
//temp = 0000 0000 0000 0000 0000 0000 0010 1000
//reg = temp
//reg = 0000 0000 0000 0000 0000 0000 0010 1000

//the reasoning here has to do with the nature of W1C bits.

//if the flag is high, and then we write high back to that bit, it will clear to 0, so even if we are writing to 
//a bit 5, writing to bit 5 could clear bit 3 if its W1C, because we read its value 

//instead of writing manually to register,s hardware designers often provide atomic set/clear registers, 
//where you write to those instead, and it handles the setting of the desired register appropriately 

//instead of doing REG |= mask;

//we do SET_REG = mask;
// for example, STM32 GPIO has a register called GPIOx_BSRR.
rather than manipulating bits within this register manually like so: 
GPIOA->ODR |= (1u << 5);
we do :

GPIOA->BSRR = (1u << 5);

= set GPIO bit 5
//no intiail read of that register 


//onto critical sections 