//
// Created by caohch1 on 11/22/20.
//
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100000;

struct Subset {
    int root;
    int height;
    int deg;

    explicit Subset(int p = 0, int r = 0, int d = 0) : root(p), height(r), deg(d) {};
} subsets[N];

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

bool cmp(Subset s1, Subset s2) {
    if (s1.root > s2.root) return true;
    else return false;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        subsets[i].root = i;
    }

    for (int i = 0; i < m; ++i) {
        int c1 = -1, c2 = -1;
        scanf("%d%d", &c1, &c2);
        subsets[c1].deg++, subsets[c2].deg++;
        int city1 = find(subsets, c1);
        int city2 = find(subsets, c2);
        if (city1 != city2) unionSet(subsets, city1, city2);
    }

    for (int i = 1; i <= n; ++i) {
        find(subsets, i);
    }

    sort(subsets + 1, subsets + 1 + n, cmp);

    int ctr = subsets[1].root;
    int tempE = 0;
    int tempV = 0;
    int maxStability = 0;
    for (int i = 1; i <= n; ++i) {
        if (subsets[i].root == ctr) tempE += subsets[i].deg, tempV++;
        else
            maxStability = (tempE / 2 - tempV) <= 0 ? maxStability : maxStability + (tempE / 2 -
                                                                                     tempV), tempE = subsets[i].deg, tempV = 1, ctr = subsets[i].root;
    }
    maxStability = (tempE / 2 - tempV) <= 0 ? maxStability : maxStability + (tempE / 2 - tempV);
    cout << maxStability;
    return 0;
}