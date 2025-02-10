#include <iostream>
#include <vector>

using namespace std;

int main(){
    int J, R;

    cin >> J >> R;
    vector<int> game_points(J);

    for (size_t r = 0; r < R; r++){
        for (size_t i = 0; i < J; i++){
            int value;
            cin >> value;
            game_points[i] += value;
        } 
    }
    
    /*
    for (size_t i = 0; i < J; i++){
        cout << game_points[i] << endl;
    }
    */
    

    int maior = game_points[0];
    int index = 0;
    for (int i = 1; i < J; i++) {
        if (game_points[i] >= maior) { 
            maior = game_points[i];
            index = i;
        }
    }
    cout << index + 1 << endl;
    return 0;
}