// Lab 02. Affine Cipher
// By: López Reyes José Roberto. 6CV4.

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <numeric>
#include <algorithm>

using namespace std;

vector<char> alfabetoActual;
map<char, int> alphabetMap;
int n, tamAlfa;

// Fills with the ASCII characters manually
void fill_alphabet()
{
    for (int i = 32; i <= 126; ++i)
        alfabetoActual.push_back(static_cast<char>(i));
    tamAlfa = 95;
}

// Greatest Common Divisor
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
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
    for (int a = 1; a < n; a++)
    {
        if (gcd(a, n) == 1)
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

    if (n < 2 || find(Zn.begin(), Zn.end(),a) == Zn.end())
    {
        cout << "\nAn error occured that can't let the program continue.\n";
        return -1;
    }

    for(int i = 0; i < Zn.size(); i++) {
        if(((a * Zn[i]) % n) == 1) {
            b = Zn[i];
            break;
        }
    }

    return b;
}

int main()
{
    fill_alphabet();
    n = 27;

    vector<int> Zn = Zestrella(n);

    cout << "Z*" << n << ": ";

    for (int i = 0; i < Zn.size(); i++)
        cout << Zn[i] << "\t";
    
    int a = 2;
    int b = find_b(n, a);
    cout << "\nThe b for " << a << " is " << b;

    return 0;
}
