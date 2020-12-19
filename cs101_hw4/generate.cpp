#include<bits/stdc++.h>
using namespace std;
ofstream fout("roadplane.in");
const int n=14000,m=30000,w=50000,cn=1000,W=20000;
int belong[n+5];
vector<int> comp[cn+5];
int f[n+5];
int getf(int x)
{
    return f[x]==x?x:f[x]=getf(f[x]);
}
int main()
{
    minstd_rand gen(time(NULL));
    for(int i=1;i<=n;i++)
    {
        uniform_int_distribution<> dc(1,cn);
        belong[i]=dc(gen);
        comp[belong[i]].push_back(i);
    }
    assert(comp[1].size());
    uniform_int_distribution<> d(0,comp[1].size()-1);
    fout<<n<<' '<<m<<' '<<w<<' '<<comp[1][d(gen)]<<endl;
    for(int i=1;i<=cn;i++)
    {
        int cnt=0;
        for(int j=0;j<comp[i].size();j++)
            f[j]=j;
        while(cnt+1<comp[i].size())
        {
            uniform_int_distribution<> did(0,comp[i].size()-1);
            int u=did(gen),v=did(gen),ru=getf(u),rv=getf(v);
            if(ru!=rv)
            {
                f[ru]=rv;
                cnt++;
                uniform_int_distribution<> dw(0,W);
                fout<<comp[i][u]<<' '<<comp[i][v]<<' '<<dw(gen)<<endl;
            }
        }
    }
    for(int i=n-cn+1;i<=m;i++)
    {
        uniform_int_distribution<> dc(1,cn);
        int c=dc(gen);
        if(!comp[c].size())
        {
            i--;
            continue;
        }
        uniform_int_distribution<> did(0,comp[c].size()-1),dw(0,W);
        fout<<comp[c][did(gen)]<<' '<<comp[c][did(gen)]<<' '<<dw(gen)<<endl;
    }
    for(int i=1;i<=cn;i++)
        f[i]=i;
    for(int i=1;i<cn;)
    {
        uniform_int_distribution<> dc(1,cn-1);
        int cu=dc(gen);
        uniform_int_distribution<> dc1(cu+1,cn);
        int cv=dc1(gen),rcu=getf(cu),rcv=getf(cv);
        if(rcu==rcv)
            continue;
        f[rcu]=rcv;
        if(!comp[cu].size()||!comp[cv].size())
            continue;
        uniform_int_distribution<> didu(0,comp[cu].size()-1),didv(0,comp[cv].size()-1),dw(-W,W);
        fout<<comp[cu][didu(gen)]<<' '<<comp[cv][didv(gen)]<<' '<<dw(gen)<<endl;
        i++;
    }
    for(int i=cn;i<=w;)
    {
        uniform_int_distribution<> dc(1,cn-1);
        int cu=dc(gen);
        uniform_int_distribution<> dc1(cu+1,cn);
        int cv=dc1(gen);
        if(!comp[cu].size()||!comp[cv].size())
            continue;
        uniform_int_distribution<> didu(0,comp[cu].size()-1),didv(0,comp[cv].size()-1),dw(-W,W);
        fout<<comp[cu][didu(gen)]<<' '<<comp[cv][didv(gen)]<<' '<<dw(gen)<<endl;
        i++;
    }
    return 0;
}