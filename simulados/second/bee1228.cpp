#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    int N;
    while (cin >> N) {
        vector<int> started(N);
        for (int i = 0; i < N; i++) {
            cin >> started[i];
        }
        map<int, int> relation;
        for (int i = 0; i < N; i++) {
            int out_position;
            cin >> out_position;
            relation[out_position] = i;
        }
        int invertion = 0;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (relation[started[i]] > relation[started[j]]) {
                    invertion++;
                }
            }
        }
        cout << invertion << endl;
    }
    return 0;
}