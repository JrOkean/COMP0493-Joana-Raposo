#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
private:
    vector<long long> bit;
    int size;

public:
    FenwickTree(int n) {
        size = n;
        bit.assign(n + 1, 0);
    }

    void update(int idx, long long val) {
        while (idx <= size) {
            bit[idx] += val;
            idx += (idx & -idx);
        }
    }

    long long query(int idx) {
        long long sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }

    long long query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    int n;
    cin >> n;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    FenwickTree ft1(n);
    FenwickTree ft2(n);
    FenwickTree ft3(n);
    
    long long result = 0;
    
    for (int i = n; i >= 1; i--) {
        
        long long smaller_right = ft1.query(a[i] - 1);
        
        long long inversions_right = ft2.query(a[i] - 1);
        
        result += inversions_right;
        
        ft1.update(a[i], 1);
        
        ft2.update(a[i], smaller_right);
        
        ft3.update(a[i], inversions_right);
    }
    
    cout << result << endl;
    
    return 0;
}