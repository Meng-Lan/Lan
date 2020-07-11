#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int main() {
    vector<vector<pair<int, int> > > G(26);
    FILE *f = fopen("graph.txt", "rb");
    int p, q, d;
    while (fscanf(f, "%d%d%d", &p, &q, &d) != EOF) {
        --p; --q;
        G[p].push_back(make_pair(q, d));
        G[q].push_back(make_pair(p, d));
    }
    fclose(f);
    srand(time(nullptr));
    int K = rand() % 10 + 3;
    vector<vector<int> > sets(K);
    vector<int> point2set(26, -1);
    for (int i = 0; i < K; ++i) {
        p = rand() % 26;
        if (point2set[p] != -1) {
            for (int q = p; q < 26; ++q) {
                if (point2set[q] == -1) {
                    p = q;
                }
            }
        }
        if (point2set[p] != -1) {
            for (int q = p; q >= 0; --q) {
                if (point2set[q] == -1) {
                    p = q;
                }
            }
        }
        point2set[p] = i;
        sets[i].push_back(p);
    }
    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = 0; i < K; ++i) {
            for (auto p : sets[i]) {
                for (auto e : G[p]) {
                    q = e.first;
                    if (point2set[q] == -1) {
                        flag = true;
                        cout << (p+1) << " " << (q+1) << endl;
                        point2set[q] = i;
                        sets[i].push_back(q);
                    }
                }
            }
        }
    }
    for (int i = 0; i < K; ++i) {
        cout << "Points in Set #" << (i+1) << " : ";
        for (auto p : sets[i]) {
            cout << (p+1) << " ";
        }
        cout << endl;
    }
    return 0;
}