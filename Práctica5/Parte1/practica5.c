// Lab 05. Bit Permutation
// By: López Reyes José Roberto. 6CV4.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// Function to get the nth bit of a number
unsigned char get_nth_bit(unsigned char num, int n)
{
    unsigned char mask = 1 << n;

    unsigned char result = num & mask;

    return result >> n;
}

// Function to set the nth bit of a number
unsigned char set_nth_bit(unsigned char num, int n)
{
    unsigned char mask = 1 << n;

    return num | mask;
}

// Function to count leading zeros
int count_leading_zeros(unsigned char num)
{
    int count = 0;
    int total_bits = sizeof(num) * CHAR_BIT;

    for (int i = total_bits - 1; i >= 0; i--)
    {
        unsigned char mask = 1U << i;

        if ((num & mask) != 0)
        {
            break;
        }

        count++;
    }

    return count;
}

int main()
{
    unsigned char v1 = 0b00011001;

    for (int i = 0; i < 8; i++)
    {
        printf("The %d bit of %d is %x.\n", i, v1, get_nth_bit(v1, i));
    }

    int n = 1;
    unsigned char new_v1 = set_nth_bit(v1, n);

    printf("The %d bit of %d is %x, and now the new number is %d.\n", n, v1, get_nth_bit(new_v1, n), new_v1);

    printf("Number of leading zeros in %d is %d.\n", v1, count_leading_zeros(v1));

    return 0;
}
