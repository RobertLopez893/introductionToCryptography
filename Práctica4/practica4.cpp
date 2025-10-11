// Lab 04. Permutation Cipher
// By: López Reyes José Roberto. 6CV4.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <numeric>
#include <fstream>
#include <sstream>

using namespace std;

// Generates a Random Permutation (for testing purposes)
vector<int> gen_perm(int n)
{
    vector<int> P(n);

    iota(P.begin(), P.end(), 0);

    random_device rd;
    mt19937 g(rd());
    shuffle(P.begin(), P.end(), g);

    return P;
}

// Computes the Inverse Permutation
vector<int> inverse_permutation(vector<int> perm)
{
    if (perm.size() < 3)
    {
        cout << "The permutation size must be at least 3." << endl;
        return {};
    }

    vector<int> inv_perm(perm.size());

    for (int i = 0; i < perm.size(); i++)
    {
        int x = perm[i];
        inv_perm[x] = i;
    }

    return inv_perm;
}

// Permutation Cipher and Decipher
string perm_cipher(string M, vector<int> P)
{
    string C;
    int key_size = P.size();

    int padding_needed = (key_size - (M.size() % key_size)) % key_size;

    if (padding_needed > 0)
    {
        M.append(padding_needed, '$');
    }

    if (M.size() % P.size() != 0)
    {
        cout << "The message's and the permutation's length need to be multiples." << endl;
        return "Error";
    }

    for (int i = 0; i < M.size() / P.size(); i++)
    {
        int x = 0;
        string S = "";
        for (int j = 0; j < P.size(); j++)
        {
            x = P[j];
            S += M[(i * P.size()) + x];
        }
        C += S;
    }

    return C;
}

// Checks if the permutation is valid
bool is_valid_permutation(const vector<int>& p)
{
    int n = p.size();
    if (n == 0) {
        return false;
    }
    vector<int> sorted_p = p;
    sort(sorted_p.begin(), sorted_p.end());
    for (int i = 0; i < n; ++i) {
        if (sorted_p[i] != i) {
            return false; // Checks for missing numbers or duplicates
        }
    }
    return true;
}

int main()
{
    string in_filename;
    cout << "Enter the name of the text file to encrypt: ";
    cin >> in_filename;

    ifstream input_file(in_filename);
    if (!input_file.is_open())
    {
        cerr << "Error: Could not open file '" << in_filename << "'." << endl;
        return 1;
    }

    stringstream buffer;
    buffer << input_file.rdbuf();
    string M = buffer.str();
    input_file.close();

    cout << "Successfully loaded message from " << in_filename << "." << endl;

    int n;
    cout << "\nEnter the size of the permutation key: ";
    cin >> n;

    if (n < 3) {
        cerr << "Error: Permutation size must be greater or equal to 3." << endl;
        return 1;
    }

    vector<int> P(n);
    cout << "Enter the " << n << " elements of the permutation (example: 2 0 1 for size 3):" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> P[i];
    }

    if (!is_valid_permutation(P)) {
        cerr << "Invalid permutation provided." << endl;
        return 1;
    }

    cout << "Encrypting..." << endl;
    string C = perm_cipher(M, P);

    string out_filename = "ciphertext.pi";
    ofstream output_file(out_filename);
    if (!output_file.is_open())
    {
        cerr << "Error: Could not create output file '" << out_filename << "'." << endl;
        return 1;
    }

    output_file << C;
    output_file.close();
    
    cout << "Ciphertext saved in: " << out_filename << endl;

    return 0;
}
