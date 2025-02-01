#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int N, M;
    while (cin >> N >> M) {
        vector<pair<int, int>> promocoes(N);
        for (int i = 0; i < N; ++i) {
            cin >> promocoes[i].first >> promocoes[i].second;
        }
        
        // Inicializa a tabela dp com -1 (indicando que não é possível vender essa quantidade de latas)
        vector<int> dp(M + 1, -1);
        dp[0] = 0; // Base case: 0 latas vendidas, 0 reais arrecadados
        
        // Preenche a tabela dp
        for (const auto& promo : promocoes) {
            int Q = promo.first;
            int V = promo.second;
            for (int i = M; i >= Q; --i) {
                if (dp[i - Q] != -1) {
                    if (dp[i] == -1) {
                        dp[i] = dp[i - Q] + V;
                    } else {
                        dp[i] = max(dp[i], dp[i - Q] + V);
                    }
                }
            }
        }
        
        // Verifica se é possível vender exatamente M latas
        if (dp[M] != -1) {
            cout << dp[M] << endl;
        } else {
            cout << 0 << endl; // Se não for possível, a resposta é 0
        }
    }
    return 0;
}