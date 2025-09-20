// Lab 02. Affine Cipher
// By: López Reyes José Roberto and Hernández Zamora Alejandro. 6CV4.

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

vector<char> alphabetVector;
map<char, int> alphabetMap;

// Fills with the ASCII characters manually
void fill_alphabet()
{
    for (int i = 32; i <= 126; ++i)
    {
        alphabetVector.push_back(static_cast<char>(i));
        alphabetMap[(char)i] = alphabetVector.size() - 1;
    }
}

// Extended Euclidean Algorithm (EEA)
vector<int> extendedEuclideanAlgorithm(int r0, int r1)
{
    if (r0 < r1)
    {
        cout << "Not a valid pair.\n";
        return {};
    }

    int s0 = 1;
    int s1 = 0;
    int i = 1;
    int t0 = 0;
    int t1 = 1;

    vector<int> s = {s0, s1};
    vector<int> t = {t0, t1};
    vector<int> r = {r0, r1};
    vector<int> q;

    do
    {
        i = i + 1;

        r.resize(i + 1);
        s.resize(i + 1);
        t.resize(i + 1);
        q.resize(i);

        r[i] = r[i - 2] % r[i - 1];
        q[i - 1] = (r[i - 2] - r[i]) / r[i - 1];
        s[i] = s[i - 2] - q[i - 1] * s[i - 1];
        t[i] = t[i - 2] - q[i - 1] * t[i - 1];
    } while (r[i] != 0);

    return {r[i - 1], s[i - 1], t[i - 1]};
}

// Returns the Z*n set
vector<int> Zestrella(int n)
{
    if (n < 2)
    {
        cout << "Your number needs to be greater or equal to 2.\n";
        return {};
    }

    vector<int> result;
    vector<int> gcd;
    for (int a = 1; a < n; a++)
    {
        gcd = extendedEuclideanAlgorithm(n, a);
        if (gcd[0] == 1)
        {
            result.push_back(a);
        }
    }

    return result;
}

// Finding b such that ab mod n = 1
int find_b(int n, int a)
{
    int b;
    vector<int> Zn = Zestrella(n);

    if (n < 2 || find(Zn.begin(), Zn.end(), a) == Zn.end())
    {
        cout << "\nAn error occured that can't let the program continue.\n";
        return -1;
    }

    vector<int> res = extendedEuclideanAlgorithm(n, a);

    if (res[0] != 1)
    {
        cout << "\nThere's no existing inverse.\n";
        return -1;
    }

    return (res[2] % n + n) % n;
}

// Key Generator
vector<int> key_gen(int n)
{
    vector<int> key(2);
    int a, b;
    vector<int> Zn = Zestrella(n);

    a = Zn[rand() % Zn.size()];
    b = rand() % n;

    key[0] = a;
    key[1] = b;

    return key;
}

// Affine Cipher Enciphering
string encipher(string M, vector<int> K)
{
    string C = "";
    int n = alphabetVector.size();

    for (char mi : M)
    {
        auto codificated = alphabetMap.find(mi);

        if (codificated == alphabetMap.end())
        {
            return "There's a character that doesn't belong in the alphabet.";
        }

        int ci = ((K[0] * codificated->second) + K[1]) % n;

        C += alphabetVector[ci];
    }

    return C;
}

// Affine Cipher Deciphering
string decipher(string C, vector<int> K)
{
    string M = "";
    int n = alphabetVector.size();

    for (char ci : C)
    {
        auto decodificated = alphabetMap.find(ci);

        if (decodificated == alphabetMap.end())
        {
            return "There's a character that doesn't belong in the alphabet.";
        }

        int mi = (decodificated->second - K[1]) * find_b(n, K[0]);

        if (mi < 0)
        {
            mi = (mi % n + n) % n;
        }
        else
        {
            mi = mi % n;
        }

        M += alphabetVector[mi];
    }

    return M;
}

// Generate all possible keys
void gen_all_keys(int n, ofstream &outFile)
{
    vector<int> Zn = Zestrella(n);

    outFile << "All possible keys for n = " << n << ":\n";

    for (int a : Zn)
    {
        for (int b = 0; b < n; ++b)
        {
            outFile << "(" << a << ", " << b << ")\n";
            outFile << find_b(n, a) << " mod " << n << " = " << (find_b(n, a)) % n << "\n";
        }
    }
}

// Function for the Ciphering Person
void bob(int n)
{
    cout << "--- Ciphering ---\n";
    string M;
    cout << "Insert the plaintext: ";
    getline(cin, M);

    vector<int> K = key_gen(n);
    string C = encipher(M, K);

    ofstream keyFile("key.txt");
    if (!keyFile.is_open())
    {
        cerr << "Error: Could not open key.txt for writing.\n";
        return;
    }
    keyFile << K[0] << " " << K[1];
    keyFile.close();

    ofstream cipherFile("ciphertext.txt");
    if (!cipherFile.is_open())
    {
        cerr << "Error: Could not open ciphertext.txt for writing.\n";
        return;
    }
    cipherFile << C;
    cipherFile.close();

    cout << "\nPlaintext ciphered successfully." << endl;
    cout << "-> Key saved to key.txt" << endl;
    cout << "-> Ciphertext saved to ciphertext.txt" << endl;
    cout << "-----------------------\n\n";
}

// Function for the Deciphering Person
void alice(int n)
{
    cout << "--- Deciphering ---\n";
    vector<int> K(2);
    string C, M;

    ifstream keyFile("key.txt");
    if (!keyFile.is_open())
    {
        cerr << "Error: Could not find key.txt to read the key.\n";
        return;
    }
    keyFile >> K[0] >> K[1];
    keyFile.close();
    cout << "-> Key (" << K[0] << ", " << K[1] << ") read from key.txt" << endl;

    cout << "\nEnter the ciphered text to decipher: ";
    getline(cin, C);

    M = decipher(C, K);

    ofstream resultFile("deciphered_text.txt");
    if (!resultFile.is_open())
    {
        cerr << "Error: Could not open deciphered_text.txt for writing.\n";
        return;
    }
    resultFile << "Recovered Plaintext: " << M;
    resultFile.close();

    cout << "\nText deciphered successfully." << endl;
    cout << "-> Result saved to deciphered_text.txt" << endl;
    cout << "-------------------------\n";
}

int main()
{
    srand(time(0));

    fill_alphabet();

    ofstream possibleKeys;
    possibleKeys.open("possible_keys.txt");

    int n = alphabetVector.size();
    gen_all_keys(n, possibleKeys);

    // Ciphering Person
    bob(n);

    // Deciphering Person
    alice(n);

    return 0;
}
