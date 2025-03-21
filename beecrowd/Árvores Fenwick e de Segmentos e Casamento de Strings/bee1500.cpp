#include <bits/stdc++.h>
using namespace std;

struct FenwickTree {
    vector<long long> tree;
    int n;

    FenwickTree(int size) {
        n = size;
        tree.resize(n + 1, 0);
    }

    void update(int idx, long long val) {
        while (idx <= n) {
            tree[idx] += val;
            idx += idx & -idx;
        }
    }

    long long query(int idx) {
        long long res = 0;
        while (idx > 0) {
            res += tree[idx];
            idx -= idx & -idx;
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    while (T--) {
        int N, C;
        cin >> N >> C;

        FenwickTree bit1(N), bit2(N);

        while (C--) {
            int cmd;
            cin >> cmd;

            if (cmd == 0) {
                int p, q, v;
                cin >> p >> q >> v;

                // Atualiza a primeira Fenwick Tree
                bit1.update(p, v);
                bit1.update(q + 1, -v);

                // Atualiza a segunda Fenwick Tree
                bit2.update(p, 1LL * v * (p - 1));
                bit2.update(q + 1, -1LL * v * q);
            } else {
                int p, q;
                cin >> p >> q;

                // Calcula a soma até q
                long long sum_q = bit1.query(q) * q - bit2.query(q);
                // Calcula a soma até p-1
                long long sum_p_1 = (p > 1) ? (bit1.query(p - 1) * (p - 1) - bit2.query(p - 1)) : 0;

                // A soma do intervalo [p, q] é a diferença
                cout << (sum_q - sum_p_1) << '\n';
            }
        }
    }

    return 0;
}