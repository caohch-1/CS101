#include <iostream>

using namespace std;
const int MK = 50000;
const int V = 25000;
const int MAX_WEIGHT = 20000;

struct Edge {
    int start = 0, end = 0, weight = 0;
};


class Graph {
public:
    Edge edges[MK];
    int E_num = 0;
    int V_num = 0;
    int dis_matrix[100][100];
    int dis[V]{};

    void set_v(int v) {
        this->V_num = v;
//        dis_matrix = new int* [V_num + 1];
//        for (int i = 0; i < V_num + 1; ++i) {
//            dis_matrix[i] = new int [V_num];
//        }
        for (int i = 1; i <= V_num; ++i) {
            for (int j = 1; j <= V_num; ++j) {
                dis_matrix[i][j] = MAX_WEIGHT;
            }
        }
        for (int i = 1; i <= V_num; ++i) {
            dis_matrix[i][i] = 0;
        }
    }

    void add_single_edge(int s, int e, int w) {
        edges[E_num].start = s;
        edges[E_num].end = e;
        edges[E_num++].weight = w;
        dis_matrix[s][e] = w;
    }

    void add_double_edge(int s, int e, int w) {
        add_single_edge(s, e, w);
        add_single_edge(e, s, w);
    }

    void bellman_ford(int s) {
        for (int i = 1; i <= V_num; ++i) {
            dis[i] = MAX_WEIGHT;
        }
        dis[s] = 0;

        for (int i = 0; i < V_num - 1; ++i) {
            for (int j = 0; j < E_num; ++j) {
                int p1 = edges[j].start;
                int p2 = edges[j].end;
                int w = edges[j].weight;

                if (dis[p1] != MAX_WEIGHT && dis[p1] + w < dis[p2]) dis[p2] = dis[p1] + w;
            }
        }
    }

    void floyd_warshall() {
        for (int k = 1; k <= V_num; ++k) {
            for (int i = 1; i <= V_num; ++i) {
                for (int j = 1; j <= V_num; ++j) {
                    if (dis_matrix[i][k] != MAX_WEIGHT && dis_matrix[k][j] != MAX_WEIGHT &&
                        dis_matrix[i][k] + dis_matrix[k][j] < dis_matrix[i][j])
                        dis_matrix[i][j] = dis_matrix[i][k] + dis_matrix[k][j];
                }
            }
        }
    }
};


int main() {
    Graph test;
    int n, m, k, s;
    scanf("%d%d%d%d", &n, &m, &k, &s);
    test.set_v(n);
    for (int i = 0; i < m; ++i) {
        int p1, p2, w;
        scanf("%d%d%d", &p1, &p2, &w);
        test.add_double_edge(p1, p2, w);
    }

    for (int i = 0; i < k; ++i) {
        int p1, p2, w;
        scanf("%d%d%d", &p1, &p2, &w);
        test.add_single_edge(p1, p2, w);
    }

    test.floyd_warshall();

//    for (int i = 1; i <= test.V_num; ++i) {
//        for (int j = 1; j <= test.V_num; ++j) {
//            cout << dis_matrix[i][j] << " ";
//        }
//        cout << endl;
//    }

    for (int i = 1; i <= test.V_num; ++i) {
        if (test.dis_matrix[s][i] == MAX_WEIGHT) printf("UNREACHABLE\n");
        else printf("%d\n", test.dis_matrix[s][i]);
    }

//    test.bellman_ford(s);
//
//    for (int i = 1; i <= test.V_num; ++i) {
//        if (test.dis[i] == MAX_WEIGHT) printf("UNREACHABLE\n");
//        else printf("%d\n", test.dis[i]);
//    }

    return 0;
}