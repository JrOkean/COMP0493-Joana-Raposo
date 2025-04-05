#include <iostream>
#include <vector>
using namespace std;

class GuildSystem {
private:
    vector<int> parent;  
    vector<int> size;    
    vector<int> points;  
    vector<int> playerPoints; 

public:
    GuildSystem(int n, vector<int>& p) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        points.resize(n + 1);
        playerPoints = p;  
        
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            points[i] = p[i-1];
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        
        if (rootA == rootB) return;  
        
        if (size[rootA] < size[rootB]) {
            parent[rootA] = rootB;
            size[rootB] += size[rootA];
            points[rootB] += points[rootA];
        } else {
            parent[rootB] = rootA;
            size[rootA] += size[rootB];
            points[rootA] += points[rootB];
        }
    }
    
    int battle(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        
        if (rootA == rootB) return 0;
        
        if (points[rootA] > points[rootB]) return 1;
        if (points[rootA] < points[rootB]) return 2;
        return 0;
    }
};

int main() {
    int n, m;
    
    while (cin >> n >> m && (n != 0 || m != 0)) {
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }
        
        GuildSystem gs(n, p);
        int victories = 0;
        
        for (int i = 0; i < m; i++) {
            int q, a, b;
            cin >> q >> a >> b;
            
            if (q == 1) {
                gs.unite(a, b);
            } else {
                int result = gs.battle(a, b);
                
                if ((gs.find(1) == gs.find(a) && result == 1) || 
                    (gs.find(1) == gs.find(b) && result == 2)) {
                    victories++;
                }
            }
        }
        
        cout << victories << endl;
    }
    
    return 0;
}