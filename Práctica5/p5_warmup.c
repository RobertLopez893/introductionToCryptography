#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(0));
    printf("--- Excercise 1 ---\n");

    unsigned char data;
    data = 'S'; // (rand() % 96) + 32;

    printf("Character: %c\n", data);
    printf("Hexadecimal Value: %x\n", data);
    printf("Integer Value: %d\n", data);

    printf("--- Excercise 2 ---\n");

    for (int i = 0; i < 8; i++)
    {
        printf("* Iteration %d\n", i + 1);
        data = data << 1;

        printf("Character: %c\n", data);
        printf("Hexadecimal Value: %x\n", data);
        printf("Integer Value: %d\n", data);
    }

    printf("--- Excercise 3 ---\n");

    data = 'A';

    for (int i = 0; i < 8; i++)
    {
        printf("* Iteration %d\n", i + 1);
        data = data >> 1;

        printf("Character: %c\n", data);
        printf("Hexadecimal Value: %x\n", data);
        printf("Integer Value: %d\n", data);
    }

    printf("--- Excercise 4 ---\n");

    unsigned char v1 = 0b01101101;
    unsigned char v2 = 0b10101111;

    printf("AND Operation:\n");

    printf("Hexadecimal Value: %x\n", v1 & v2);
    printf("Integer Value: %d\n", v1 & v2);

    printf("OR Operation:\n");

    printf("Hexadecimal Value: %x\n", v1 | v2);
    printf("Integer Value: %d\n", v1 | v2);

    printf("XOR Operation:\n");

    printf("Hexadecimal Value: %x\n", v1 ^ v2);
    printf("Integer Value: %d\n", v1 ^ v2);

    printf("--- Excercise 5 ---\n");

    unsigned char data2 = 0b11100101;
    unsigned char mask = 0b10000000;

    printf("Original data2: %x\n", data2);
    printf("Mask: %x\n", mask);
    printf("Result: %x\n", data2 & mask);

    printf("--- Excercise 6 ---\n");

    mask = 0b00001000;

    printf("Original data2: %x\n", data2);
    printf("Mask: %x\n", mask);
    printf("Result: %x\n", data2 & mask);

    return 0;
}
