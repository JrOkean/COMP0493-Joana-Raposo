#include <iostream>
#include <string>
using namespace std;

const int MOD = 1000000007;
const int MAX = 1000;

long long fact[MAX + 1];
long long inv_fact[MAX + 1];

long long pow_mod(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    inv_fact[MAX] = pow_mod(fact[MAX], MOD - 2, MOD);
    for (int i = MAX - 1; i >= 0; --i) {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;
    }
}

int main() {
    precompute();
    string word;
    while (cin >> word) {
        int counts[26] = {0};
        for (char c : word) {
            counts[c - 'A']++;
        }
        long long res = fact[word.size()];
        for (int i = 0; i < 26; ++i) {
            if (counts[i] > 0) {
                res = (res * inv_fact[counts[i]]) % MOD;
            }
        }
        cout << res << endl;
    }
    return 0;
}