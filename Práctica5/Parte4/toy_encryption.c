// Lab 05. Bit Permutation
// By: López Reyes José Roberto. 6CV4.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* --- Print in Binary --- */

// Print a value in binary
void printBin(unsigned char byte) {
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

/* --- Cipher Key --- */

// Generate a secret key K
void gen_key(const char *filename)
{
    unsigned int K = ((unsigned int)rand() << 16) | rand();

    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error: Couldn't open %s for writing.\n", filename);
        return;
    }

    fprintf(file, "%X", K);
    fclose(file);

    printf("32-bit key generated and saved to %s\n", filename);
}

// Load key from file
unsigned int load_key(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Couldn't open %s for reading.\n", filename);
        return 0;
    }

    printf("\nLoading the key from %s.\n", filename);

    unsigned int K;
    if (fscanf(file, "%X", &K) != 1)
    {
        printf("Error reading key from %s.\n", filename);
        fclose(file);
        return 0;
    }

    fclose(file);
    printf("Key loaded successfully from %s.\n", filename);
    return K;
}

/* --- S-box --- */

// Save S-box in a file
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

    printf("S-box has been succesfully saved in %s\n", filename);
}

// Load the S-box from a file
int *load_s_file(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error: Couldn't open %s for reading.\n", filename);
        return NULL;
    }

    int *S = (int *)malloc(16 * sizeof(int));
    if (S == NULL)
    {
        printf("Error: Memory allocation failed while loading S-Box.\n");
        fclose(file);
        return NULL;
    }

    printf("\nLoading the S-box from %s.\n", filename);
    for (int i = 0; i < 16; i++)
    {
        if (fscanf(file, "%X", &S[i]) != 1)
        {
            printf("Error: File format is incorrect or file is corrupted.\n");
            fclose(file);
            free(S);
            return NULL;
        }
    }

    fclose(file);
    printf("Function S loaded successfully.\n");
    return S;
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

    save_s_file(S, "s_box.txt");
    free(S);
}

// Obtain the inverse Sbox
void gen_inv_function(int *S)
{
    int *S_inv = (int *)malloc(16 * sizeof(int));

    for (int z = 0; z < 16; ++z)
    {
        unsigned char valor = S[z];
        S_inv[valor] = z;
    }

    save_s_file(S_inv, "s_box_inv.txt");
    free(S_inv);
}

/* --- Permutation --- */

// Swap two integers
void swap_ints(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Save Permutation to a file
void save_perm_file(int *P, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Couldn't open %s for writing.\n", filename);
        return;
    }
    for (int i = 0; i < 8; i++) {
        fprintf(file, "%d ", P[i]);
    }
    fclose(file);
    printf("Permutation P has been succesfully saved in %s\n", filename);
}

// Load Permutation from a file
int *load_perm_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Couldn't open %s for reading.\n", filename);
        return NULL;
    }

    int *P = (int *)malloc(8 * sizeof(int));
    if (P == NULL) {
        printf("Error: Memory allocation failed for P-Box.\n");
        fclose(file);
        return NULL;
    }

    printf("\nLoading the Permutation from %s.\n", filename);
    for (int i = 0; i < 8; i++) {
        if (fscanf(file, "%d", &P[i]) != 1) {
            printf("Error: File format incorrect for P-Box.\n");
            fclose(file);
            free(P);
            return NULL;
        }
    }

    fclose(file);
    printf("Permutation loaded successfully.\n");
    return P;
}

// Generate Random Permutation
void gen_perm(const char *filename) {
    int n = 8;
    int *P = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        P[i] = i + 1; 
    }

    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap_ints(&P[i], &P[j]);
    }

    save_perm_file(P, filename);
    free(P);
}

// Obtain the inverse Permutation
void gen_inv_permn(int *P)
{
    int *P_inv = (int *)malloc(8 * sizeof(int));

    for (int z = 0; z < 8; ++z)
    {
        int valor = P[z];
        P_inv[valor - 1] = z + 1;
    }

    save_perm_file(P_inv, "perm_inv.txt");
    free(P_inv);
}

/* --- Ciphering Operations --- */

// Substitute the block of 4 bits
unsigned char substitution(unsigned char M, int *S)
{
    int nibble_izq = (M >> 4) & 0x0F;
    int nibble_der = M & 0x0F;       
    
    int nuevo_izq  = S[nibble_izq];
    int nuevo_der  = S[nibble_der];
    
    return (unsigned char)((nuevo_izq << 4) | nuevo_der);
}

