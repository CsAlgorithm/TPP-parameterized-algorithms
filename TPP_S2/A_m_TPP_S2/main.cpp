#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <stack>
#include <bitset>
#include"instance_access.h"
#define INF 0x3f3f3f3f
#define eps 1e-8
#define FI first
#define SE second
using namespace std;
typedef long long ll;

const int MaxM = 25, MaxK = 700;

int M, K, Q;

int G[MaxM + 5][MaxM + 5];

int P[MaxM + 5][MaxK + 5];

int C[MaxM + 5];

void read(char *p,int m,int k,int d,int h)
{
    //scanf("%d%d", &M, &K);
   int* _graph;
    int* _price;
    //_graph->printMatrix();
    //cout<<endl;
    //_price->printMatrix();
    //cout<<endl;
    get_instance_largek(_graph,_price,m,k,p);
    //cout<<endl;
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<m;++j)
        {
            int temp=_graph[i*m+j];
            //cout<<temp<<" ";
            *(G[i] + j)=temp;
        }
        //cout<<endl;
    }
    //cout<<endl;

    for(int i=0;i<m;++i)
    {
        for(int j=0;j<k;++j)
        {
            int temp=_price[i*k+j];
//            cout<<temp<<" ";
            *(P[i] + j)=temp;
        }
//        cout<<endl;
    }
    M=m;
    K=k;
    Q=h;
    for(int i=1;i<m;++i)
    {
        C[i]=d;
    }

}
inline void ck(int &x, int v) {
    if(x > v) x = v;
}

int head[MaxM + MaxK + 10];

struct Edge {
    int nxt, to, cow, cost;
    Edge() {}
    Edge(int nxt, int to, int cow, int cost) : nxt(nxt), to(to), cow(cow), cost(cost) {}
} ed[100000];
int ecnt, mx_flow, mi_cost;

void init() {
    mx_flow = mi_cost = ecnt = 0;
    memset(head, -1, sizeof(head));
}

void addedge(int u, int v, int cow, int cost) {
    ed[ecnt] = Edge(head[u], v, cow, cost);
    head[u] = ecnt ++;
    ed[ecnt] = Edge(head[v], u, 0, -cost);
    head[v] = ecnt ++;
}

queue <int> q;

int dis[MaxK + MaxM + 10], pre[MaxK + MaxM + 10], inq[MaxK + MaxM + 10];

bool Spfa(int S, int T) {
    memset(dis, 0x3f, sizeof(dis));
    dis[S] = 0;
    q.push(S);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = 0;
        for(int e = head[u]; ~e; e = ed[e].nxt) {
            if(!ed[e].cow) continue;
            int v = ed[e].to;
            if(dis[v] > dis[u] + ed[e].cost) {
                dis[v] = dis[u] + ed[e].cost;
                pre[v] = e;
                if(!inq[v]) {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return dis[T] != INF;
}

void End(int S, int T) {
    int flow = INF;
    for(int u = T; u != S; u = ed[pre[u] ^ 1].to) {
        flow = min(flow, ed[pre[u]].cow);
    }
    for(int u = T; u != S; u = ed[pre[u] ^ 1].to) {
        ed[pre[u]].cow -= flow;
        ed[pre[u] ^ 1].cow += flow;
        mi_cost += flow * ed[pre[u]].cost;
    }
    mx_flow += flow;
}

int minPrice(int s) {
    init();
    int src = 0, dec = M + K+1;
    for(int i = 1; i < M; ++ i) {
        if(~s >> i & 1) continue;
        addedge(src, i, C[i], 0);
        for(int k = 0; k < K; ++ k) {
            if(P[i][k] == 0) continue;
            addedge(i, M + k+1, 1, P[i][k]);
        }
    }
    for(int i = 1; i <= K; ++ i) {
        addedge(M + i, dec, 1, 0);
    }
    while(Spfa(src, dec)) End(src, dec);
    if(mx_flow != K) return -1;
    return mi_cost;
}

int dp[MaxM + 1][1 << MaxM];

int pop[1 << MaxM];

void work() {
    int U = 1 << M;
    for(int i = 1; i < U; ++ i) {
        pop[i] = pop[i >> 1] + (i & 1);
    }
    for(int i = 1; i < M; ++ i) {
        for(int j = 0; j < U; ++ j) {
            dp[i][j] = INF;
        }
    }
    for(int i = 1; i < M; ++ i) {
        dp[i][1 << i] = G[0][i];
    }
    for(int s = 1; s < U; ++ s) {
        if(pop[s] >= Q) continue;
        for(int i = 1; i < M; ++ i) {
            if(dp[i][s] == INF) continue;
            for(int j = 1; j < M; ++ j) {
                if(s >> j & 1) continue;
                ck(dp[j][s | (1 << j)], dp[i][s] + G[i][j]);
            }
        }
    }
    int ans = INF;
    for(int i = 0; i < U; ++ i) {
        if(pop[i] > Q) continue;
        int f = minPrice(i);
        if(f == -1) continue;
        for(int j = 1; j < M; ++ j) {
            if(dp[j][i] == INF) continue;
            ck(ans, f + dp[j][i] + G[j][0]);
        }
    }
    printf("%d", ans);
}

int main(int argc,char *argv[]) {
    //arguments order: filename m k u q
    if(argc !=6)
    {
        cout<<"wrong number of arguments";
        return 1;
    }
    int m,k,u,q;
    m=atoi(argv[2]);
    k=atoi(argv[3]);
    u=atoi(argv[4]);
    q=atoi(argv[5]);
    read(argv[1],m,k,u,q);
    time_t begin,end;
    cout<<"optimal object value: ";
    begin=clock();
    work();
    end=clock();
    cout<<endl;
    cout<<"time: ";
    cout<<double(end-begin)/CLOCKS_PER_SEC<<endl;
    return 0;
}
