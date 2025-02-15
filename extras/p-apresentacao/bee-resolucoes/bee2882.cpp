#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge {
    int to, rev;
    long long cap;
    Edge(int t, int r, long long c) : to(t), rev(r), cap(c) {}
};

class Dinic {
public:
    vector<vector<Edge>> graph;
    vector<int> level, iter;
    
    Dinic(int n) : graph(n), level(n), iter(n) {}
    
    void add_edge(int from, int to, long long cap) {
        graph[from].emplace_back(to, graph[to].size(), cap);
        graph[to].emplace_back(from, graph[from].size() - 1, 0);
    }
    
    void bfs(int s) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (Edge &e : graph[v]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    
    long long dfs(int v, int t, long long f) {
        if (v == t) return f;
        for (int &i = iter[v]; i < graph[v].size(); ++i) {
            Edge &e = graph[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                long long d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    
    long long max_flow(int s, int t) {
        long long flow = 0;
        while (true) {
            bfs(s);
            if (level[t] == -1) return flow;
            fill(iter.begin(), iter.end(), 0);
            long long f;
            while ((f = dfs(s, t, LLONG_MAX)) > 0) {
                flow += f;
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int P, R, C;
    while (cin >> P >> R >> C) {
        if (P == 0 && R == 0 && C == 0) break;
        
        vector<int> D(P), E(R);
        for (int i = 0; i < P; ++i) cin >> D[i];
        for (int i = 0; i < R; ++i) cin >> E[i];
        
        vector<tuple<int, int, int>> connections;
        vector<bool> has_connection(P + 1, false); // 1-based
        
        for (int i = 0; i < C; ++i) {
            int I, J, T;
            cin >> I >> J >> T;
            connections.emplace_back(T, J-1, I-1); // T, refinery (0-based), post (0-based)
            has_connection[I] = true;
        }
        
        // Pre-check: sum of demands and supplies
        long long sum_D = 0, sum_E = 0;
        for (int d : D) sum_D += d;
        for (int e : E) sum_E += e;
        if (sum_D > sum_E) {
            cout << -1 << '\n';
            continue;
        }
        
        // Check if all gas stations have at least one connection
        bool possible = true;
        for (int i = 1; i <= P; ++i) {
            if (!has_connection[i]) {
                possible = false;
                break;
            }
        }
        if (!possible) {
            cout << -1 << '\n';
            continue;
        }
        
        // Collect and sort Ts
        vector<int> Ts;
        for (auto &conn : connections) {
            Ts.push_back(get<0>(conn));
        }
        sort(Ts.begin(), Ts.end());
        Ts.erase(unique(Ts.begin(), Ts.end()), Ts.end());
        
        if (Ts.empty()) {
            cout << -1 << '\n';
            continue;
        }
        
        // Sort connections by T
        sort(connections.begin(), connections.end());
        
        // Binary search on Ts
        int low = 0, high = Ts.size() - 1;
        int answer = -1;
        while (low <= high) {
            int mid = (low + high) / 2;
            int T_val = Ts[mid];
            
            // Build the graph
            int source = 0;
            int sink = R + P + 1;
            Dinic din(sink + 1);
            
            // Source to refineries
            for (int j = 0; j < R; ++j) {
                din.add_edge(source, j + 1, E[j]);
            }
            
            // Refineries to gas stations (connections with T <= T_val)
            for (auto &conn : connections) {
                int T = get<0>(conn);
                if (T > T_val) break;
                int refinery = get<1>(conn) + 1; // 1-based in graph
                int post = R + 1 + get<2>(conn); // 1-based after R
                din.add_edge(refinery, post, 1e18);
            }
            
            // Gas stations to sink
            for (int i = 0; i < P; ++i) {
                int post = R + 1 + i;
                din.add_edge(post, sink, D[i]);
            }
            
            // Compute max flow
            long long flow = din.max_flow(source, sink);
            if (flow == sum_D) {
                answer = T_val;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        cout << (answer != -1 ? answer : -1) << '\n';
    }
    
    return 0;
}