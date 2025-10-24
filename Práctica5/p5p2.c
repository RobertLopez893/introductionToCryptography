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

    save_s_file(S, "s_function.txt");
}

// Substitute the block of 4 bits
char *substitution(char *M, int *S, int n)
{    
    char *C = (char *)malloc((n + 1) * sizeof(char));
    if (C == NULL) {
        printf("An error has ocurred.\n");
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        unsigned char byte_original = (unsigned char)M[i];

        int nibble_izq = (byte_original >> 4);
        int nibble_der = (byte_original & 0x0F);

        int nuevo_izq = S[nibble_izq];
        int nuevo_der = S[nibble_der];

        C[i] = (nuevo_izq << 4) | nuevo_der;
        
        printf("Byte[%d]: 0x%02X -> (H:%X, L:%X) -> S(H):%X, S(L):%X -> Nuevo: 0x%02X\n",
               i, byte_original, nibble_izq, nibble_der, nuevo_izq, nuevo_der, (unsigned char)C[i]);
    }
    
    C[n] = '\0';
    return C;
}

// Load the function from the text file
int *load_s_file(const char *filename)
{    
    FILE *file = fopen(filename, "r");
    
    if (file == NULL)
    {
        printf("Error: Couldn't open %s for reading.\n", filename);
        return NULL;
    }
    
    int *S = (int *)malloc(16 * sizeof(int));
    if (S == NULL) {
        printf("Error: Memory allocation failed while loading S-Box.\n");
        fclose(file);
        return NULL;
    }
    
    printf("\nLoading the S function from %s.\n", filename);
    for (int i = 0; i < 16; i++)
    {
        if (fscanf(file, "%X", &S[i]) != 1)
        {
            printf("Error: File format is incorrect or file is corrupted. Failed at value %d.\n", i);
            fclose(file);
            free(S);
            return NULL;
        }
    }

    fclose(file);

    printf("Function S loaded successfully.\n");
    return S;
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
        return 1;
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

    gen_function();    

    int* S = load_s_file("s_function.txt");

    printf("\nRandom S Function Generated: ");

    for (int i = 0; i < 16; i++)
    {
        printf("%02X ", S[i]);
    }
    printf("\n");

    char M2[1024];

    printf("Enter a string of text: ");

    if (fgets(M2, sizeof(M2), stdin) != NULL)
    {
        M2[strcspn(M2, "\n")] = 0;
    }
    else
    {
        printf("Failed to read input.\n");
        return 1;
    }

    int n2 = strlen(M2);

    char* M_substituted = substitution(M2, S, n2);

    if (M_substituted != NULL) {
        printf("\nOriginal Message: ");
        print_hex(M2, n2);
        printf("Ciphered Text: ");
        print_hex(M_substituted, n2);

        free(M_substituted);
    }

    free(S);

    return 0;
}
