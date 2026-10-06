// #include <stdio.h>
// #include <stdint.h>

// int main(void)
// {
//     uint8_t  a = 255;
//     uint16_t b = 1000;
//     uint32_t c = 100000;

//     printf("a = %u\n", a);
//     printf("b = %u\n", b);
//     printf("c = %u\n", c);

//     return 0;
// }

// Suppose we have TIM2_CNT is a 32-bit timer counter register.
//We know it goes from 0 - 2^32 -1

// #include <stdio.h>
// #include <stdint.h>

// int main(void)
// {
//     uint8_t x = 255;

//     printf("before: %u\n", x);

//     x++;
//     // It literally will cycle back to 0

//     printf("after:  %u\n", x);

//     return 0;
// }

// Onto Hex:

//0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F
//0000,0001,0010,0011,0100,0101,0110,0111,1000,1001,1010 = A, 1011 = B, 1100 = C, 1101 = D, 1110 = E, 1111 = F

//uint8_t x = 0xA5; //You can do this as well instead of defining it as an integer. 

//0xA5 = 10110101
// imagine a 32 bit integer: 00000000 00000000 00000000 00100000, or 0x00000020, hex is much easier

// #include <stdio.h>
// #include <stdint.h>

// int main(void)
// {
//     uint32_t x = 0xA5;

//     printf("decimal: %u\n", x);
//     printf("hex:     0x%08X\n", x); //The 0 pads the empty spaces, 8 is the number of hex bits, X is print in hex upper case

//     return 0;
// }

//a = 10101100
//b = 00001111

//a & b = 00001100 = 0x0C

// AND can be used to select or deselect bits

// BITWISE OR = |

//   10100000
// | 00000101
// ----------
//   10100101

//a | b = 10100101 = 0xA5

//~ = NOT, flips every bit

//XOR = exclusive or
//   10100000
// ^ 00100000
// ----------
//   10000000

// #include <stdio.h>
// #include <stdint.h>

// int main(void)
// {
//     uint8_t a = 0xAC; //10101100
//     uint8_t b = 0x0F; //00001111

//     uint8_t and_result = a & b; //00001100 = 0x0C
//     uint8_t or_result  = a | b; //10101111 = 0xAF
//     uint8_t xor_result = a ^ b;

//     printf("a     = 0x%02X\n", a);
//     printf("b     = 0x%02X\n", b);

//     printf("a & b = 0x%02X\n", and_result);
//     printf("a | b = 0x%02X\n", or_result);
//     printf("a ^ b = 0x%02X\n", xor_result);

//     uint32_t x = 1;

//     printf("x      = 0x%08X\n", x); //0x00000001 
//     printf("x << 1 = 0x%08X\n", x << 1); //0x00000002
//     printf("x << 2 = 0x%08X\n", x << 2); //0x00000004
//     printf("x << 5 = 0x%08X\n", x << 5); // 00000001 -> 00100000 = 0010 0000 = 0x20

//     return 0;
// }

//Note; 1u means an unsigned 1.

// 1u << n (I.E> 1u << 5) creates 0010 0000 from 0000 0001, so its basically just a way to create a bit mask where the only bit that is 1 is the 5th bit

//reg  = 1010 0101
//mask = 0010 0000   ← 1u << 5

//now we can do thing s with this mask

//reg |= (1u << 5);

//Do a BITWISE or operation using a bit mask whose 5 element is 1. 

//   1010 0101
// | 0010 0000
// -----------
//   1010 0101

// reg ^= (1u << 5);

//   1010 0101
// ^ 0010 0000
// -----------
//10000101
  
// #include <stdio.h>
// #include <stdint.h>

// int main(void){

//     uint32_t reg = 0x00000000;
//     printf("reg = 0x%08X\n",reg);
//     reg |=  (1u << 5);     // set bit 5: 0x0000000 | 0x00000020
//     printf("reg after or = 0x%08X\n",reg);//-> 0x00000020

//     //0010 0000 & 1101 1111 -> 0000 0000
//     reg &= ~(1u << 5);     // clear bit 5 -> 0x00000020 & 0xFFFFFFDF -> 0x00000000

//     printf("reg after and = 0x%08X\n",reg);
//     reg ^=  (1u << 5);     // toggle bit 5 -> 
//     printf("reg after xor = 0x%08X\n",reg); // 0x00000000 ^ 0x00000020 = 0x00000020

//     if (reg & (1u << 5))   // test bit 5
//     {
//         // bit 5 is set
//     }

//     return 0;
// }

//
// bit:   7 6 5 4 3 2 1 0
//        ───────────────
// reg =  1 0 1 1 0 1 0 1
//              └───┘
//              field

//Imagine a register has several fields in it, where say bits 4-6 are a MODE field 

// #include <stdio.h>
// #include <stdint.h>

// int main(void){

//     uint32_t reg = 0x000000B5; //Suppose this is the value of our register
//     //1011 0101 = 0xB5
//     //Bits 4-6: 011
//     //How can we extract bits 4-6 from this?
//     // uint32_t mode = (reg >> 4); //removes the lower 0,1,2,3: 1011
//     // printf("mode = 0x%08X\n",mode); //Now we need 011 only. We can use the & operator to get that
//     // uint32_t bit_mode_sel = 0x7u;

//     // mode &= bit_mode_sel;
//     // printf("mode = 0x%08X\n",mode);

//     uint32_t mode = (reg >> 4) & 0x7u;
//     printf("mode = 0x%08X\n",mode);

//     uint32_t reg = 0x20; //suppose we just have 1 value: LSB's are 0010 0000

//     if (reg & (1u << 5)) // If we are only looking at 1 bit, we normally don't need to shift down 
//     //This evaluates as a boolean. If there is a 1 at bit 5, then we are good 
//     {
//         printf("Bit 5 is set\n");
//     }

    

    

