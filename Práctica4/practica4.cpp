// Lab 04. Permutation Cipher
// By: López Reyes José Roberto. 6CV4.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <numeric>

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

int main()
{
    int n = 6;
    vector<int> P = gen_perm(n);

    cout << "Permutation: [ ";
    for (int i = 0; i < n; i++)
    {
        cout << P[i] << " ";
    }
    cout << "]" << endl;

    string M = "Mario! Bors?";

    string C = perm_cipher(M, P);

    cout << "Plaintext: " << M << endl;
    cout << "Ciphertext: " << C << endl;

    P = inverse_permutation(P);

    M = perm_cipher(C, P);

    cout << "Ciphertext: " << C << endl;
    cout << "Plaintext: " << M << endl;

    return 0;
}
