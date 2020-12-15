//
// Created by MissSirius on 2020/12/7.
//

#include <iostream>
using namespace std;
const int N = 25005;
const int M = 500;
const int WEIGHT = 20005;
int dis[N];
bool visited[N];

class Queue
{
public:
    int data[N*M];
    int head = 0;
    int tail = 0;

    void push(int key) {
        data[tail++] = key;
    }

    int pop() {
        return data[head++];
    }

    bool empty() const {
        return head == tail;
    }
};

struct Edge {
    int end = 0;
    int weight = 0;
};

struct Vertice {
    Edge edges[M];
    int deg = 0;
} graph[N];

void spfa(int S, int V, Vertice* graph)
{
    for (int i = 0; i <= V; i++) {
        dis[i] = WEIGHT;
    }
    dis[S] = 0;

    Queue q;
    q.push(S);
    visited[S] = true;

    while (!q.empty()) {
        int curr = q.pop();
        visited[curr] = false;

        for (int i = 0; i < graph[curr].deg; i++) {
            int vertice = graph[curr].edges[i].end;
            int weight = graph[curr].edges[i].weight;

            if (dis[vertice] > dis[curr] + weight) {
                dis[vertice] = dis[curr] + weight;
                if (!visited[vertice]) q.push(vertice), visited[vertice] = true;
            }
        }
    }
}


int main()
{
    int n, m, k, s;
    scanf("%d%d%d%d", &n, &m, &k, &s);
    for (int i = 0; i < m; ++i) {
        int p1, p2, w;
        scanf("%d%d%d", &p1, &p2, &w);
        graph[p1].edges[graph[p1].deg].end = p2;
        graph[p2].edges[graph[p2].deg].end = p1;
        graph[p1].edges[graph[p1].deg].weight = w;
        graph[p2].edges[graph[p2].deg].weight = w;
        graph[p1].deg ++;
        graph[p2].deg ++;
    }
    for (int i = 0; i < k; ++i) {
        int p1, p2, w;
        scanf("%d%d%d", &p1, &p2, &w);
        graph[p1].edges[graph[p1].deg].end = p2;
        graph[p1].edges[graph[p1].deg].weight = w;
        graph[p1].deg ++;
    }
    spfa(s, n, graph);
    for (int i = 1; i <= n; ++i) {
        if (dis[i] != WEIGHT) printf("%d\n", dis[i]);
        else cout<<"UNREACHABLE\n";
    }
    return 0;
}
