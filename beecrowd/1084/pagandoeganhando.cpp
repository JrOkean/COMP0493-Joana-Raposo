#include <iostream>
#include <vector>
using namespace std;

int main(){
    while (true){
        int N, D;
        vector<int> number;

        cin >> N >> D;

        if (N == 0 && D == 0){
            break;
        };

        vector<int> numero(N);
        for (int i = 0; i < N; i++) {
            cin >> numero[i];
        }

        int restantes = N - D;
        vector<int> resultado;
        int inicio = 0;

        for (int i = 0; i < restantes; i++) {
            int maxElemento = -1;
            int maxIndice = inicio;

            for (int j = inicio; j <= N - (restantes - i); j++) {
                if (numero[j] > maxElemento) {
                    maxElemento = numero[j];
                    maxIndice = j;
                }
            }

            resultado.push_back(maxElemento);
            inicio = maxIndice + 1;
        }

        for (int x : resultado) {
            cout << x;
        }
        cout << endl;
    }
    return 0;
}