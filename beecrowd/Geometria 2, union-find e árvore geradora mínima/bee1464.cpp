#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    
    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }
};

int cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convexHull(vector<Point>& points) {
    int n = points.size();
    if (n <= 3) return points;
    
    int lowestPoint = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[lowestPoint].y || 
            (points[i].y == points[lowestPoint].y && points[i].x < points[lowestPoint].x)) {
            lowestPoint = i;
        }
    }
    
    swap(points[0], points[lowestPoint]);
    
    Point p0 = points[0];
    
    sort(points.begin() + 1, points.end(), [&p0](const Point& a, const Point& b) {
        int o = cross(p0, a, b);
        if (o == 0) { 
            return (a.x - p0.x) * (a.x - p0.x) + (a.y - p0.y) * (a.y - p0.y) < 
                   (b.x - p0.x) * (b.x - p0.x) + (b.y - p0.y) * (b.y - p0.y);
        }
        return o > 0;
    });
    
    vector<Point> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    
    for (int i = 2; i < n; i++) {
        while (hull.size() > 1 && cross(hull[hull.size()-2], hull[hull.size()-1], points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    
    return hull;
}

int countLayers(vector<Point> points) {
    int layers = 0;
    
    while (points.size() >= 3) {
        vector<Point> hull = convexHull(points);
        layers++;
        
        vector<Point> remainingPoints;
        for (const Point& p : points) {
            bool inHull = false;
            for (const Point& h : hull) {
                if (p == h) {
                    inHull = true;
                    break;
                }
            }
            if (!inHull) {
                remainingPoints.push_back(p);
            }
        }
        
        points = remainingPoints;
    }
    
    return layers;
}

int main() {
    int n;
    
    while (cin >> n && n != 0) {
        vector<Point> points;
        
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            points.push_back(Point(x, y));
        }
        
        int layers = countLayers(points);
        
        if (layers % 2 == 1) {
            cout << "Take this onion to the lab!" << endl;
        } else {
            cout << "Do not take this onion to the lab!" << endl;
        }
    }
    
    return 0;
}