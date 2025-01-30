#include <iostream>
#include <set>
using namespace std;
 
int main() {
    int T, num_lamb, id_lamb;
    set<int> unique;
    
    cin >> T;
    for(int i = 0; i < T; i++){
        cin >> num_lamb;
        for(int l = 0; l < num_lamb; l++){
            cin >> id_lamb;
            unique.insert(id_lamb);
        };
        cout << unique.size() << endl;
        unique.clear();
    };
    
    return 0;
}