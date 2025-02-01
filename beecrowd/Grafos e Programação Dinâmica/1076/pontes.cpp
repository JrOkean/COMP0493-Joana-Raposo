#include <iostream>
#include <vector>

using namespace std;

int main() {
    int Nt, Mb;

    while (cin >> Nt >> Mb) {
        vector<int> adjacency_list[Nt]; // Lista de adjacência para o grafo
        vector<char> initial_notes(Nt); // Vetor para armazenar as notas iniciais

        // Lê as notas iniciais das torres
        for (int i = 0; i < Nt; i++) {
            cin >> initial_notes[i];
        }

        // Lê as pontes (arestas) e constrói o grafo
        for (int i = 0; i < Mb; i++) {
            int tower_a, tower_b;
            cin >> tower_a >> tower_b;
            tower_a--; tower_b--; // Ajusta para índice 0-based
            adjacency_list[tower_a].push_back(tower_b);
            adjacency_list[tower_b].push_back(tower_a);
        }

        // Conta o número de torres que começam com B
        int count_B = 0;
        for (int i = 0; i < Nt; i++) {
            if (initial_notes[i] == 'B') {
                count_B++;
            }
        }

        // Verifica se é possível ajustar todas as torres para A
        if (count_B % 2 == 0) {
            cout << "Y" << endl;
        } else {
            cout << "N" << endl;
        }
    }

    return 0;
}