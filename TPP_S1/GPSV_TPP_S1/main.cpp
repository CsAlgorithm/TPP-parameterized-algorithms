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

const int MaxM = 100, MaxK = 20;
const int MaxH=50,MaxD=200;
//const int MaxM = 300, MaxK = 25;
//const int MaxH=300,MaxD=50;

int Graph[MaxM + 5][MaxM + 5];

int Price[MaxM + 5][MaxK + 5];

int M, K, H, D;

int M_j[MaxM];
void read(char *p,int m,int k,int d,int h)
{
    //scanf("%d%d", &M, &K);
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
            *(Graph[i] + j)=temp;
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
            *(Price[i] + j)=temp;
        }
//        cout<<endl;
    }
    M=m;
    K=k;
    memset(M_j,0,sizeof(int)*MaxM);
    for(int i=0;i<M;++i)
    {
        int count=0;
        for(int j=0;j<K;++j)
        {
            if(Price[i][j]!=0)
            {
                ++count;
            }
        }
        M_j[i]=count;
    }
    H=h;
    D=d;
}

struct dpEle{
    int pre_k;
    int pre_i;
    int pre_b;
    int value;
};

dpEle dp[MaxH+5][MaxM+5][MaxK+5];



int d(int j, int b)
{
    int value=0;
    int check[MaxK];
    memset(check,0,sizeof(int)*MaxK);
    for(int b1=0;b1<b;++b1)
    {
        int temp=INF;
        int tempi=0;
        for(int i=0;i<K;++i)
        {
            if(check[i]==0 && Price[j][i]!=0 && Price[j][i]<temp)
            {
                temp=Price[j][i];
                tempi=i;
            }
        }
        value=value+temp;
        check[tempi]=1;
    }
    return value;
}

void work() {
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<M;++i)
    {
        for(int b=1;b<=(M_j[i]<D?M_j[i]:D);++b)
        {
            dp[0][i][b].value=Graph[0][i]+d(i,b);
            dp[0][i][b].pre_b=0;
            dp[0][i][b].pre_i=0;
            dp[0][i][b].pre_k=-1;
        }
    }

    for(int k=0;k<H;++k)
    {
        for(int i=1;i<M;++i)
        {
            for(int b=1;b<=K;++b)
            {
                int temp=dp[k][i][b].value;
                if(temp==INF)
                {
                    continue;
                }
                int pre_i=INF;
                if(k>0)
                {
                    pre_i=dp[k][i][b].pre_i;
                }
                for(int i1=1;i1<M;++i1)
                {
                    if(i1==i || i1==pre_i)  continue;
                    for(int c=1;c<=M_j[i1] &&  c<=D && c<=K-b;++c)
                    {
                        int t=temp+Graph[i][i1]+d(i1,c);
                        if(t<dp[k+1][i1][b+c].value)
                        {
                            dp[k+1][i1][b+c].value=t;
                            dp[k+1][i1][b+c].pre_i=i;
                            dp[k+1][i1][b+c].pre_k=k;
                            dp[k+1][i1][b+c].pre_b=b;
                            continue;
                        }
                    }
                }
            }
        }
    }
}

