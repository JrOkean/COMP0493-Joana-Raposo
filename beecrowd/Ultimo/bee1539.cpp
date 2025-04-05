#include <bits/stdc++.h>
using namespace std;

const double INF = 1e18;

struct Antenna {
    int x, y, r;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N;
    while (cin >> N && N != 0) {
        vector<Antenna> antennas(N);
        for (int i = 0; i < N; ++i) {
            int x, y, r;
            cin >> x >> y >> r;
            antennas[i] = {x, y, r};
        }

        vector<vector<pair<int, double>>> adj(N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == j) continue;
                int dx = antennas[i].x - antennas[j].x;
                int dy = antennas[i].y - antennas[j].y;
                double distance = sqrt(dx*dx + dy*dy);
                if (distance <= antennas[i].r) {
                    adj[i].emplace_back(j, distance);
                }
            }
        }

        int C;
        cin >> C;
        while (C--) {
            int A1, A2;
            cin >> A1 >> A2;
            A1--;
            A2--;
            
            if (A1 == A2) {
                cout << "0\n";
                continue;
            }

            vector<double> dist(N, INF);
            dist[A1] = 0.0;
            priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
            pq.push({0.0, A1});

            while (!pq.empty()) {
                auto current = pq.top();
                pq.pop();
                double d = current.first;
                int u = current.second;

                if (u == A2) break;
                if (d > dist[u]) continue;

                for (auto& edge : adj[u]) {
                    int v = edge.first;
                    double w = edge.second;
                    if (dist[v] > dist[u] + w) {
                        dist[v] = dist[u] + w;
                        pq.push({dist[v], v});
                    }
                }
            }

            if (dist[A2] == INF) {
                cout << "-1\n";
            } else {
                cout << (int)dist[A2] << "\n";
            }
        }
    }

    return 0;
}