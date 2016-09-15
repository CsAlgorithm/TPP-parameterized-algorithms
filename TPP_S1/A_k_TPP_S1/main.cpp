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

const int MaxK = 20, MaxM = 100;

//int dp[1 << MaxK][MaxM + 1][MaxK + 1];
int dp[1 << MaxK][MaxM + 1][16];

int M, K, Q;

int G[MaxM + 5][MaxM + 5];

int P[MaxM + 5][MaxK + 5];

void read(char *p,int m,int k,int q)
{
    int* _graph;
    int* _price;
    //_graph->printMatrix();
    //cout<<endl;
    //_price->printMatrix();
    //cout<<endl;
    get_instance(_graph,_price,m,k,p);
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
    Q=q;
}

inline void ck(int &x, int v) {
    if(x > v) x = v;
}

void case1() {
    int U = 1 << K;
    for(int i = 0; i < U; ++ i) {
        for(int j = 0; j < M; ++ j) {
            for(int k = 1; k <= Q; ++ k) {
                dp[i][j][k] = INF;
            }
        }
    }
    for(int i = 0; i < M; ++ i) {
        dp[0][i][1] = G[0][i];
    }
    for(int s = 0; s < U; ++ s) {
        for(int c = 1; c <= Q; ++ c) {
            for(int u = 0; u < M; ++ u) {
                if(dp[s][u][c] == INF) continue;
                for(int k = 0; k < K; ++ k) {
                    if(P[u][k] == 0 || (s >> k & 1)) continue;
                    ck(dp[s | (1 << k)][u][c], dp[s][u][c] + P[u][k]);
                }
                if(c == Q) continue;
                for(int v = 0; v < M; ++ v) {
                    if(u == v) continue;
                    ck(dp[s][v][c + 1], dp[s][u][c] + G[u][v]);
                }
            }
        }
    }
    int ans = INF;
    for(int i = 0; i < M; ++ i) {
        for(int j = 1; j <= Q; ++ j) {
            if(dp[U - 1][i][j] == INF) continue;
            ans = min(ans, dp[U - 1][i][j] + G[i][0]);
        }
    }
    printf("%d", ans);
}

bool done[MaxM + 5];

void case2() {
    int U = 1 << K;
    for(int i = 0; i < M; ++ i) {
        for(int j = 0; j < U; ++ j) {
            dp[i][j][0] = INF;
        }
    }
    dp[0][0][0] = 0;
    for(int s = 0; s < U; ++ s) {
        memset(done, 0, (M + 1) * sizeof(bool));
        while(true) {
            int w = INF, u = -1;
            for(int i = 0; i < M; ++ i) {
                if(!done[i] && dp[i][s][0] < w) {
                    w = dp[i][s][0];
                    u = i;
                }
            }
            if(u == -1) break;
            done[u] = true;
            for(int v = 0; v < M; ++ v) {
                if(!done[v] && dp[v][s][0] > dp[u][s][0] + G[u][v]) {
                    dp[v][s][0] = dp[u][s][0] + G[u][v];
                }
            }
        }
        for(int i = 1; i < M; ++ i) {
            if(dp[i][s][0] == INF) continue;
            for(int k = 0; k < K; ++ k) {
                if(P[i][k] == 0) continue;
                if(s >> k & 1) continue;
                ck(dp[i][s | (1 << k)][0], dp[i][s][0] + P[i][k]);
            }
        }
    }
    printf("%d", dp[0][U - 1][0]);
}


int main(int argc,char *argv[]) {
    //arguments order: filename m k q
    if(argc !=5)
    {
        cout<<"wrong number of arguments";
        return 1;
    }
    int m,k,q;
    m=atoi(argv[2]);
    k=atoi(argv[3]);
    q=atoi(argv[4]);
    read(argv[1],m,k,q);
    time_t begin,end;
    cout<<"optimal object value: ";
    begin=clock();
    if(Q < K) {
    case1();
    } else {
    case2();
    }
    end=clock();
    cout<<endl;
    cout<<"time: ";
    cout<<double(end-begin)/CLOCKS_PER_SEC<<endl;
    return 0;
}
