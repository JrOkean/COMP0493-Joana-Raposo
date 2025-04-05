#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

vector<int> dijkstra(int start, const vector<vector<pair<int, int>>>& adj) {
    int n = adj.size();
    vector<int> dist(n, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M;
    while (cin >> N >> M && (N || M)) {
        int S, D;
        cin >> S >> D;
        
        vector<vector<pair<int, int>>> adj_forward(N);
        vector<vector<pair<int, int>>> adj_reversed(N);
        vector<tuple<int, int, int>> edges;
        
        for (int i = 0; i < M; ++i) {
            int u, v, p;
            cin >> u >> v >> p;
            adj_forward[u].emplace_back(v, p);
            adj_reversed[v].emplace_back(u, p);
            edges.emplace_back(u, v, p);
        }
        
        vector<int> dist_S = dijkstra(S, adj_forward);
        vector<int> dist_revD = dijkstra(D, adj_reversed);
        
        if (dist_S[D] == INF) {
            cout << -1 << '\n';
            continue;
        }
        
        vector<vector<pair<int, int>>> adj_modified(N);
        for (const auto& edge : edges) {
            int u = get<0>(edge);
            int v = get<1>(edge);
            int p = get<2>(edge);
            
            bool forbidden = false;
            if (dist_S[u] != INF && dist_revD[v] != INF) {
                if (dist_S[u] + p + dist_revD[v] == dist_S[D]) {
                    forbidden = true;
                }
            }
            
            if (!forbidden) {
                adj_modified[u].emplace_back(v, p);
            }
        }
        
        vector<int> new_dist = dijkstra(S, adj_modified);
        if (new_dist[D] == INF) {
            cout << -1 << '\n';
        } else {
            cout << new_dist[D] << '\n';
        }
    }
    
    return 0;
}