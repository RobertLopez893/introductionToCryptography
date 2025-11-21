// Lab 05. Bit Permutation
// By: López Reyes José Roberto. 6CV4.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

/* --- Base64 Helper --- */

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
static int mod_table[] = {0, 2, 1};

// Encoding in Base-64
char *base64_encode(const unsigned char *data, size_t input_length) {
    size_t output_length = 4 * ((input_length + 2) / 3);
    char *encoded_data = malloc(output_length + 1);
    if (encoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }
    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[output_length - 1 - i] = '=';
    encoded_data[output_length] = '\0';
    return encoded_data;
}

// Helper to get value of a base64 char
int b64_value(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

// Decodes Base64 string back to bytes
unsigned char *base64_decode(const char *data, size_t input_length, size_t *output_length) {
    if (input_length % 4 != 0) return NULL;

    *output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=') (*output_length)--;
    if (data[input_length - 2] == '=') (*output_length)--;

    unsigned char *decoded_data = malloc(*output_length);
    if (decoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {
        uint32_t a = data[i] == '=' ? 0 & i++ : b64_value(data[i++]);
        uint32_t b = data[i] == '=' ? 0 & i++ : b64_value(data[i++]);
        uint32_t c = data[i] == '=' ? 0 & i++ : b64_value(data[i++]);
        uint32_t d = data[i] == '=' ? 0 & i++ : b64_value(data[i++]);

        uint32_t triple = (a << 3 * 6) + (b << 2 * 6) + (c << 1 * 6) + (d << 0 * 6);

        if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }

    return decoded_data;
}

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
void gen_function(const char *filename)
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

    save_s_file(S, filename);
    free(S);
}

// Obtain the inverse Sbox
void gen_inv_function(int *S, const char *filename)
{
    int *S_inv = (int *)malloc(16 * sizeof(int));

    for (int z = 0; z < 16; ++z)
    {
        unsigned char valor = S[z];
        S_inv[valor] = z;
    }

    save_s_file(S_inv, filename);
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
void gen_inv_permn(int *P, const char *filename)
{
    int *P_inv = (int *)malloc(8 * sizeof(int));

    for (int z = 0; z < 8; ++z)
    {
        int valor = P[z];
        P_inv[valor - 1] = z + 1;
    }

    save_perm_file(P_inv, filename);
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

/* --- Generate all the files --- */

// Generates all files by asking for their names
void generate_files_interactive() {
    char fname[256];

    printf("\n--- Generating New Crypto Files ---\n");
    
    printf("Name for new Key file: ");
    if (scanf("%255s", fname) == 1) gen_key(fname);
    
    printf("Name for new S-Box file: ");
    if (scanf("%255s", fname) == 1) gen_function(fname);
    
    printf("Name for new Permutation file: ");
    if (scanf("%255s", fname) == 1) gen_perm(fname);

    printf("--- Files Generated ---\n");
    while (getchar() != '\n');
}

// Generates Inverse Files based on existing originals
void generate_inverse_files_interactive() {
    char input_fname[256];
    char output_fname[256];

    printf("\n--- Generating Inverse Files ---\n");

    printf("Enter filename of the S-Box to invert: ");
    if (scanf("%255s", input_fname) == 1) {
        int *S = load_s_file(input_fname);
        if (S) {
            printf("Name for the Inverse S-Box file: ");
            if (scanf("%255s", output_fname) == 1) {
                gen_inv_function(S, output_fname);
            }
            free(S);
        }
    }

    printf("Enter filename of the Permutation to invert: ");
    if (scanf("%255s", input_fname) == 1) {
        int *P = load_perm_file(input_fname);
        if (P) {
            printf("Name for the Inverse Permutation file: ");
            if (scanf("%255s", output_fname) == 1) {
                gen_inv_permn(P, output_fname);
            }
            free(P);
        }
    }
    
    printf("--- Inverse Files Generated ---\n");
    while (getchar() != '\n');
}

/* --- Reads text from file --- */

// Helper to read all text from a file into a string
int read_file_content(const char *filename, char *buffer, size_t max_len) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return 0;
    }
        
    size_t read_size = fread(buffer, 1, max_len - 1, file);
    buffer[read_size] = '\0';
        
    if (read_size > 0 && buffer[read_size - 1] == '\n') {
        buffer[read_size - 1] = '\0';
    }

    fclose(file);
    return 1;
}

// Helper to write a string to a file
void write_file_content(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open %s for writing.\n", filename);
        return;
    }
    fprintf(file, "%s", content);
    fclose(file);
    printf("File successfully saved to %s\n", filename);
}

/* --- Ciphering and Deciphering flows --- */

