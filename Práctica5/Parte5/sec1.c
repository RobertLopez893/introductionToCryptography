// Lab 05. Bit Permutation
// By: López Reyes José Roberto. 6CV4.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Multiplicative module
unsigned char prod_mod(unsigned char coefs) {
    // 0010 1011
    unsigned char mx = 0x2B;
    unsigned char res;

    if((coefs >> 7) == 0x00) {
        res = coefs << 1;
    } else {
        res = (coefs << 1) ^ mx;
    }

    return res;
}

// Multiplicative module with two functions
unsigned char prod_mod_func(unsigned char f, unsigned char g) {
    unsigned char res = 0x00;

    for (int i = 0; i < 8; i++)
    {
        if(g & 0x01) {
            res = res ^ f;
        }

        f = prod_mod(f);

        g = g >> 1;
    }

    return res;
}

// Print the results
void print_res(unsigned char fx, unsigned char gx, unsigned char res) {
    printf("f(x) = %02X\n", fx);
    printf("g(x) = %02X\n", gx);
    printf("g(x) * f(x) mod m(x) = %02X\n", res);
}

int main(void)
{
    unsigned char fx = 0x53;
    unsigned char res;

    res = prod_mod(fx);

    printf("f(x) = %02X\n", fx);
    printf("x * f(x) mod m(x) = %02X\n", res);

    unsigned char gx = 0x95;

    printf("----- First Example -----\n");

    res = prod_mod_func(fx, gx);
    print_res(fx, gx, res);

    printf("----- Second Example -----\n");

    res = prod_mod_func(0x56, 0x88);
    print_res(0x56, 0x88, res);

    printf("----- Third Example -----\n");

    res = prod_mod_func(0x09, 0x3D);
    print_res(0x09, 0x3D, res);

    printf("----- Fourth Example -----\n");

    res = prod_mod_func(0X66, 0X77);
    print_res(0X66, 0X77, res);
    
    printf("----- Fifth Example -----\n");

    res = prod_mod_func(0XB6, 0XAE);
    print_res(0XB6, 0XAE, res);

    return 0;
}
