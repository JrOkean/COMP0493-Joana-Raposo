#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    while (cin >> N, N != 0) {
        vector<string> palavras(N);
        for (int i = 0; i < N; ++i) {
            cin >> palavras[i];
        }

        sort(palavras.begin(), palavras.end());

        bool ruim = false;
        for (int i = 0; i < N - 1; ++i) {
            const string &a = palavras[i];
            const string &b = palavras[i+1];
            if (b.size() >= a.size() && b.compare(0, a.size(), a) == 0) {
                ruim = true;
                break;
            }
        }

        cout << (ruim ? "Conjunto Ruim" : "Conjunto Bom") << '\n';
    }

    return 0;
}