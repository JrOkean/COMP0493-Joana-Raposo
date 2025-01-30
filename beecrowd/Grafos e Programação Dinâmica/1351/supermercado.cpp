#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

int main(){
    int M, N;
    while (cin >> M >> N && (M != 0 || N != 0)) {
        vector<int> lista_mrs_jones(M);
        for (int i = 0; i < M; i++) {
            cin >> lista_mrs_jones[i];
        }

        vector<pair<int, double>> produtos_supermercado(N);
        for (int i = 0; i < N; i++) {
            int K;
            double P;
            cin >> K >> P;
            produtos_supermercado[i] = {K, P};
        }

        vector<vector<double>> dp(M + 1, vector<double>(N + 1, numeric_limits<double>::infinity()));
        dp[0][0] = 0.0;

        for (int i = 0; i <= M; i++) {
            for (int j = 1; j <= N; j++) {
                if (i == 0) {
                    dp[i][j] = 0.0; // Custo para comprar 0 itens é 0
                } else {
                    dp[i][j] = dp[i][j - 1]; // Ignorar o produto j
                    if (lista_mrs_jones[i - 1] == produtos_supermercado[j - 1].first) {
                        dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + produtos_supermercado[j - 1].second);
                    }
                }
            }
        }

        double resultado = dp[M][N];
        if (resultado == numeric_limits<double>::infinity()) {
            cout << "Impossible" << endl;
        } else {
            cout << fixed << setprecision(2) << resultado << endl;
        }
    }
    return 0;
}