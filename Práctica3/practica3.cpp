// Lab 03. Multiplicative Inverse
// By: López Reyes José Roberto, Hernández Zamora Alejandro and Hernández Gutiérrez Gerardo. 6CV4.

#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

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

// Pair generator for testing purposes
vector<int> gen_pairs()
{
    int a, b;

    do
    {
        a = rand() % 49 + 2;
        b = rand() % 49 + 2;
    } while (a < b);

    return {a, b};
}

int main()
{
    srand(time(0));

    vector<int> numbers;
    vector<int> res;

    for(int x = 0; x < 10; x++) {
        cout << "Iteration " << x + 1 << ".\n";

        numbers = gen_pairs();
        res = extendedEuclideanAlgorithm(numbers[0], numbers[1]);

        cout << "gcd(" << numbers[0] << ", " << numbers[1] << ") = " << res[0] << "\n";
        cout << "s = " << res[1] << "\n";
        cout << "t = " << res[2] << "\n";
    }

    return 0;
}
