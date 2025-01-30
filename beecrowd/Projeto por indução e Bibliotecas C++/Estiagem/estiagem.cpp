#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <iomanip>
#include <cassert>

using namespace std;

float truncate(float value) {
    return floorf(value * 100) / 100;
}

int main() {
    //size_t para garantir positividade do tipo de dado
    size_t N;
    cin >> N;

    int city = 0;

    while (N != 0) {
        cout << "Cidade# " << ++city << ":\n";

        int people = 0, t_waste = 0;
        vector<int> indices;
        map<int, int> waste_to_people;

        int X = 1, Y = 1; // # of moradores, gasto total
        for (int idx = 0; idx < N; idx += 1) {
            cin >> X
                >> Y;
            people += X;
            t_waste += Y;
            waste_to_people[Y/X] =  waste_to_people[Y/X] + X;

        }
        for (auto it = waste_to_people.begin(); it != waste_to_people.end(); ++it) {
            cout << it->second << '-' << it->first;
            if (next(it) != waste_to_people.end()) {
                cout << " ";
            }
        }

        cout << "\nConsumo medio: ";
        cout << fixed << setprecision(2) << truncate((float(t_waste)/people));
        cout << " m3." << "\n";
           
        cin >> N;
        if (N != 0) {
            cout << "\n";
        }

    }
    return 0;
}