// Lab 05. Bit Permutation
// By: López Reyes José Roberto. 6CV4.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Generates a random Key
char *gen_key(int n)
{
    char *K = (char *)malloc((n + 1) * sizeof(char));

    for (int i = 0; i < n; i++)
    {
        K[i] = rand() % (126 - 32 + 1) + 32;
    }

    K[n] = '\0';

    return K;
}

// Enciphers using XOR
char *cipher(char *M, char *K, int n)
{
    char *C = (char *)malloc((n + 1) * sizeof(char));

    for (int i = 0; i < n; i++)
    {
        C[i] = M[i] ^ K[i];
    }

    C[n] = '\0';

    return C;
}

// Prints in Hexadecimal
void print_hex(char *S, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%02X ", (unsigned char)S[i]);
    }
    printf("\n");
}

// Generates random S function
int *gen_function()
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

    return S;
}

// Saves the S Function in a file
void save_s_file(int *S, const char *filename)
{    
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Error: Couldn't open %s for writing.\n", filename);
        return;
    }

    for (int i = 0; i < 16; i++)
    {
        fprintf(file, "%X ", S[i]);
    }

    fclose(file);

    printf("\nThe function S has been succesfully saved in %s\n", filename);
}

int main()
{
    srand(time(NULL));
    char M[1024];

    printf("\n----- Programming Excercises 1 -----\n");

    printf("Enter a string of text: ");

    if (fgets(M, sizeof(M), stdin) != NULL)
    {
        M[strcspn(M, "\n")] = 0;
    }
    else
    {
        printf("Failed to read input.\n");
    }

    int n = strlen(M);

    char *K = gen_key(n);

    char *C = cipher(M, K, n);

    printf("Plaintext: ");
    print_hex(M, n);

    printf("Key: ");
    print_hex(K, n);

    printf("Ciphertext: ");
    print_hex(C, n);

    char *deciphered = cipher(C, K, n);

    printf("Deciphered Text: ");
    print_hex(deciphered, n);

    free(K);
    free(C);
    free(deciphered);

    printf("\n----- Programming Excercises 2 -----\n");

    int* S = gen_function();
    printf("\nRandom S Function Generated: ");

    for (int i = 0; i < 16; i++)
    {
        printf("%X ", S[i]);
    }
    printf("\n");

    save_s_file(S, "s_function.txt");

    free(S);

    return 0;
}
