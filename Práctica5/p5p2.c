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
char *cipher(char* M, char* K) {
    int n = strlen(M);

    char *C = (char *)malloc((n + 1) * sizeof(char));

    for (int i = 0; i < n; i++)
    {
        C[i] = M[i] ^ K[i];
    }

    C[n] = '\0';

    return C;    
}

// Prints in Hexadecimal
void print_hex(char* S) {
    for (int i = 0; i < strlen(S); i++)
    {
        printf("%x ", (unsigned char)S[i]);
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));
    char M[1024];

    printf("Enter a string of text: ");

    if (fgets(M, sizeof(M), stdin) != NULL)
    {
        M[strcspn(M, "\n")] = 0;
    }
    else
    {
        printf("Failed to read input.\n");
    }

    char* K = gen_key(strlen(M));

    char* C = cipher(M, K);

    printf("Plaintext: ");
    print_hex(M);

    printf("Key: ");
    print_hex(K);

    printf("Ciphertext: ");
    print_hex(C);

    char* deciphered = cipher(C, K);

    printf("Deciphered Text: ");
    print_hex(deciphered);

    free(K);
    free(C);    
    free(deciphered);

    return 0;
}
