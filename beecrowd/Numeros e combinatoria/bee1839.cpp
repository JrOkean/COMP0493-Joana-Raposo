#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MOD = 1000000007;
const int MAXK = 2500; // 50x50 = 2500

long long fact[MAXK + 1];
long long inv_fact[MAXK + 1];

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
    for (int i = 1; i <= MAXK; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    inv_fact[MAXK] = pow_mod(fact[MAXK], MOD - 2, MOD);
    for (int i = MAXK - 1; i >= 0; --i) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
}

int main() {
    precompute();

    int N, M;
    cin >> N >> M;
    vector<string> grid(N);
    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
    }

    // Construir a matriz de soma acumulada
    vector<vector<int>> sum(N + 1, vector<int>(M + 1, 0));
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (grid[i - 1][j - 1] == '#');
        }
    }

    int xA, yA, xB, yB;
    while (cin >> xA >> yA >> xB >> yB) {
        // Converter para índices 0-based
        int x1 = xA - 1;
        int y1 = yA - 1;
        int x2 = xB - 1;
        int y2 = yB - 1;

        // Calcular o número de células na região
        int numRows = x2 - x1 + 1;
        int numCols = y2 - y1 + 1;
        int k = numRows * numCols;

        // Calcular o número de paredes na região
        int s = sum[x2 + 1][y2 + 1] - sum[x1][y2 + 1] - sum[x2 + 1][y1] + sum[x1][y1];

        if (s < 0 || s > k) {
            cout << 0 << endl;
        } else {
            long long ans = fact[k];
            ans = ans * inv_fact[s] % MOD;
            ans = ans * inv_fact[k - s] % MOD;
            cout << ans << endl;
        }
    }

    return 0;
}