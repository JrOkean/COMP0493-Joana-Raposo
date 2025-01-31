#include <iostream>
using namespace std;

bool subset_verification(int bridges_value, int* graus, int regions) {
    bool* dp = new bool[bridges_value + 1];
    for (int i = 0; i <= bridges_value; ++i) {
        dp[i] = false;
    }
    dp[0] = true;

    for (int i = 1; i <= regions; ++i) {
        for (int j = bridges_value; j >= graus[i]; --j) {
            if (dp[j - graus[i]]) {
                dp[j] = true;
            }
        }
    }

    bool result = dp[bridges_value];
    delete[] dp;
    return result;
}

int main() {
    int bridges, regions;

    while (cin >> regions >> bridges) {
        int** matrix = new int*[regions + 1];
        for (int i = 0; i <= regions; ++i) {
            matrix[i] = new int[regions + 1];
            for (int j = 0; j <= regions; ++j) {
                matrix[i][j] = 0;
            }
        }

        for (int i = 0; i < bridges; ++i) {
            int A, B;
            cin >> A >> B;
            matrix[A][B] += 1;
            matrix[B][A] += 1;
        }

        int* graus = new int[regions + 1];
        for (int i = 1; i <= regions; ++i) {
            graus[i] = 0;
            for (int j = 1; j <= regions; ++j) {
                graus[i] += matrix[i][j];
            }
        }

        if (subset_verification(bridges, graus, regions)) {
            cout << "S" << endl;
        } else {
            cout << "N" << endl;
        }

        for (int i = 0; i <= regions; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        delete[] graus;
    }

    return 0;
}