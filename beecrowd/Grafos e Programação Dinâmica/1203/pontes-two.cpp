#include <iostream>
#include <vector>

using namespace std;

// K pontes (edges), R regions (vertex).
// g(K) == 2 (porque liga EXATAMENTE duas regiões).

bool subset_verification(int bridges_value, vector<int>& graus) {
    vector<bool> dp( + 1, false);
    dp[0] = true;

    for (int grau : graus) {
        for (int i = bridges_value; i >= grau; --i) {
            if (dp[i - grau]) {
                dp[i] = true;
            }
        }
    }

    return dp[bridges_value];
}

int main(){
    int bridges,  regions;

    while(cin >> regions >> bridges){
        vector<vector<int>> matrix(regions + 1, vector<int>(regions + 1, 0));
        for (size_t i = 0; i < bridges; i++){
            int A, B;
            cin >> A >> B;
            matrix[A][B] += 1;
            matrix[A][B] += 1;
        }

        vector<int> graus(regions+1, 0);
        for (size_t i = 1; i <= regions; i++){
            for (size_t j = 1; j <= regions; j++){
                graus[i] += matrix[i][j];
            }
        }
        
        if (subset_verification(bridges, graus)){
            cout << "S" << endl;
        } else{
            cout << "N" << endl;
        }
    }
    return 0;
}