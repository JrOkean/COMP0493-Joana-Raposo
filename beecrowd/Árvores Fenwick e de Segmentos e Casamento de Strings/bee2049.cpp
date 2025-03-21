#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Função para implementar o algoritmo KMP (Knuth-Morris-Pratt)
vector<int> computeLPS(string pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    
    int len = 0;
    int i = 1;
    
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    return lps;
}

bool KMPSearch(string text, string pattern) {
    int n = text.size();
    int m = pattern.size();
    
    if (m == 0) return true;
    if (n < m) return false;
    
    vector<int> lps = computeLPS(pattern);
    
    int i = 0;
    int j = 0;
    
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        
        if (j == m) {
            return true;
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    return false;
}

int main() {
    int assinatura;
    int instancia = 1;
    bool primeiraInstancia = true; // Controle para a primeira instância
    
    while (cin >> assinatura) {
        if (assinatura == 0) break;
        
        // Adiciona linha em branco ANTES, exceto na primeira
        if (!primeiraInstancia) {
            cout << endl;
        } else {
            primeiraInstancia = false;
        }
        
        string painel;
        cin >> painel;
        
        string assinaturaStr = to_string(assinatura);
        
        cout << "Instancia " << instancia << endl;
        if (KMPSearch(painel, assinaturaStr)) {
            cout << "verdadeira" << endl;
        } else {
            cout << "falsa" << endl;
        }
        
        instancia++;
    }
    
    return 0;
}
