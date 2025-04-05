#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
    
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

class DisjointSet {
private:
    vector<int> parent, rank;
    
public:
    DisjointSet(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return;
        
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            if (rank[rootX] == rank[rootY]) {
                rank[rootX]++;
            }
        }
    }
};

int kruskal(vector<Edge>& edges, int numVertices) {
    DisjointSet ds(numVertices);
    int totalCost = 0;
    int edgesAdded = 0;
    
    for (const Edge& edge : edges) {
        if (ds.find(edge.u) != ds.find(edge.v)) {
            ds.unite(edge.u, edge.v);
            totalCost += edge.w;
            edgesAdded++;
            
            if (edgesAdded == numVertices - 1) {
                break;
            }
        }
    }
    
    return totalCost;
}

int main() {
    int n;
    cin >> n;
    
    vector<Edge> edges(n);
    int maxVertex = 0;
    
    for (int i = 0; i < n; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        maxVertex = max(maxVertex, max(edges[i].u, edges[i].v));
    }
    
    // Para MST mínima: ordenar por peso crescente
    sort(edges.begin(), edges.end());
    int minCost = kruskal(edges, maxVertex);
    
    // Para MST máxima: ordenar por peso decrescente
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w > b.w;
    });
    int maxCost = kruskal(edges, maxVertex);
    
    cout << maxCost << endl;
    cout << minCost << endl;
    
    return 0;
}