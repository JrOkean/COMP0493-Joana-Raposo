#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <climits>

using namespace std;

struct Edge {
    int to, rev, cap;
    Edge(int t, int r, int c) : to(t), rev(r), cap(c) {}
};

class EdmondsKarp {
private:
    vector<vector<Edge>> graph;
    vector<int> parent;

    bool bfs(int source, int sink) {
        fill(parent.begin(), parent.end(), -1);
        parent[source] = source;
        queue<int> q;
        q.push(source);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (Edge &e : graph[u]) {
                if (parent[e.to] == -1 && e.cap > 0) {
                    parent[e.to] = u;
                    if (e.to == sink)
                        return true;
                    q.push(e.to);
                }
            }
        }
        return false;
    }

public:
    EdmondsKarp(int n) {
        graph.resize(n);
        parent.resize(n);
    }

    void addEdge(int from, int to, int cap) {
        graph[from].emplace_back(to, graph[to].size(), cap);
        graph[to].emplace_back(from, graph[from].size() - 1, 0);
    }

    int maxFlow(int source, int sink) {
        int flow = 0;
        while (bfs(source, sink)) {
            int path_flow = INT_MAX;
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                for (Edge &e : graph[u]) {
                    if (e.to == v && e.cap > 0) {
                        path_flow = min(path_flow, e.cap);
                        break;
                    }
                }
            }
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                for (Edge &e : graph[u]) {
                    if (e.to == v && e.cap > 0) {
                        e.cap -= path_flow;
                        graph[v][e.rev].cap += path_flow;
                        break;
                    }
                }
            }
            flow += path_flow;
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    map<string, int> sizeToNode = {
        {"XXL", 1}, {"XL", 2}, {"L", 3}, {"M", 4}, {"S", 5}, {"XS", 6}
    };

    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;

        int K = N / 6;
        vector<pair<int, int>> volunteers(M);

        for (int i = 0; i < M; ++i) {
            string s1, s2;
            cin >> s1 >> s2;
            volunteers[i] = {sizeToNode[s1], sizeToNode[s2]};
        }

        int source = 0;
        int sink = 7 + M;
        int totalNodes = 7 + M + 1;
        EdmondsKarp ek(totalNodes);

        // Source to shirt sizes
        for (int shirt = 1; shirt <= 6; ++shirt)
            ek.addEdge(source, shirt, K);

        // Volunteers to sink and shirts to volunteers
        for (int i = 0; i < M; ++i) {
            int volunteerNode = 7 + i;
            ek.addEdge(volunteerNode, sink, 1);

            int s1 = volunteers[i].first;
            int s2 = volunteers[i].second;
            ek.addEdge(s1, volunteerNode, 1);
            ek.addEdge(s2, volunteerNode, 1);
        }

        int maxFlow = ek.maxFlow(source, sink);
        cout << (maxFlow == M ? "YES" : "NO") << "\n";
    }

    return 0;
}