// Lab 05. Bit Permutation
// By: López Reyes José Roberto. 6CV4.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Generate a secret key K
unsigned int gen_key(void) {
    /* TODO: Implement the function */
}

// Generates random S function
void gen_function()
{
    int *S = (int *)malloc(16 * sizeof(int));

    for (int i = 0; i < 16; i++)
    {
        S[i] = i;
    }

    for (int i = 15; i > 0; i--)
    {
        int j = rand() % (i + 1);

        int temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    /* TODO: Save the Box in a file */
}

int main() {

    return 0;
}
