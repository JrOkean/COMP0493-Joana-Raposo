#include <iostream>
#include <vector>

using namespace std;

struct point{
    int x, y;
};

int main(){
    while (true) {
        int set_points;
        cin >> set_points;
        
        if (set_points == 0) {
            break;
        };
        
        vector<point> m_point;
        
        // Leitura dos N pontos
        for (int i = 0; i < set_points; i++) {
            point p;
            cin >> p.x >> p.y;
            m_point.push_back(p);
        }

        
        
        // Aqui você pode processar os pontos conforme necessário
        // Por exemplo, imprimir os pontos lidos:
        cout << "Caso de teste com " << N << " pontos:" << endl;
        for (const Ponto& p : pontos) {
            cout << "X: " << p.x << ", Y: " << p.y << endl;
        }
        cout << endl;
    }
    return 0;
}