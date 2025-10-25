// Lab 05. Bit Permutation
// By: López Reyes José Roberto. 6CV4.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Funciones Ejercicio 1 ---

// Generate de 32bit key
unsigned int generar_clave32(void) {
    unsigned int K = 0;
    for (int i = 0; i < 4; ++i) {        
        unsigned int b = (unsigned int)(rand() % 256);
        K |= (b << (8 * i));                
    }
    return K;
}

// Save the key in a file
void guardar_clave_hex(const char *archivo, unsigned int K) {
    FILE *f = fopen(archivo, "w");
    if (!f) { perror("No se pudo abrir key.txt"); exit(1); }
    fprintf(f, "%08X\n", K);
    fclose(f);
    printf("Clave K guardada en '%s' (hex): %08X\n", archivo, K);
}

// Random S-box
void generar_Sbox(unsigned char S[16]) {
    unsigned char usado[16] = {0};
    for (int z = 0; z < 16; ++z) {
        int v;
        do { v = rand() % 16; } while (usado[v]);
        usado[v] = 1;
        S[z] = (unsigned char)v;              
    }
}

// Save S-box in file
void guardar_Sbox(const char *archivo, const unsigned char S[16]) {
    FILE *f = fopen(archivo, "w");
    if (!f) { perror("No se pudo abrir Sbox.txt"); exit(1); }

    fprintf(f, "z:    ");
    for (int i = 0; i < 16; ++i) fprintf(f, "%X ", i);
    fprintf(f, "\nS(z): ");
    for (int i = 0; i < 16; ++i) fprintf(f, "%X ", S[i]);
    fprintf(f, "\n");

    fclose(f);

    printf("\nS-box guardada en '%s'\n", archivo);
    printf("z:    "); for (int i = 0; i < 16; ++i) printf("%X ", i);
    printf("\nS(z): "); for (int i = 0; i < 16; ++i) printf("%X ", S[i]);
    printf("\n");
}

// --- Funciones Ejercicio 2 ---

// Load key from file
unsigned int cargar_clave_hex(const char *archivo) {
    FILE *f = fopen(archivo, "r");
    if (!f) {
        perror("Error al abrir el archivo de clave");
        exit(1);
    }
    unsigned int K;
    if (fscanf(f, "%X", &K) != 1) {
        fprintf(stderr, "Error al leer la clave del archivo.\n");
        exit(1);
    }
    fclose(f);
    return K;
}

// Load S-box from file
void cargar_Sbox(const char *archivo, unsigned char S[16]) {
    FILE *f = fopen(archivo, "r");
    if (!f) {
        perror("Error al abrir el archivo S-box");
        exit(1);
    }
    
    fscanf(f, "z:    ");
    for (int i = 0; i < 16; ++i) {
        fscanf(f, "%*X");
    }
    
    fscanf(f, "\nS(z): ");
    for (int i = 0; i < 16; ++i) {
        unsigned int val;
        if (fscanf(f, "%X", &val) != 1) {
            fprintf(stderr, "Error al leer valor de S-box.\n");
            exit(1);
        }
        S[i] = (unsigned char)val;
    }
    fclose(f);
}

// Apply the S-box
unsigned char aplicar_Sbox(unsigned char C, const unsigned char S[16]) {
    unsigned char high_nibble = (C >> 4) & 0x0F; 
    unsigned char low_nibble = C & 0x0F;         

    unsigned char sub_high = S[high_nibble];
    unsigned char sub_low = S[low_nibble];

    return (sub_high << 4) | (sub_low & 0x0F);
}

// Toy Encryption Algorithm
unsigned char cifrar_toy(unsigned char M, unsigned int K, const unsigned char S[16]) {
    unsigned char k1 = (unsigned char)(K & 0xFF);
    unsigned char k2 = (unsigned char)((K >> 8) & 0xFF);
    unsigned char k3 = (unsigned char)((K >> 16) & 0xFF);

    printf("Subclaves extraidas de K (%08X):\n", K);
    printf("k1 = %02X\n", k1);
    printf("k2 = %02X\n", k2);
    printf("k3 = %02X\n", k3);
    
    // --- Implementación Algoritmo 2 ---
    unsigned char C = M;
    printf("Ronda 0 (Plaintext M): %02X\n", C);

    // 1. C = M ^ k1
    C = C ^ k1;
    printf("Ronda 1 (Tras k1):     %02X\n", C);

    // 2. C = S(C)
    C = aplicar_Sbox(C, S);
    printf("Ronda 1 (Tras S-box):  %02X\n", C);

    // 3. C = C ^ k2
    C = C ^ k2;
    printf("Ronda 2 (Tras k2):     %02X\n", C);

    // 4. C = S(C)
    C = aplicar_Sbox(C, S);
    printf("Ronda 2 (Tras S-box):  %02X\n", C);

    // 5. C = C ^ k3
    C = C ^ k3;
    printf("Ronda 3 (Tras k3):     %02X\n", C);

    return C;
}


// --- Función Principal ---

int main(void) {
    srand((unsigned)time(NULL)); 

    // --- Ejercicio 1: Generación ---
    printf("--- Ejercicio 1: Generacion de Clave y S-box ---\n");
    unsigned int K_gen = generar_clave32();
    guardar_clave_hex("key.txt", K_gen);

    unsigned char S_gen[16];
    generar_Sbox(S_gen);
    guardar_Sbox("Sbox.txt", S_gen);

    printf("\n\n--- Ejercicio 2: Cifrado 'Toy Encryption' ---\n");

    // a) Pedir nombre de archivo de clave
    char archivo_clave[100];
    printf("Introduce el nombre del archivo de la clave (ej. key.txt): ");
    scanf("%99s", archivo_clave);

    // b) Pedir M (plaintext)
    char M_char;
    printf("Introduce el caracter a cifrar (M): ");
    scanf(" %c", &M_char); // El espacio antes de %c consume el 'Enter' anterior
    unsigned char M = (unsigned char)M_char;

    // c) Cargar K del archivo
    unsigned int K_cargada = cargar_clave_hex(archivo_clave);

    // e) Cargar S-box del archivo
    char archivo_sbox[100];
    unsigned char S_cargada[16];
    printf("Introduce el nombre del archivo de la S-box (ej. Sbox.txt): ");
    scanf("%99s", archivo_sbox);
    cargar_Sbox(archivo_sbox, S_cargada);
    printf("S-box cargada desde '%s'\n", archivo_sbox);

    // f) Cifrar usando los datos cargados
    printf("\n--- Proceso de Cifrado para M = '%c' (%02X) ---\n", M, M);
    unsigned char C = cifrar_toy(M, K_cargada, S_cargada);

    // g) Imprimir C en hexadecimal
    printf("Resultado final (Cifrado C): ");
    printf("%02X\n", C);

    return 0;
}
