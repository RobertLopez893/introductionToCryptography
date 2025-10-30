// Lab 05. Bit Permutation
// By: López Reyes José Roberto. 6CV4.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

    printf("The function S has been succesfully saved in %s\n", filename);
}

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

    printf("\nLoading the S function from %s.\n", filename);
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

int main()
{
    srand(time(NULL));

    gen_key("key.txt");
    gen_function();

    char key_name[256];
    char sbox_name[256];

    printf("\nEnter the name of your key file: ");

    if (fgets(key_name, sizeof(key_name), stdin) != NULL) {
        key_name[strcspn(key_name, "\n")] = '\0';
    }

    printf("\nEnter the name of your S-box file: ");

    if (fgets(sbox_name, sizeof(sbox_name), stdin) != NULL) {
        sbox_name[strcspn(sbox_name, "\n")] = '\0';
    }

    unsigned int K = load_key(key_name);
    int *S = load_s_file(sbox_name);
    
    free(S);

    return 0;
}
