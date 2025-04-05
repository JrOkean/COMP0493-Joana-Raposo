#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    double m1, m2, m3;
    while (cin >> m1 >> m2 >> m3) {
        // Verifica se todas as medianas são positivas
        if (m1 <= 0 || m2 <= 0 || m3 <= 0) {
            cout << "-1.000" << endl;
            continue;
        }
        // Verifica as desigualdades triangulares
        if ((m1 + m2 > m3) && (m1 + m3 > m2) && (m2 + m3 > m1)) {
            double s = (m1 + m2 + m3) / 2.0;
            double area_med = sqrt(s * (s - m1) * (s - m2) * (s - m3));
            double area_tri = (4.0 / 3.0) * area_med;
            cout << fixed << setprecision(3) << area_tri << endl;
        } else {
            cout << "-1.000" << endl;
        }
    }
    return 0;
}