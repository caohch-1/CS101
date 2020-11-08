//
// Created by caohch1 on 10/23/20.
//
#include <iostream>
#include <algorithm>

typedef long long ll;
using namespace std;
const int N = 500005;
int n, m;
int eCnt;

struct myPair {
    int num, id;
} needs[N];

inline bool cmp(myPair x, myPair y) { return x.num < y.num; }

struct E {
    int v, next;
} e[N << 2];

struct V {
    int head;
} v[N];

inline void add(int x, int y) {
    e[++eCnt].v = y;
    e[eCnt].next = v[x].head, v[x].head = eCnt;
}

int pos[N], fa[N];

inline int find(int x) { return fa[x] = (fa[x] == x ? x : find(fa[x])); }

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> needs[i].num, needs[i].id = i;
    sort(needs + 1, needs + n + 1, cmp);
//    cout<<"start: "<<endl;
//    for (int i = 1; i < n+1; ++i) {
//        cout<<needs[i].id<<" "<<needs[i].num<<endl;
//    }
    for (int i = 1; i <= n; ++i) pos[needs[i].id] = i;
    int tx, ty;
    for (int i = 1; i <= m; ++i) {
        cin >> tx >> ty;
        add(tx, ty), add(ty, tx);
    }
    cout<<endl<<"start: "<<endl;
    for (int i = 1; i <eCnt ; ++i) {
        cout<<e[i].v<<" "<<e[i].next<<endl;
    }
    for (int i = 1; i <= n; ++i) fa[i] = i;
    ll ans = 0;
    for (int i = n; i >= 1; --i) {
        int x = needs[i].id;
        ans += needs[i].num;
        for (int j = v[x].head; j; j = e[j].next) {
            int y = e[j].v;
            if (pos[y] < pos[x])continue;
            int fx = find(x), fy = find(y);
            if (fx == fy)continue;
            ans -= needs[i].num;
            fa[fy] = fx;
        }
    }
    cout << ans << endl;
    return 0;
}
