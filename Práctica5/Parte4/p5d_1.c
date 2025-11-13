// Lab 05. Bit Permutation
// By: López Reyes José Roberto. 6CV4.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Load SBox from a file
void cargar_Sbox(const char *archivo, unsigned char S[16])
{
    FILE *f = fopen(archivo, "r");
    if (!f)
    {
        perror("An error occurred while trying to open the file.");
        exit(1);
    }

    for (int i = 0; i < 16; ++i)
    {
        unsigned int val;

        if (fscanf(f, "%X", &val) != 1)
        {
            fprintf(stderr, "Error: The SBox doesn't contain the 16 valid HEX numbers.\n");
            fclose(f);
            exit(1);
        }
        S[i] = (unsigned char)val;
    }

    fclose(f);
}

// Obtain the inverse Sbox
void invertir_Sbox(const unsigned char S[16], unsigned char S_inv[16])
{
    for (int z = 0; z < 16; ++z)
    {
        unsigned char valor = S[z];
        S_inv[valor] = (unsigned char)z;
    }
}

// Print the Sbox
void imprimir_Sbox(const unsigned char S[16], const char *titulo)
{
    printf("%s\n", titulo);
    printf("z:   ");
    for (int i = 0; i < 16; ++i)
        printf("%X ", i);
    printf("\nS(z):");
    for (int i = 0; i < 16; ++i)
        printf("%X ", S[i]);
    printf("\n\n");
}

// Save the Sbox in a file
void save_s_file(unsigned char *S, const char *filename)
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

    printf("The function S has been succesfully saved in %s\n", filename);
}

// Generate a random Sbox
void gen_function()
{
    unsigned char *S = (unsigned char *)malloc(16 * sizeof(unsigned char));

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

    save_s_file(S, "s_box.txt");
    free(S);
}

// Compare two integers
int compare_ints(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// Swap two integers
void swap_ints(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Generate a random permutation
int *gen_perm(int n)
{
    int *P = (int *)malloc(n * sizeof(int));
    if (P == NULL)
    {
        perror("There was an error assigning the memory for the permutation.");
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        P[i] = i;
    }

    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap_ints(&P[i], &P[j]);
    }

    return P;
}

// Print a value in binary
void imprimirBinario(unsigned char byte) {
    printf("Binary:     ");    
    for (int i = 7; i >= 0; i--) {        
        unsigned char bit = (byte >> i) & 1;
        printf("%u", bit);
                
        if (i == 4) {
            printf(" ");
        }
    }
    printf("\n");
}

// Permutate the bits
unsigned char permutarBits(int P[8], unsigned char dato) {
    unsigned char resultado = 0;
    
    for (int i = 1; i <= 8; i++) {
        unsigned char bit_original = (dato >> (8 - i)) & 1;        
        int nueva_posicion = P[i - 1];
        resultado = resultado | (bit_original << (8 - nueva_posicion));
    }

    return resultado;
}

int main(void)
{
    srand(time(NULL));

    unsigned char S[16], S_inv[16];
    char archivo_entrada[50], archivo_salida[50] = "s_box_inv.txt";

    gen_function();

    printf("Enter the name of the file containing the S-box: ");
    scanf("%s", archivo_entrada);

    cargar_Sbox(archivo_entrada, S);
    imprimir_Sbox(S, "\nOriginal S-box: ");

    invertir_Sbox(S, S_inv);
    imprimir_Sbox(S_inv, "Inverse S-box: ");

    save_s_file(S_inv, archivo_salida);

    unsigned char dato;
        
    printf("Enter a printable ASCII character: ");
    scanf(" %c", &dato); 

    printf("\n--- Original Data ---\n");
    printf("Character:    '%c'\n", dato);
    printf("Hexadecimal:  0x%02X\n", dato);
    imprimirBinario(dato);

    int n_size = 8;

    for (int i = 0; i < 10; i++)
    {
        printf("\n--- Iteration %d ---\n", i);
        int *P = gen_perm(n_size);

        if (P != NULL)
        {
            printf("Generated permutation (size %d): { ", n_size);
            for (int i = 0; i < n_size; i++)
            {
                printf("%d ", P[i]);
            }
            printf("}\n");

            unsigned char dato_permutado = permutarBits(P, dato);

            printf("\n--- Permutation Result ---\n");    
            printf("Character:    '%c'\n", dato_permutado);
            printf("Hexadecimal: 0x%02X\n", dato_permutado);
            imprimirBinario(dato_permutado);

            free(P);
        }
    }

    return 0;
}