// Ciphering Person
void bob() {
    printf("\n--- BOB (Encryption) ---\n");    
    
    char key_name[256], sbox_name[256], perm_name[256];
    
    printf("\nEnter Key filename: ");
    if (fgets(key_name, sizeof(key_name), stdin)) key_name[strcspn(key_name, "\n")] = 0;

    printf("Enter S-box filename: ");
    if (fgets(sbox_name, sizeof(sbox_name), stdin)) sbox_name[strcspn(sbox_name, "\n")] = 0;

    printf("Enter Permutation filename: ");
    if (fgets(perm_name, sizeof(perm_name), stdin)) perm_name[strcspn(perm_name, "\n")] = 0;
    
    unsigned int K = load_key(key_name);
    int *S = load_s_file(sbox_name);
    int *P = load_perm_file(perm_name);

    if (!S || !P || K == 0) {
        printf("Error: Could not load files. Make sure they exist.\n");
        if(S) free(S); 
        if(P) free(P);
        return;
    }
    
    char plain_filename[256];
    char plaintext[1024];
    
    printf("\nEnter the plaintext filename: ");
    if (fgets(plain_filename, sizeof(plain_filename), stdin)) {
        plain_filename[strcspn(plain_filename, "\n")] = 0;
    }
        
    if (!read_file_content(plain_filename, plaintext, sizeof(plaintext))) {        
        free(S);
        free(P);
        return;
    }

    size_t len = strlen(plaintext);
    unsigned char *ciphertext = malloc(len);
    if (!ciphertext) {
        printf("Memory allocation error.\n");
        free(S); free(P);
        return;
    }

    printf("\nEncrypting \"%s\" (%zu bytes)...\n", plaintext, len);
    
    for (size_t i = 0; i < len; i++) {
        ciphertext[i] = cipher((unsigned char)plaintext[i], K, S, P);
    }

    char *b64_out = base64_encode(ciphertext, len);
    if (b64_out) {
        printf("--------------------------------------------------\n");
        printf("Ciphertext (Base64): %s\n", b64_out);
        printf("--------------------------------------------------\n");

        char out_filename[256];
        printf("Enter filename to save this Ciphertext: ");
        if (fgets(out_filename, sizeof(out_filename), stdin)) {
            out_filename[strcspn(out_filename, "\n")] = 0;
        }
        write_file_content(out_filename, b64_out);

        free(b64_out);
    } else {
        printf("Error encoding Base64.\n");
    }
    
    free(ciphertext);
    free(S);
    free(P);
}

// Deciphering Person
void alice() {
    printf("\n--- ALICE (Decryption) ---\n");
        
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

    if (!S_inv || !P_inv || K == 0) {
        printf("Error loading files in Alice. Ensure you have the INVERSE files.\n");
        if(S_inv) free(S_inv);
        if(P_inv) free(P_inv);
        return;
    }

     char cipher_filename[256];
    char b64_input[2048]; 
    
    printf("\nEnter the Ciphertext filename: ");
    if (fgets(cipher_filename, sizeof(cipher_filename), stdin)) {
        cipher_filename[strcspn(cipher_filename, "\n")] = 0;
    }

    if (!read_file_content(cipher_filename, b64_input, sizeof(b64_input))) {
        free(S_inv); free(P_inv);
        return;
    }
    
    size_t cipher_len;
    unsigned char *ciphertext = base64_decode(b64_input, strlen(b64_input), &cipher_len);
    
    if (!ciphertext) {
        printf("Error: Invalid Base64 string inside file.\n");
        free(S_inv); free(P_inv);
        return;
    }
    
    char *recovered_plaintext = malloc(cipher_len + 1);
    
    printf("\nDeciphering %zu bytes...\n", cipher_len);
    for (size_t i = 0; i < cipher_len; i++) {        
        recovered_plaintext[i] = decipher(ciphertext[i], K, S_inv, P_inv);
    }
    recovered_plaintext[cipher_len] = '\0'; 
    
    printf("--------------------------------------------------\n");
    printf("Recovered Plaintext: %s\n", recovered_plaintext);
    printf("--------------------------------------------------\n");

    char out_filename[256];
    printf("Enter filename to save Recovered Text: ");
    if (fgets(out_filename, sizeof(out_filename), stdin)) {
        out_filename[strcspn(out_filename, "\n")] = 0;
    }
    write_file_content(out_filename, recovered_plaintext);

    free(ciphertext);
    free(recovered_plaintext);
    free(S_inv);
    free(P_inv);
}

/* --- Main Function --- */

int main()
{
    srand(time(NULL));

    generate_files_interactive();
    generate_inverse_files_interactive();

    bob();

    printf("\n-----------------------------------\n");
    printf("   Transmission through channel...   ");
    printf("\n-----------------------------------\n");

    alice();

    return 0;
}