//     return 0;
// }


//0000 = 0
// 0001 = 1
// 0010 = 2
// 0011 = 3
// 0100 = 4
// 0101 = 5
// 0110 = 6
// 0111 = 7
// 1000 = 8
// 1001 = 9
// 1010 = A, 1011 = B, 1100 = C, 1101 = D, 1110 = E, 1111 = F


// 31                    7 6 5 4 3 2 1 0
// ──────────────────────────────────────
//                       | MODE | E | R | //suppose an imaginary control register looks liek this 

// bit 0      RUN
// bit 2      ENABLE
// bits 4–6   MODE

//Note, & can be used for selecting or deselecting bits
// | can be used for assigning bits? 

// #include <stdio.h>
// #include <stdint.h> 

// #define RUN_BIT (1u << 0)
// #define ENABLE_BIT (1u << 2) //0100

// #define MODE_POS 4u
// #define MODE_MASK (0x7u << MODE_POS)

// //so we get 0111 -> 0111 0000


// int main(void){
//     uint32_t control_reg = 0x00;

//     // To enable the system: 

//     control_reg |= ENABLE_BIT; //Should get 0000 0100

//     printf("control_reg = 0x%08X\n",control_reg);// indeed that is what we get.
//     // So we enabled the system

//     control_reg |= RUN_BIT;
//     printf("control_reg = 0x%08X\n",control_reg);

//     // 0000 0101
//     //Set MODE = 5 -> 101
//     control_reg &= ~MODE_MASK; 
//     //~MODE_MASK = 1000 1111
//     // 0000 0101 & 1000 1111. Note the 4 LSB remain selected
//     //control reg = the same? . Yes. the point is to clear bits 4,5,6.
//     //while keepign everything else the same
//     printf("control_reg = 0x%08X\n",control_reg);

//     control_reg |= (5u << MODE_POS);
//     printf("control_reg = 0x%08X\n",control_reg);

//     // uint32_t mode = (control_reg >> MODE_POS) & 0x7u;
//     // printf("mode = 0x%08X\n",mode);
//     //or you can do:

//     uint32_t mode = (control_reg & MODE_MASK) >> MODE_POS;
//     //keep only th emode and shift to the mode pos

//     //Notice that we only want to insert up to 3 bits, and note
//     //that in hex that goes up to 7.

//     //So how can we ensure only up to 7 is input? 
//     //instead of control_reg |= (mode << MODE_POS);
//     // do control_reg |= ((mode & 0x7u) << MODE_POS);
//     //using the 0x7u here selects only the 3 LSB bits since 7 is 0111. So that
//     //ensures that mode is indeed only 3 bits







// }


// uint8_t u; 0-255
// int8_t  s; -128 <= s <= 127

// Note for unsigned behavior, overflowing resets to 0.
// The same cannot be said for signed behavior. THis is actually
//undefined behavior

//  #include <stdio.h>
//  #include <stdint.h>

//  int main(void)
//  {
// //     // uint8_t a = 250;
// //     // uint8_t b = 10;

// //     // uint8_t result = a + b;

// //     // printf("result = %u\n", (unsigned)result);

// //     // uint8_t a = 5;
// //     // uint8_t b = 10;

// //     // printf("sizeof(a)     = %zu\n", sizeof(a));
// //     // printf("sizeof(a+b)   = %zu\n", sizeof(a + b));

//      uint8_t x = 0x0F; // 00001111
// //     printf("sizeof(x)     = %zu\n", sizeof(x));


// //     x = ~x; // I would think it would be 1111 0000.
// //     printf("sizeof(x)     = %zu\n", sizeof(x));

//     printf("sizeof(x)  = %zu\n", sizeof(x)); //1 byte
//     printf("sizeof(~x) = %zu\n", sizeof(~x)); // 4 bytes big since it gets promtoed





//      return 0;
//  }

//Note, the CPU isn't actually doing 8 bit arithmetic.
// It actually promotes the uint8_t's to 32 bit ints because every possible uint8_t can be represented by an int

//so we really get (int)250 + (int)10 = 260

//with the overflow, we get 1413 text size using size main
// same with non overflow, why?

//Maybe the machien code that is generated automatiically converts up to 32 bits? 

//note the sizeof yields byte sizes. 
//So a is one byte, but a + b is 4 bytes (32 bits) promotion


/////////////////////lets investigate bugs iwth signed and unsigned combos
//Review 2's complement



#include <stdio.h>
#include <stdint.h>

int main(void){

// int32_t  signed_value   = -1;
// uint32_t unsigned_value = 1;


// if (signed_value < unsigned_value)
// {
//     printf("-1 is smaller\n");
// }
// else
// {
//     printf("something surprising happened\n");
// }
// }
//Note that C has rules when comparing 2 different types. 
//I get lots of segmentation faults trying to cast a -1 int32_t to a uint32_t

//This can pose issues: (I.E. current time - past time) but current time is accidentially a int32_t, whcih can go negative

// uint8_t a = 255;
// a++;
// printf("%u\n",a);

// uint8_t a = 250;
// uint8_t b = 10;

// printf("%zu\n", sizeof(a + b));

  //  uint8_t x = 0x0F;
//0000 1111 -> unsigned x =  4 + 2 + 1 + 8
   // printf("x  = 0x%02X\n", (unsigned)x); //= 15
   // printf("~x = 0x%08X\n", (unsigned)~x);// Gets upconverted to 32 bits recall, so we get 11111111 11111111 11111111 1111 0000
    //0xFFFFFFF0
    // ~x normally upconverts to 4 bytes (32 bits)
    int32_t  a = -1;
uint32_t b = 1;

if (a < b)
    printf("a < b\n");
else
    printf("a >= b\n");
}