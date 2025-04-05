#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    
    bool operator < (const Point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

long long cross(const Point &O, const Point &A, const Point &B) {
    return (long long)(A.x - O.x) * (B.y - O.y) - (long long)(A.y - O.y) * (B.x - O.x);
}

vector<Point> convexHull(vector<Point> P) {
    int n = P.size(), k = 0;
    if (n <= 3) return P;
    
    vector<Point> H(2*n);
    
    sort(P.begin(), P.end());
    
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    
    for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    
    H.resize(k-1);
    return H;
}

int main() {
    int n;
    int testCase = 1;
    
    while (cin >> n && n != 0) {
        vector<Point> points;
        
        points.push_back(Point(0, 0));
        
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            points.push_back(Point(x, y));
        }
        
        vector<Point> hull = convexHull(points);
        
        cout << "Teste " << testCase++ << endl;
        cout << hull.size() << endl;
        cout << endl;
    }
    
    return 0;
}