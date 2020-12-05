#include <iostream>
#include <algorithm>

using namespace std;
const int N = 36000010;
const int V = 6005;

struct Edge {
    int start;
    int end;
    int weight;

    explicit Edge(int s = 0, int e = 0, int w = 0) : start(s), end(e), weight(w) {};
};

struct Graph {
    int V;
    int E;
    Edge edge[N];
    int size = 0;

    explicit Graph(int v = 0, int e = 0) : V(v), E(e) {};
} graph;

struct Subset {
    int root;
    int height;

    explicit Subset(int p = 0, int r = 0) : root(p), height(r) {};
} subsets[V];

inline int find(Subset pSubset[], int i) {
    if (pSubset[i].root != i) {
        pSubset[i].root = find(pSubset, pSubset[i].root);
    }
    return pSubset[i].root;
}

inline void unionSet(Subset pSubset[], int x, int y) {
    int xRoot = find(pSubset, x);
    int yRoot = find(pSubset, y);

    if (pSubset[xRoot].height < pSubset[yRoot].height) pSubset[xRoot].root = yRoot;
    else if (pSubset[xRoot].height > pSubset[yRoot].height) pSubset[yRoot].root = xRoot;
    else pSubset[yRoot].root = xRoot, pSubset[xRoot].height++;
}

Edge res[V];

inline void HEAP_DECREASE_KEY(Graph &edges, int i, Edge key) {
    edges.edge[i] = key;
    while (i > 1 && edges.edge[i / 2].weight > edges.edge[i].weight) {
        swap(edges.edge[i], edges.edge[i / 2]);
        i = i / 2;
    }
}

inline void MIN_HEAP_INSERT(Graph &edges, Edge e) {
    edges.size++;
    HEAP_DECREASE_KEY(edges, edges.size, e);

}

inline void MIN_HEAPIFY(Graph &edges, int i) {
    int l = 2 * i;
    int r = 2 * i + 1;
    int min;
    if (l <= edges.size && edges.edge[i].weight > edges.edge[l].weight) {
        min = l;
    } else min = i;

    if (r <= edges.size && edges.edge[min].weight > edges.edge[r].weight) {
        min = r;
    }

    if (min != i) {
        swap(edges.edge[i], edges.edge[min]);
        MIN_HEAPIFY(edges, min);
    }
}

Edge HEAP_EXTRACT_MIN(Graph &edges) {
    Edge min = edges.edge[1];
    edges.edge[1] = edges.edge[edges.size];
    edges.size--;
    MIN_HEAPIFY(edges, 1);
    return min;
}

void kruskal() {
    int e = 0, i = 0;

    for (int j = 0; j < graph.V; ++j) {
        subsets[j].root = j;
        subsets[j].height = 0;
    }

    while (e < graph.V - 1 && i < graph.E) {
        Edge next = HEAP_EXTRACT_MIN(graph);
        i++;

        int start = find(subsets, next.start);
        int end = find(subsets, next.end);

        if (start != end) res[e++] = next, unionSet(subsets, start, end);
    }
}

struct point {
    int x = 0;
    int y = 0;
} points[V];

int dis(int x, int y) {
    int dis1 = points[x].x - points[y].x;
    int dis2 = points[x].y - points[y].y;
    if (dis1 < 0) dis1 = -dis1;
    if (dis2 < 0) dis2 = -dis2;
    return dis1 + dis2;
}


int main() {
    int start;
    scanf("%d", &graph.V);
    scanf("%d", &start);
    for (int i = 1; i <= graph.V; ++i) {
        scanf("%d", &points[i].x);
        scanf("%d", &points[i].y);
    }

    for (int i = 1; i <= graph.V; ++i) {
        for (int j = i + 1; j <= graph.V; ++j) {
            Edge temp;
            temp.start = i;
            temp.end = j;
            temp.weight = dis(i, j);
            MIN_HEAP_INSERT(graph, temp);
        }
    }
    graph.E = graph.size;

    kruskal();

    int ans = 0;
    for (int i = 0; i < graph.V - 2; ++i) {
        ans += res[i].weight;
    }
    cout << ans << endl;

    return 0;
}