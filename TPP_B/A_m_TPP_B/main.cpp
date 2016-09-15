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

int Graph[MaxM + 5][MaxM + 5];

int Price[MaxM + 5][MaxK + 5];

int M, K, B;

void read(char *p,int m,int k)
{
    //scanf("%d%d", &M, &K);
    M=m;
    K=k;
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
            Graph[i][j]=temp;
        }
        //cout<<endl;
    }
    //cout<<endl;

    for(int i=0;i<m;++i)
    {
        for(int j=0;j<k;++j)
        {
            int temp=_price[i*k+j];
            //cout<<temp<<" ";
            Price[i][j]=temp;
        }
        //cout<<endl;
    }
}

int f[1 << MaxM], g[MaxK + 5];

inline void checkmin(int &x, int v) {
    if(x > v) x = v;
}

int getB(int s)
{
    memset(g, 0x3f, K * sizeof(int));
    for(int i = 1; i < M; ++ i) {
        if(~s >> i & 1) continue;
        for(int j = 0; j < K; ++ j) {
            if(Price[i][j] == 0) continue;
            checkmin(g[j], Price[i][j]);
        }
    }
    int ret = 0;
    for(int i = 0; i < K; ++ i) {
        if(g[i] == INF) return -1;
        ret += g[i];
    }
    return ret;
}

inline int minPrice(int s) {
    memset(g, 0x3f, K * sizeof(int));
    for(int i = 1; i < M; ++ i) {
        if(~s >> i & 1) continue;
        for(int j = 0; j < K; ++ j) {
            if(Price[i][j] == 0) continue;
            checkmin(g[j], Price[i][j]);
        }
    }
    int ret = 0;
    for(int i = 0; i < K; ++ i) {
        if(g[i] == INF) return -1;
        ret += g[i];
    }
    if(ret>B)
    {
        return -1;
    }
    return ret;
}

int dp[MaxM + 5][1 << MaxM];

void work() {
    int U = 1 << M;
    for(int i = 0; i < U; ++ i) {
        f[i] = minPrice(i);
    }
    for(int i = 0; i < M; ++ i) {
        for(int j = 0; j < U; ++ j) {
            dp[i][j] = INF;
        }
    }
    for(int i = 0; i < M; ++ i) {
        dp[i][1 << i] = Graph[0][i];
    }
    for(int s = 1; s < U; ++ s) {
        for(int i = 1; i < M; ++ i) {
            if(dp[i][s] == INF) continue;
            for(int j = 1; j < M; ++ j) {
                if(s >> j & 1) continue;
                checkmin(dp[j][s | (1 << j)], dp[i][s] + Graph[i][j]);
            }
        }
    }
}

void write() {
    int answer = INF;
    int p_cost=INF;
    int U = 1 << M;
    for(int i = 0; i < U; ++ i) {
        if(f[i] == -1) continue;
        for(int j = 1; j < M; ++ j) {
            if(dp[j][i] == INF) continue;
            //checkmin(answer, dp[j][i] + Graph[j][0]);
            if(dp[j][i] + Graph[j][0]<answer)
            {
                answer=dp[j][i] + Graph[j][0];
                p_cost=f[i];
            }
        }
    }
    //cout<<' '<<p_cost<<' ';
    printf("%d", answer);
}


int main(int argc,char *argv[]) {
    //arguments order: filename m k b
    if(argc !=5)
    {
        cout<<"wrong number of arguments";
        return 1;
    }
    int m,k;
    double i;
    m=atoi(argv[2]);
    k=atoi(argv[3]);
    i=atof(argv[4]);
    read(argv[1],m,k);
    int b=getB((1<<(M+1))-1);
    B=b*i;
    time_t begin,end;
    cout<<"optimal object value: ";
    begin=clock();
    work();
    write();
    end=clock();
    cout<<endl;
    cout<<"time: ";
    cout<<double(end-begin)/CLOCKS_PER_SEC<<endl;
    return 0;
}
