// Lab 04. Permutation Cipher
// By: López Reyes José Roberto. 6CV4.

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <numeric>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

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

    // Fallos si la longitud de M no es igual a la de P
    for (int i = 0; i < M.size() / P.size(); i++)
    {
        int x = 0;
        string S = "";
        for (int j = 0; j < P.size(); j++)
        {
            x = P[j];
            S += M[x];
        }
        C += S;
    }

    return C;
}

int main()
{
    vector<int> P = {3, 1, 0, 2};
    string M = "FLOR SIL";

    string C = perm_cipher(M, P);

    cout << "Plaintext: " << M << endl;
    cout << "Ciphertext: " << C << endl;

    C = "RLFO";
    P = inverse_permutation(P);

    M = perm_cipher(C, P);

    cout << "Ciphertext: " << C << endl;
    cout << "Plaintext: " << M << endl;

    return 0;
}
