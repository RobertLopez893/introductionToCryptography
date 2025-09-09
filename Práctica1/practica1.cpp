// Lab 01. Modular Arithmetic
// By: López Reyes José Roberto. 6CV2.

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;

vector<int> primeNum = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 37, 43, 47};
vector<char> alphabetVector;
map<char, int> alphabetMap;

// Function that prints the Multiplication Table
void mulTable(int n)
{
    if (n < 2 || n > 50)
    {
        cout << "Invalid value.\n";
        return;
    }

    cout << "Multiplication table for Z_" << n << ":\n"
         << "*\t";

    for (int x = 1; x < n; x++)
    {
        cout << x << "\t";
    }

    cout << "\n";

    for (int x = 1; x < n; x++)
    {
        cout << x << "\t";
        for (int y = 1; y < n; y++)
        {
            cout << (x * y) % n << "\t";
        }
        cout << "\n";
    }
}

// Select a random even number
int selectEven()
{
    int x;

    x = (rand() % 25) * 2 + 2;

    return x;
}

// Select a random odd number
int selectOdd()
{
    int x;

    x = (rand() % 25) * 2 + 1;

    return x;
}

// Implementation of the Shift Cipher
string encipher(string M, int K)
{
    string C = "";
    int n = alphabetVector.size();

    if (K > alphabetVector.size())
    {
        return "The key can't be greather than Zn.";
    }

    for (char mi : M)
    {
        auto codificated = alphabetMap.find(mi);

        if (codificated == alphabetMap.end())
        {
            return "There's a character that doesn't belong in the alphabet.";
        }

        int ci = (codificated->second + K) % n;

        C += alphabetVector[ci];
    }

    return C;
}

// Implementation of the Shift Decipher
string decipher(string C, int K)
{
    string M = "";
    int n = alphabetVector.size();

    if (K > alphabetVector.size())
    {
        return "The key can't be greather than Zn.";
    }

    for (char ci : C)
    {
        auto deciphered = alphabetMap.find(ci);

        if (deciphered == alphabetMap.end())
        {
            return "There's a character that doesn't belong in the alphabet.";
        }

        int mi = 0;

        if ((deciphered->second - K) < 0)
        {
            mi = (n + (deciphered->second) - K) % n;
        }
        else
        {
            mi = (deciphered->second - K) % n;
        }

        M += alphabetVector[mi];
    }

    return M;
}

// English Alphabet Test
void testEnglishAlphabet()
{
    alphabetVector.clear();
    alphabetMap.clear();

    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < alphabet.size(); i++)
    {
        alphabetVector.push_back(alphabet[i]);
        alphabetMap[alphabet[i]] = i;
    }

    string M, C;
    int K;

    cout << "Please insert your plaintext: ";
    getline(cin, M);

    cout << "Please insert your key: ";
    cin >> K;

    C = encipher(M, K);
    cout << "Plain Text: " << M << "\nKey: " << K << "\nCiphered Text: " << C << "\n";

    cin.ignore();
    cout << "Please insert your ciphered text: ";
    getline(cin, C);

    M = decipher(C, K);
    cout << "Ciphered Text: " << C << "\nKey: " << K << "\nDeciphered Text: " << M << "\n";
    cout << "-----------------------\n";
}

// Printable ASCII Alphabet
void testASCIIAlphabet()
{
    alphabetVector.clear();
    alphabetMap.clear();

    for (int i = 32; i < 127; i++)
    {
        alphabetVector.push_back((char)i);
        alphabetMap[(char)i] = alphabetVector.size() - 1;
    }

    string M, C;
    int K;

    cout << "Please insert your plaintext: ";
    getline(cin, M);

    cout << "Please insert your key: ";
    cin >> K;

    C = encipher(M, K);
    cout << "Plain Text: " << M << "\nKey: " << K << "\nCiphered Text: " << C << "\n";

    cin.ignore();
    cout << "Please insert your ciphered text: ";
    getline(cin, C);

    M = decipher(C, K);
    cout << "Ciphered Text: " << C << "\nKey: " << K << "\nDeciphered Text: " << M << "\n";
    cout << "-----------------------\n";
}

// Random Alphabet Test
void testRandomAlphabet()
{
    alphabetVector.clear();
    alphabetMap.clear();

    int n;
    cout << "Please insert your desired alphabet size: ";
    cin >> n;
    cout << "\n";

    char r;
    for (int i = 0; i < n; i++)
    {
        do
        {
            r = (char)(rand() % (127 - 32 + 1) + 32);
        } while (alphabetMap.find(r) != alphabetMap.end());

        alphabetVector.push_back(r);
        alphabetMap[r] = alphabetVector.size() - 1;
    }

    cout << "Alphabet: ";
    for (auto c : alphabetVector)
        cout << c;
    cout << "\n-----------------------\n";

    cin.ignore();
    string M, C;
    int K;

    cout << "Please insert your plaintext: ";
    getline(cin, M);

    cout << "Please insert your key: ";
    cin >> K;

    C = encipher(M, K);
    cout << "Plain Text: " << M << "\nKey: " << K << "\nCiphered Text: " << C << "\n";

    cin.ignore();
    cout << "Please insert your ciphered text: ";
    getline(cin, C);

    M = decipher(C, K);
    cout << "Ciphered Text: " << C << "\nKey: " << K << "\nDeciphered Text: " << M << "\n";
    cout << "-----------------------\n";
}

int main()
{
    srand(time(0));

    // Multiplication Tables
    mulTable(selectEven());
    mulTable(selectOdd());
    mulTable(primeNum[rand() % primeNum.size()]);

    cout << "-----------------------\n";

    // Run all tests
    testEnglishAlphabet();
    testASCIIAlphabet();
    testRandomAlphabet();

    return 0;
}
