#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool coloration_solve(int Nt, vector<int>* matrix, const string& notas) {
    vector<int> color(Nt, -1); // -1: não visitado, 0: cor A, 1: cor B
    queue<int> q;

    for (int i = 0; i < Nt; i++) {
        if (color[i] == -1) {
            color[i] = (notas[i] == 'B') ? 1 : 0;
            q.push(i);

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : matrix[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        return false;
                    }
                }
            }
        }
    }

    return true; 
}

int main() {
    int Nt, Mb;

    while (cin >> Nt >> Mb) {
        vector<int> matrix[Nt];
        string notas;

        cin >> notas;

        for (int i = 0; i < Mb; i++) {
            int a, b;
            cin >> a >> b;
            a--; b--; 
            matrix[a].push_back(b);
            matrix[b].push_back(a);
        }

        cout << (coloration_solve(Nt, matrix, notas) ? "Y" : "N") << endl;
    }

    return 0;
}