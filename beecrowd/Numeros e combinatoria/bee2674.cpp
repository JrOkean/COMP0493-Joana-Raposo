#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const int MAX = pow(10, 5);

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;          // 2 e 3 são primos
    if (n % 2 == 0 || n % 3 == 0)     // Elimina pares e múltiplos de 3
        return false;
    
    // Verifica divisores de 5 até √n, alternando entre +2 e +4
    int i = 5;
    int w = 2;
    while (i * i <= n) {
        if (n % i == 0)
            return false;
        i += w;
        w = 6 - w;  // Alterna entre 2 e 4
    }
    return true;
}

int main() {
    int N;
    string result;
    while (cin >> N && N < MAX) {
        if (is_prime(N)) {
            result = "Primo";
            vector<int> numbers;
            int temp = N;
            while (temp > 0) {
                numbers.push_back(temp % 10);
                temp /= 10;                   
            }
            bool todos_digitos_primos = true;
            for (size_t i = 0; i < numbers.size(); i++){
                if(!is_prime(numbers[i])) {
                    todos_digitos_primos = false;
                    break;
                }
            }
            if (todos_digitos_primos) {
                result = "Super";
            }
        } else {
            result = "Nada";
        }
        cout << result << endl;
    }
    return 0;
}