int heuristic()
{
    int temp_v=INF;
    int temp_k;
    int temp_i;
    int _ret=1;
    for(int k=0;k<H;++k)
    {
        for(int i=1;i<M;++i)
        {
            if(dp[k][i][K].value+Graph[i][0]<temp_v)
            {
                _ret=0;
                temp_v=dp[k][i][K].value+Graph[i][0];
                temp_k=k;
                temp_i=i;
            }
        }
    }
    if(_ret)
    {
        cout<<"NULL1";
        return 0;
    }
    int path_length=temp_k+1+2;
    int path[path_length][3];
    path[path_length-1][0]=0;
    path[path_length-1][1]=temp_v;
    path[path_length-1][2]=K;
    path[path_length-2][0]=temp_i;
    path[path_length-2][2]=K;
    int _k=temp_k;
    int _i=temp_i;
    int _b=K;
    int temp_b=K;
    for(int i=temp_k;i>=0;--i)
    {
        temp_k=dp[_k][_i][_b].pre_k;
        temp_i=dp[_k][_i][_b].pre_i;
        temp_b=dp[_k][_i][_b].pre_b;
        temp_v=dp[_k][_i][_b].value;
        path[temp_k+2][1]=temp_v;
        path[temp_k+1][0]=temp_i;
        path[temp_k+1][2]=temp_b;
        _k=temp_k;
        _i=temp_i;
        _b=temp_b;
    }
    path[0][0]=0;
    path[0][1]=0;
    path[0][2]=0;
    int purchase_plan[M][2];
    memset(purchase_plan,0,sizeof(purchase_plan));
    for(int i=1;i<path_length;++i)
    {
        purchase_plan[i][0]=path[i][0];
        purchase_plan[i][1]=path[i][2]-path[i-1][2];
    }
    int check[M][2];
    memset(check,0,sizeof(check));
    for(int i=0;i<path_length;++i)
    {
        if(check[purchase_plan[i][0]][0]==0)
        {
            check[purchase_plan[i][0]][0]=1;
            check[purchase_plan[i][0]][1]=i;
        }else{
            if(purchase_plan[check[purchase_plan[i][0]][1]][1]+purchase_plan[i][1]>=D)
            {
                purchase_plan[check[purchase_plan[i][0]][1]][1]=D;
            }else{
                purchase_plan[check[purchase_plan[i][0]][1]][1]=purchase_plan[check[purchase_plan[i][0]][1]][1]+purchase_plan[i][1];
            }
            purchase_plan[i][0]=-1;
        }
    }
    for(int i=0;i<path_length;++i)
    {
        if(purchase_plan[i][0]!=-1) continue;
        for(int j=i;j<path_length-1;++j)
        {
            purchase_plan[j][0]=purchase_plan[j+1][0];
            purchase_plan[j][1]=purchase_plan[j+1][1];
        }
        --path_length;
        --i;
    }
    int purchased_product[K];
    memset(purchased_product,0,sizeof(purchased_product));
    for(int i=0;i<path_length;++i)
    {
        int j=purchase_plan[i][0];
        int b=purchase_plan[i][1];
//        int check[MaxK];
//        memset(check,0,sizeof(int)*MaxK);
        for(int b1=0;b1<b;++b1)
        {
            int temp=INF;
            int tempi=0;
            for(int i=0;i<K;++i)
            {
                if(purchased_product[i]==0 && Price[j][i]!=0 && Price[j][i]<temp)
                {
                    temp=Price[j][i];
                    tempi=i;
                }
            }
            if(temp==INF)
            {
                break;
            }
            purchased_product[tempi]=j;
        }
    }
    int gotostep3=0;
    for(int i=0;i<K;++i)
    {
        if(purchased_product[i]==0)
        {
            gotostep3=1;
            break;
        }
    }
    int market[M];
    memset(market,0,sizeof(market));
    for(int i=0;i<path_length;++i)
    {
        market[purchase_plan[i][0]]=purchase_plan[i][1];
    }
    if(gotostep3)
    {
        for(int i=0;i<K;++i)
        {
            if(purchased_product[i]==0)
            {
                int tempv=INF;
                int tempj;
                for(int j=0;j<M;++j)
                {
                    if(Price[j][i]>0 && market[j]>0 && market[j]<D)
                    {
                        if(Price[j][i]<tempv)
                        {
                            tempv=Price[j][i];
                            tempj=j;
                        }
                    }
                }
                if(tempv!=INF)
                {
                    purchased_product[i]=tempj;
                    ++market[tempj];
                }
            }
        }
    }
    int gotostep4=0;
    for(int i=0;i<K;++i)
    {
        if(purchased_product[i]==0)
        {
            gotostep4=1;
            break;
        }
    }
    if(gotostep4)
    {
        int addMarket[M];
        memset(addMarket,0,sizeof(addMarket));
        for(int c=0;c<H-path_length+1;++c)
        {
            int marketTemp[M];
            memset(marketTemp,0,sizeof(marketTemp));
            int ifbreak=1;
            for(int i=0;i<M;++i)
            {
                for(int j=0;j<K;++j)
                {
                    if(purchased_product[j]==0)
                    {
                        if(Price[i][j]!=0 && market[i]==0 && addMarket[i]==0)
                        {
                            ++marketTemp[i];
                        }
                        ifbreak=0;
                    }
                }
            }
            if(ifbreak)
            {
                break;
            }
            int tempv=0;
            int tempi;
            for(int i=0;i<M;++i)
            {
                if(marketTemp[i]>tempv)
                {
                    tempv=marketTemp[i];
                    tempi=i;
                }
            }
            addMarket[tempi]=1;
            int additemnum=0;
            for(int j=0;j<K;++j)
            {
                if(Price[tempi][j]!=0 && purchased_product[j]==0)
                {
                    purchased_product[j]=tempi;
                    ++additemnum;
                }
                if(additemnum==D)
                {
                    break;
                }
            }
        }
        int isfeasible=0;
        for(int i=0;i<K;++i)
        {
            if(purchased_product[i]==0)
            {
                isfeasible=1;
            }
        }
        if(isfeasible)
        {
            cout<<"NULL2l";
            return 0;
        }
        for(int i=0;i<M;++i)
        {
            if(addMarket[i]==1)
            {
                int cost=INF;
                int tempj;
                for(int j=0;j<path_length-1;++j)
                {
                    if((Graph[purchase_plan[j][0]][i]+Graph[i][purchase_plan[j+1][0]])<cost)
                    {
                        cost=Graph[purchase_plan[j][0]][i]+Graph[i][purchase_plan[j+1][0]];
                        tempj=j;
                    }
                }
                for(int j=path_length-1;j>tempj;--j)
                {
                    purchase_plan[j+1][0]=purchase_plan[j][0];
                }
                purchase_plan[tempj+1][0]=i;
                ++path_length;
            }
        }
        int cost=0;
        for(int i=0;i<path_length-1;++i)
        {
            cost=cost+Graph[i][i+1];
        }
        cost=cost+Graph[path_length-1][0];
        for(int i=0;i<K;++i)
        {
            cost=cost+Price[purchased_product[i]][i];
        }
        cout<<cost;
        return 1;
    }
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
    read(argv[1],m,k,INF,q);
    time_t begin,end;
    cout<<"optimal object value: ";
    begin=clock();
    work();
    heuristic();
    end=clock();
    cout<<endl;
    cout<<"time: ";
    cout<<double(end-begin)/CLOCKS_PER_SEC<<endl;
    return 0;
}
