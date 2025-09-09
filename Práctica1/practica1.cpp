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
void mulTable(int n) {
    if(n < 2 || n > 50) {
        cout << "Invalid value.\n";
        return; 
    }    

    cout << "Multiplication table for Z_" << n  << ":\n" << "*\t";

    for(int x = 1; x < n; x++) {
        cout << x << "\t";
    }

    cout << "\n";

    for(int x = 1; x < n; x++) {
        cout << x << "\t";
        for(int y = 1; y < n; y++) {
            cout << (x * y) % n << "\t";
        }
        cout << "\n";
    }
}

// Select a random even number 
int selectEven() {
    int x;

    x = (rand() % 25) * 2 + 2;

    return x;
}

// Select a random odd number 
int selectOdd() {
    int x;

    x = (rand() % 25) * 2 + 1;

    return x;
}

// Implementation of the Shift Cipher
string encipher(string M, int K){
    string C = "";
    int n = alphabetVector.size();

    for(char mi : M) {
        auto codificated = alphabetMap.find(mi);

        if(codificated == alphabetMap.end()) {
            return "There's a character that doesn't belong in the alphabet.";
        }

        int ci = (codificated->second + K) % n;

        C += alphabetVector[ci];
    }

    return C;
}

// Implementation of the Shift Decipher
string decipher(string C, int K){
    string M = "";
    int n = alphabetVector.size();

    for(char ci : C) {
        auto deciphered = alphabetMap.find(ci);

        if(deciphered == alphabetMap.end()) {
            return "There's a character that doesn't belong in the alphabet.";
        }

        int mi = 0;

        if((deciphered->second - K) < 0){
            mi = (n + (deciphered->second) - K) % n;
        } else {
            mi = (deciphered->second - K) % n;
        }        

        M += alphabetVector[mi];
    }

    return M;
}

int main() {
    srand(time(0));

    // Generating the random numbers to test the multiplication table
    int x = selectEven();
    int y = selectOdd();
    int z = primeNum.at(rand() % primeNum.size());

    // Generating three different tables
    mulTable(x);
    mulTable(y);
    mulTable(z);

    cout << "-----------------------\n";

    // Testing Ciphering and Deciphering

    // First C/D test: English Alphabet
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    for (int i=0; i<alphabet.size(); ++i) {
        alphabetVector.push_back(alphabet[i]);
        alphabetMap[alphabet[i]] = i;
    }

    string M = "SILVIA";
    int K = 14;

    string C = encipher(M, K);

    cout << "Plain Text: " << M << "\n";
    cout << "Key: " << K << "\n";
    cout << "Ciphered Text: " << C << "\n";

    cout << "-----------------------\n";

    string C2 = "GWZJWO";
    int K2 = 14;

    string M2 = decipher(C2, K2);
    
    cout << "Ciphered Text: " << C2 << "\n";
    cout << "Key: " << K2 << "\n";
    cout << "Decipheared Text: " << M2 << "\n";

    return 0;
}
