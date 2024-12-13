#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct car {
    int id;     // ID do carro
    int h_in;  // Tempo de entrada
    int h_out;   // Tempo de saída
};

bool _can_park(int n, int k, vector<car> cars){
    stack<car> parking_lot;
    int curr_time;
    
    sort(cars.begin(), cars.end(), 
        [](const car& a, const car& b) { 
            return a.h_in < b.h_in; 
        }
    );
    
    for(const car& car : cars){
       while (!parking_lot.empty() && parking_lot.size() >= k) {
           
            if (parking_lot.top().h_out <= car.h_in) {
                parking_lot.pop();
            } else {
                return false;
            }
        }
        
        parking_lot.push(car);
    }
    
    return true;
}

int main() {
    int w_car, max_car;
    vector<car> p_lot;
    
    while (true) {
        cin >> w_car >> max_car;
        //parking lot
        //quebra a leitura de entrada
        if (w_car == 0 && max_car == 0) {
            break;
        };
        
        vector<car> cars(w_car);

        for (int i = 0; i < w_car; i++) {
            cars[i].id = i + 1;
            cin >> cars[i].h_in >> cars[i].h_out;
        }
        
        cout << (_can_park(w_car, max_car, cars) ? "Sim" : "Nao") << endl;
    }
    return 0;
}