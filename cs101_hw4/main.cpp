#include <iostream>

using namespace std;
const int MAX_WEIGHT = 20001;
const int MAX_V = 25005;
const int MAX_E = 50005;

struct Edge {
    int start, end, weight;
};

class Graph {
public:
    int V, E;
    Edge *edges;
    int *distance;

    Graph(int v = 0, int e = 0) {
        this->V = v, this->E = e;
        edges = new Edge[MAX_E];
        distance = new int[MAX_V];
    }

    void BellmanFord(int s) {
        for (int i = 1; i <= this->V; ++i) {
            distance[i] = MAX_WEIGHT;
        }
        distance[s] = 0;

        for (int i = 1; i <= this->V - 1; ++i) {
            for (int j = 0; j < this->E; ++j) {
                int point1 = this->edges[j].start;
                int point2 = this->edges[j].end;
                int w = this->edges[j].weight;
                distance[point2] = (distance[point1] != MAX_WEIGHT && distance[point1] + w < distance[point2]) ?
                                   distance[point1] + w : distance[point2];
            }

        }
    }
};

int n, m, k, s;
Graph graph;


int main() {
    scanf("%d%d%d%d", &n, &m, &k, &s);
    graph.V = n, graph.E = m + k;
    for (int i = 0; i < m + k; ++i) {
        int p1, p2, w;
        scanf("%d%d%d", &p1, &p2, &w);
        graph.edges[i].start = p1;
        graph.edges[i].end = p2;
        graph.edges[i].weight = w;
    }

    graph.BellmanFord(s);

    for (int i = 1; i <= n; ++i) {
        if (graph.distance[i] == MAX_WEIGHT) printf("UNREACHABLE\n");
        else printf("%d\n", graph.distance[i]);
    }

    return 0;

}