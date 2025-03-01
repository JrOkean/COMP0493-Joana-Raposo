#include <iostream>
#include <algorithm>
using namespace std;

int _mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main(){
    int x, y, z;
    while(cin >> x >> y >> z){
        int triplo[3] = {x, y, z};
        sort(triplo, triplo + 3);

        int cateto1 = triplo[0];
        int cateto2 = triplo[1];
        int hipotenusa = triplo[2];
        
        string result;
        if(hipotenusa * hipotenusa == cateto1 * cateto1 + cateto2 * cateto2){
            result = "tripla pitagorica";

            int aux = _mdc(triplo[0], triplo[1]);
            int mdc = _mdc(aux, triplo[2]);
            if(mdc == 1) result = "tripla pitagorica primitiva";
        } else{
            result = "tripla";
        }
        cout << result << endl;
    }
    return 0;
}