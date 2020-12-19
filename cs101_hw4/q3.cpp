//
// Created by MissSirius on 2020/12/19.
//
#include <iostream>

using namespace std;

const int N = 505;
const int MAX_WEIGHT = 1005;

int dist[N][N];

int travel_order[N][N];

int costs[N];

void tsp_sub(int s, int n, bool *visit, int &cost, int &last, int &ctr, int start) {
    travel_order[start][ctr] = s;

    visit[s] = true;
    int next_cost = MAX_WEIGHT;
    int next_vertice = -1;
    for (int i = 1; i <= n; ++i) {
        if (!visit[i] && dist[s][i] < next_cost) next_cost = dist[s][i], next_vertice = i;
    }

    if (next_vertice == -1) {
        last = s;
        return;
    }

    visit[next_vertice] = true, cost += next_cost;

    tsp_sub(next_vertice, n, visit, cost, last, ++ctr, start);
}

void tsp(int n) {
    for (int i = 1; i <= n; ++i) {
        bool vis[n + 5];
        for (int j = 1; j <= n; ++j) {
            vis[j] = false;
        }

        int cost = 0;
        int last;
        int ctr = 0;
        tsp_sub(i, n, vis, cost, last, ctr, i);

        costs[i] = cost + dist[i][last];
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < n; ++j) {
        }
    }

}


int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &dist[i][j]);
        }
    }

    tsp(n);

    int min_cost = 5000000;
    int min_start;
    for (int i = 1; i <= n; ++i) {
        if (costs[i] < min_cost) min_start = i;
    }

    for (int i = 0; i < n; ++i) {
        cout << travel_order[min_start][i] << " ";
    }
    return 0;
}



