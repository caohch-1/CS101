#include<bits/stdc++.h>
using namespace std;

struct point {
    int v,next,cap;
} edge[25010*10];

int head[25010];
int dis[25010];
bool vis[25010];
int len, n, m;

void addedge(int from, int to, int cap)
{
    edge[len].v = to;
    edge[len].cap = cap;
    edge[len].next = head[from];
    head[from] = len++;
}

void spfa(int start)
{
    queue<int>q;
    for(int i = 1; i <= n; i++){
        dis[i] = 999999999;
        vis[i] = 0;
    }
    q.push(start);
    dis[start] = 0;
    vis[start] = 1;
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        vis[x] = 0;
        for(int i = head[x]; i != -1; i = edge[i].next)
        {
            int v = edge[i].v;
            if(dis[v] > dis[x] + edge[i].cap){
                dis[v] = dis[x] + edge[i].cap;
                if(!vis[v]){
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}
int main()
{
    int s,t;
    len = 0;
    int u,v,w;
    int k;
    scanf("%d%d%d%d",&n,&m,&k,&s);//s到t的最短路
    memset(head,-1,sizeof(head));
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        addedge(u,v,w);
        addedge(v,u,w);
    }
    for(int i=1;i<=k;i++){
        scanf("%d%d%d",&u,&v,&w);
        addedge(u,v,w);
    }
    spfa(s);
    for(int i=1;i<=n;i++){
        if(dis[i]==999999999){
            puts("UNREACHABLE");
        }else{
            printf("%d\n",dis[i]);
        }
    }
    return 0;
}