// Permutate the bits
unsigned char permutation(unsigned char dato, int P[8]) {
    unsigned char resultado = 0;
    
    for (int i = 1; i <= 8; i++) {
        unsigned char bit_original = (dato >> (8 - i)) & 1;        
        int nueva_posicion = P[i - 1];
        resultado = resultado | (bit_original << (8 - nueva_posicion));
    }

    return resultado;
}

/* --- Toy Encryption and Decryption --- */

// Toy Encryption Algorithm
unsigned char cipher(unsigned char M, unsigned int K, int *S, int *P) {
    unsigned char C;

    unsigned char k[4];
    k[0] = (K >> 24) & 0xFF;
    k[1] = (K >> 16) & 0xFF;
    k[2] = (K >> 8) & 0xFF;
    k[3] = K & 0xFF;

    for (int i = 0; i < 3; i++)
    {
        M = M ^ k[i];
        M = substitution(M, S);
        M = permutation(M, P);
    }

    C = M ^ k[3];
    return C;
}

// Toy Decryption Algorithm
unsigned char decipher(unsigned char C, unsigned int K, int *S, int *P) {
    unsigned char M;

    unsigned char k[4];
    k[0] = (K >> 24) & 0xFF;
    k[1] = (K >> 16) & 0xFF;
    k[2] = (K >> 8) & 0xFF;
    k[3] = K & 0xFF;

    M = C ^ k[3];

    for (int i = 2; i >= 0; i--)
    {
        M = permutation(M, P);
        M = substitution(M, S); 
        M = M ^ k[i];               
    }

    return M;
}

/* --- Ciphering and Deciphering flows --- */

// Ciphering Person
void bob() {
    printf("\n--- BOB (Encryption) ---\n");
        
    gen_key("key.txt");
    gen_function(); 
    gen_perm("perm.txt");   
    
    char key_name[256], sbox_name[256], perm_name[256];

    printf("Enter Key file: ");
    if (fgets(key_name, sizeof(key_name), stdin)) key_name[strcspn(key_name, "\n")] = 0;

    printf("Enter S-box file: ");
    if (fgets(sbox_name, sizeof(sbox_name), stdin)) sbox_name[strcspn(sbox_name, "\n")] = 0;

    printf("Enter Permutation file: ");
    if (fgets(perm_name, sizeof(perm_name), stdin)) perm_name[strcspn(perm_name, "\n")] = 0;
    
    unsigned int K = load_key(key_name);
    int *S = load_s_file(sbox_name);
    int *P = load_perm_file(perm_name);
    
    if(S && P) {
        gen_inv_function(S);
        gen_inv_permn(P);
    } else {
        printf("Error loading files in Bob.\n");
        return;
    }

    unsigned char M;
    printf("Enter a single printable ASCII character: ");
    scanf(" %c", &M);
    
    while (getchar() != '\n'); 
    
    unsigned char C = cipher(M, K, S, P);
    printf("\nCiphered Char: %c", C);
    printf("\nCiphered Hex:  %02X\n", C);    
    printBin(C);

    free(S);
    free(P);
}

// Deciphering Person
void alice() {
    printf("\n--- ALICE (Decryption) ---\n");
    
    unsigned char C;
    printf("Enter a single printable ASCII character: ");
    scanf(" %c", &C);

    while (getchar() != '\n');

    char key_name[256], sbox_inv_name[256], perm_inv_name[256];

    printf("\nEnter Key file: ");
    if (fgets(key_name, sizeof(key_name), stdin)) key_name[strcspn(key_name, "\n")] = 0;

    printf("Enter Inverse S-box file: ");
    if (fgets(sbox_inv_name, sizeof(sbox_inv_name), stdin)) sbox_inv_name[strcspn(sbox_inv_name, "\n")] = 0;

    printf("Enter Inverse Permutation file: ");
    if (fgets(perm_inv_name, sizeof(perm_inv_name), stdin)) perm_inv_name[strcspn(perm_inv_name, "\n")] = 0;
    
    unsigned int K = load_key(key_name);
    int *S_inv = load_s_file(sbox_inv_name);
    int *P_inv = load_perm_file(perm_inv_name);

    if (!S_inv || !P_inv) {
        printf("Error loading files in Alice.\n");
        return;
    }
    
    unsigned char recover = decipher(C, K, S_inv, P_inv);
    
    printf("\nRecovered Char: %c", recover);
    printf("\nRecovered Hex:  %02X\n", recover); 
    printBin(recover);

    free(S_inv);
    free(P_inv);
}

/* --- Main Function --- */

int main()
{
    srand(time(NULL));

    bob();

    printf("\n-----------------------------------\n");
    printf("   Transmission through channel...   ");
    printf("\n-----------------------------------\n");

    alice();

    return 0;
}
