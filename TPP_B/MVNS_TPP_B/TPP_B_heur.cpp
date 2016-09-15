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
#include"random.h"
#define INF 0x3f3f3f3f
#define eps 1e-8
#define FI first
#define SE second
using namespace std;
typedef long long ll;

const int MaxM = 25, MaxK = 700;



int M, K, B;

int G[MaxM + 5][MaxM + 5];

int P[MaxM + 5][MaxK + 5];

void read(char *p,int m,int k,int b)
{
    int* _graph;
    int* _price;
    get_instance_largek(_graph,_price,m,k,p);
    //cout<<endl;
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<m;++j)
        {
            int temp=_graph[i*m+j];
            *(G[i] + j)=temp;
        }
    }

    for(int i=0;i<m;++i)
    {
        for(int j=0;j<k;++j)
        {
            int temp=_price[i*k+j];
            *(P[i] + j)=temp;
        }
    }
    M=m;
    K=k;
    B=b;
}

struct Solution{
    int market[MaxM];
    int path[MaxM];
    //int buy[MaxM][MaxK];
    int pathlength;
    int value;
};

Solution type1insertion(Solution s,const int v,const int i,const int j,const int k)
{
    int cycle_size=s.pathlength;
    if(i<j)
    {
        if(k>i && k<j)
        {
            int i_1_jL=0;
            int k_1_iL=0;
            int j_1_kL=0;
            int i_1_j[cycle_size];
            int k_1_i[cycle_size];
            int j_1_k[cycle_size];
            memset(i_1_j,0x3f,sizeof(i_1_j));
            memset(k_1_i,0x3f,sizeof(k_1_i));
            memset(j_1_k,0x3f,sizeof(j_1_k));
            for(int i1=i-1;i1>=0;--i1)
            {
                i_1_j[i_1_jL]=s.path[i1];
                ++i_1_jL;
            }
            for(int i1=cycle_size-1;i1>=j;--i1)
            {
                i_1_j[i_1_jL]=s.path[i1];
                ++i_1_jL;
            }
            for(int i1=k-1;i1>=i;--i1)
            {
                k_1_i[k_1_iL]=s.path[i1];
                ++k_1_iL;
            }
            for(int i1=j-1;i1>=k;--i1)
            {
                j_1_k[j_1_kL]=s.path[i1];
                ++j_1_kL;
            }
            int p=0;
            for(int i1=i_1_jL-1;i1>=0;--i1)
            {
                s.path[p]=i_1_j[i1];
                ++p;
            }
            for(int i1=j_1_kL-1;i1>=0;--i1)
            {
                s.path[p]=j_1_k[i1];
                ++p;
            }
            for(int i1=0;i1<k_1_iL;++i1)
            {
                s.path[p]=k_1_i[i1];
                ++p;
            }
            s.path[p]=v;
            ++p;
            s.pathlength=p;
        }
        if(k<i)
        {
            int p=0;
            int temps[cycle_size+1];
            for(int i1=j;i1>=i+1;--i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            for(int i1=k;i1>=0;--i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            for(int i1=cycle_size-1;i1>=j+1;--i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            for(int i1=k+1;i1<=i;++i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            temps[p]=v;
            ++p;
            for(int i1=0;i1<p;++i1)
            {
                s.path[i1]=temps[i1];
            }
            s.pathlength=p;
        }
        if(k>j)
        {
            int p=0;
            int temps[cycle_size+1];
            for(int i1=j;i1>=i+1;--i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            for(int i1=k;i1>=j+1;--i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            for(int i1=k+1;i1<cycle_size;++i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            for(int i1=0;i1<=i;++i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            temps[p]=v;
            ++p;
            for(int i1=0;i1<p;++i1)
            {
                s.path[i1]=temps[i1];
            }
            s.pathlength=p;
        }
    }
    if(i>j)
    {
        if(k>j && k<i)
        {
            int p=0;
            int temps[cycle_size+1];
            for(int i1=j;i1>=0;--i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            for(int i1=cycle_size-1;i1>=i+1;--i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            for(int i1=k;i1>=j+1;--i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            for(int i1=k+1;i1<=i;++i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            temps[p]=v;
            ++p;
            for(int i1=0;i1<p;++i1)
            {
                s.path[i1]=temps[i1];
            }
            s.pathlength=p;
        }
        if(k<j)
        {
            int p=0;
            int temps[cycle_size+1];
            for(int i1=j;i1<=i-1;++i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            for(int i1=k;i1<=j-1;++i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            for(int i1=k-1;i1>=0;--i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            for(int i1=cycle_size-1;i1>=i;--i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            temps[p]=v;
            ++p;
            for(int i1=0;i1<p;++i1)
            {
                s.path[i1]=temps[i1];
            }
            s.pathlength=p;
        }
        if(k>i)
        {
            int p=0;
            int temps[cycle_size+1];
            for(int i1=j;i1<=i-1;++i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            for(int i1=k;i1<cycle_size;++i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            for(int i1=0;i1<=j-1;++i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            for(int i1=k-1;i1>=i;--i1)
            {
                temps[p]=s.path[i1];
                ++p;
            }
            temps[p]=v;
            ++p;
            for(int i1=0;i1<p;++i1)
            {
                s.path[i1]=temps[i1];
            }
            s.pathlength=p;
        }
    }
    return s;
}

Solution type2insertion(Solution s,const int v,const int i,const int j, const int k,const int l)
{
    int cycle_size=s.pathlength;
    if(i<j)
    {
        if(k>i && k<j)
        {
            if(l<i)
            {
                int p=0;
                int temps[cycle_size+1];
                for(int i1=j;i1<cycle_size;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=0;i1<=l;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=j-1;i1>=k+1;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=l+1;i1<=i-1;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=k;i1>=i;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                temps[p]=v;
                ++p;
                for(int i1=0;i1<p;++i1)
                {
                    s.path[i1]=temps[i1];
                }
                s.pathlength=p;
            }
            if(l>j)
            {
                int p=0;
                int temps[cycle_size+1];
                for(int i1=j;i1<=l;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=j-1;i1>=k+1;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=l+1;i1<cycle_size;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=0;i1<=i-1;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=k;i1>=i;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                temps[p]=v;
                ++p;
                for(int i1=0;i1<p;++i1)
                {
                    s.path[i1]=temps[i1];
                }
                s.pathlength=p;
            }
        }
        if(l>i && l<j)
        {
            if(k<i)
            {
                int p=0;
                int temps[cycle_size+1];
                for(int i1=j;i1>=l;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=j+1;i1<cycle_size;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=0;i1<=k-1;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=l-1;i1>=i+1;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=k;i1<=i;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                temps[p]=v;
                ++p;
                for(int i1=0;i1<p;++i1)
                {
                    s.path[i1]=temps[i1];
                }
                s.pathlength=p;
            }
            if(k>j)
            {
                int p=0;
                int temps[cycle_size+1];
                for(int i1=j;i1>=l;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=j+1;i1<=k-1;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=l-1;i1>=i+1;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=k;i1<cycle_size;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=0;i1<=i;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                temps[p]=v;
                ++p;
                for(int i1=0;i1<p;++i1)
                {
                    s.path[i1]=temps[i1];
                }
                s.pathlength=p;
            }
        }
    }
    if(i>j)
    {
        if(k>j && k<i)
        {
            if(l<j)
            {
                int p=0;
                int temps[cycle_size+1];
                for(int i1=j;i1>=l;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=j+1;i1<=k-1;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=l-1;i1>=0;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=cycle_size-1;i1>=i+1;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=k;i1<=i;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                temps[p]=v;
                ++p;
                for(int i1=0;i1<p;++i1)
                {
                    s.path[i1]=temps[i1];
                }
                s.pathlength=p;
            }
            if(l>i)
            {
                int p=0;
                int temps[cycle_size+1];
                for(int i1=j;i1>=0;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=cycle_size-1;i1>=l;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=j+1;i1<=k-1;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=l-1;i1>=i+1;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=k;i1<=i;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                temps[p]=v;
                ++p;
                for(int i1=0;i1<p;++i1)
                {
                    s.path[i1]=temps[i1];
                }
                s.pathlength=p;
            }
        }
        if(l>j && l<i)
        {
            if(k<j)
            {
                int p=0;
                int temps[cycle_size+1];
                for(int i1=j;i1<=l;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=j-1;i1>=k+1;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=l+1;i1<=i-1;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=k;i1>=0;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=cycle_size-1;i1>=i;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                temps[p]=v;
                ++p;
                for(int i1=0;i1<p;++i1)
                {
                    s.path[i1]=temps[i1];
                }
                s.pathlength=p;
            }
            if(k>i)
            {
                int p=0;
                int temps[cycle_size+1];
                for(int i1=j;i1<=l;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=j-1;i1>=0;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=cycle_size-1;i1>=k+1;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=l+1;i1<=i-1;++i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                for(int i1=k;i1>=i;--i1)
                {
                    temps[p]=s.path[i1];
                    ++p;
                }
                temps[p]=v;
                ++p;
                for(int i1=0;i1<p;++i1)
                {
                    s.path[i1]=temps[i1];
                }
                s.pathlength=p;
            }
        }
    }
    return s;
}

int travelingCost(Solution s)
{
    int cost=0;
    for(int i=0;i<s.pathlength-1;++i)
    {
        cost=cost+G[s.path[i]][s.path[i+1]];
    }
    cost=cost+G[s.path[s.pathlength-1]][s.path[0]];
    return cost;
}

Solution GENI(Solution s,int p)
{
    int Np[M][p];
    int Np_v[M][p];
    memset(Np,0x3f,sizeof(Np));
    memset(Np_v,0x3f,sizeof(Np_v));
    for(int i=0;i<M;++i)
    {
        for(int j=0;j<s.pathlength;++j)
        {
            if(i==s.path[j]) continue;
            for(int j1=0;j1<p;++j1)
            {
                if(G[i][s.path[j]]<=Np_v[i][j1])
                {
                    for(int k=p-2;k>=j1;--k)
                    {
                        Np[i][k+1]=Np[i][k];
                        Np_v[i][k+1]=Np_v[i][k];
                    }
                    Np[i][j1]=j;
                    Np_v[i][j1]=G[i][s.path[j]];
                    break;
                }
            }
        }
    }
//    for(int i=0;i<M;++i)
//    {
//        cout<<i<<' ';
//        for(int j=0;j<p;++j)
//        {
//            cout<<Np[i][j]<<' ';
//        }
//        cout<<endl;
//    }
    int v=-1;
    int pathNode[M];
    memset(pathNode,0,sizeof(pathNode));
    for(int i=0;i<s.pathlength;++i)
    {
        pathNode[s.path[i]]=1;
    }
    for(int i=0;i<M;++i)
    {
        if(s.market[i]==1 && pathNode[i]==0)
        {
            v=i;
            break;
        }
    }
    if(v==-1)
    {
        return s;
    }
    int tempv=INF;
    Solution temps;
    for(int i=0;i<p;++i)
    {
        if(Np[v][i]==INF) break;
        for(int j=0;j<p;++j)
        {
//            cout<<Np[v][i]<<' '<<Np[v][j]<<endl;
            if(Np[v][j]==INF) break;
            if(i==j) continue;
            int i_1;
            //方向1+: i i+1 j
            i_1=Np[v][i]+1;
            if(i_1>=s.pathlength)
            {
                i_1=0;
            }
            for(int k=0;k<p;++k)
            {
//                cout<<Np[s.path[i_1]][k]<<endl;
                if(Np[s.path[i_1]][k]==INF) break;
                if(Np[s.path[i_1]][k]==Np[v][i] || Np[s.path[i_1]][k]==Np[v][j]) continue;
                Solution t=type1insertion(s,v,Np[v][i],Np[v][j],Np[s.path[i_1]][k]);
                int _t=travelingCost(t);
                if(_t<tempv && t.pathlength==s.pathlength+1)
                {
                    tempv=_t;
                    temps=t;
                }
            }
            i_1=Np[v][i]-1;
            if(i_1<0)
            {
                i_1=s.pathlength-1;
            }
            for(int k=0;k<p;++k)
            {
//                cout<<Np[s.path[i_1]][k]<<endl;
                if(Np[s.path[i_1]][k]==INF) break;
                if(Np[s.path[i_1]][k]==Np[v][i] || Np[s.path[i_1]][k]==Np[v][j]) continue;
                Solution t=type1insertion(s,v,Np[v][i],Np[v][j],Np[s.path[i_1]][k]);
                int _t=travelingCost(t);
                if(_t<tempv && t.pathlength==s.pathlength+1)
                {
                    tempv=_t;
                    temps=t;
                }
            }
        }
    }

    for(int i=0;i<p;++i)
    {
        if(Np[v][i]==INF) break;
        for(int j=0;j<p;++j)
        {
//            cout<<Np[v][i]<<' '<<Np[v][j]<<endl;
            if(Np[v][j]==INF) break;
            if(i==j) continue;
            int i_1,j_1;
            i_1=Np[v][i]+1;
            j_1=Np[v][j]+1;
            if(i_1>=s.pathlength)
            {
                i_1=0;
            }
            if(j_1>=s.pathlength)
            {
                j_1=0;
            }
            for(int k=0;k<p;++k)
            {
//                cout<<Np[s.path[i_1]][k]<<endl;
                if(Np[s.path[i_1]][k]==INF) break;
                for(int l=0;l<p;++l)
                {
                    if(Np[s.path[j_1]][l]==INF) break;
                    Solution t=type2insertion(s,v,Np[v][i],Np[v][j],Np[s.path[i_1]][k],Np[s.path[j_1]][l]);
                    int _t=travelingCost(t);
                    if(_t<tempv && t.pathlength==s.pathlength+1)
                    {
                        tempv=_t;
                        temps=t;
                    }
                }
            }

            i_1=Np[v][i]+1;
            j_1=Np[v][j]-1;
            if(i_1>=s.pathlength)
            {
                i_1=0;
            }
            if(j_1<0)
            {
                j_1=s.pathlength-1;
            }
            for(int k=0;k<p;++k)
            {
//                cout<<Np[s.path[i_1]][k]<<endl;
                if(Np[s.path[i_1]][k]==INF) break;
                for(int l=0;l<p;++l)
                {
                    if(Np[s.path[j_1]][l]==INF) break;
                    Solution t=type2insertion(s,v,Np[v][i],Np[v][j],Np[s.path[i_1]][k],Np[s.path[j_1]][l]);
                    int _t=travelingCost(t);
                    if(_t<tempv && t.pathlength==s.pathlength+1)
                    {
                        tempv=_t;
                        temps=t;
                    }
                }
            }

            i_1=Np[v][i]-1;
            j_1=Np[v][j]+1;
            if(i_1<0)
            {
                i_1=s.pathlength-1;
            }
            if(j_1>=s.pathlength)
            {
                j_1=0;
            }
            for(int k=0;k<p;++k)
            {
//                cout<<Np[s.path[i_1]][k]<<endl;
                if(Np[s.path[i_1]][k]==INF) break;
                for(int l=0;l<p;++l)
                {
                    if(Np[s.path[j_1]][l]==INF) break;
                    Solution t=type2insertion(s,v,Np[v][i],Np[v][j],Np[s.path[i_1]][k],Np[s.path[j_1]][l]);
                    int _t=travelingCost(t);
                    if(_t<tempv && t.pathlength==s.pathlength+1)
                    {
                        tempv=_t;
                        temps=t;
                    }
                }
            }

            i_1=Np[v][i]-1;
            j_1=Np[v][j]-1;
            if(i_1<0)
            {
                i_1=s.pathlength-1;
            }
            if(j_1<0)
            {
                j_1=s.pathlength-1;
            }
            for(int k=0;k<p;++k)
            {
//                cout<<Np[s.path[i_1]][k]<<endl;
                if(Np[s.path[i_1]][k]==INF) break;
                for(int l=0;l<p;++l)
                {
                    if(Np[s.path[j_1]][l]==INF) break;
                    Solution t=type2insertion(s,v,Np[v][i],Np[v][j],Np[s.path[i_1]][k],Np[s.path[j_1]][l]);
                    int _t=travelingCost(t);
                    if(_t<tempv && t.pathlength==s.pathlength+1)
                    {
                        tempv=_t;
                        temps=t;
                    }
                }
            }
        }
    }
    if(tempv==INF)
    {
        return s;
    }
    return GENI(temps,p);
}

inline int increase(int i,int direction)
{
    if(direction==1)
    {
        return ++i;
    }
    if(direction==0)
    {
        return --i;
    }
}

inline int decrease(int i,int direction)
{
    if(direction==1)
    {
        return --i;
    }
    if(direction==0)
    {
        return ++i;
    }
}

Solution type1unstring(Solution s,const int i,const int j,const int k)
{
    int direction=-1;
    if(i<j)
    {
        if(k>i && k<j)
        {
            direction=1;
        }
        if(k<i || k>j)
        {
            direction=0;
        }
    }
    if(i>j)
    {
        if(k>j && k<i)
        {
            direction=0;
        }
        if(k<j || k>i)
        {
            direction=1;
        }
    }
    if(direction==-1)
    {
        return s;
    }
    int cycle_length=s.pathlength;
    int temp[cycle_length-1];
    int p=0;
    for(int i1=k;i1!=i;i1=(decrease(i1,direction)+cycle_length)%cycle_length)
    {
        temp[p]=s.path[i1];
        ++p;
    }
    for(int i1=j;i1!=k;i1=(decrease(i1,direction)+cycle_length)%cycle_length)
    {
        temp[p]=s.path[i1];
        ++p;
    }
    for(int i1=(increase(j,direction)+cycle_length)%cycle_length;i1!=i;i1=(increase(i1,direction)+cycle_length)%cycle_length)
    {
        temp[p]=s.path[i1];
        ++p;
    }
    s.pathlength=p;
    for(int i1=0;i1<p;++i1)
    {
        s.path[i1]=temp[i1];
    }
    return s;
}

Solution type2unstring(Solution s,const int i,const int j,const int k,const int l)
{
    int direction=-1;
    if(i< l)
    {
        if(j>i && j<l)
        {
            if(k>l)
            {
                direction=1;
            }
            if(k<i)
            {
                direction=1;
            }
        }
        if(k>i && k<l)
        {
            if(j>l)
            {
                direction=0;
            }
            if(j<i)
            {
                direction=0;
            }
        }
    }
    if(i>l)
    {
        if(j>l && j<i)
        {
            if(k>i)
            {
                direction=0;
            }
            if(k<l)
            {
                direction=0;
            }
        }
        if(k>l && k<i)
        {
            if(j>i)
            {
                direction=1;
            }
            if(j<l)
            {
                direction=1;
            }
        }
    }
    if(direction==-1)
    {
        return s;
    }
    int cycle_length=s.pathlength;
    int temp[cycle_length-1];
    int p=0;
    for(int i1=j;i1!=(increase(l,direction)+cycle_length)%cycle_length;i1=(increase(i1,direction)+cycle_length)%cycle_length)
    {
        temp[p]=s.path[i1];
        ++p;
    }
    for(int i1=(increase(k,direction)+cycle_length)%cycle_length;i1!=i;i1=(increase(i1,direction)+cycle_length)%cycle_length)
    {
        temp[p]=s.path[i1];
        ++p;
    }
    for(int i1=k;i1!=l;i1=(decrease(i1,direction)+cycle_length)%cycle_length)
    {
        temp[p]=s.path[i1];
        ++p;
    }
    for(int i1=(decrease(j,direction)+cycle_length)%cycle_length;i1!=i;i1=(decrease(i1,direction)+cycle_length)%cycle_length)
    {
        temp[p]=s.path[i1];
        ++p;
    }
    s.pathlength=p;
    for(int i1=0;i1<p;++i1)
    {
        s.path[i1]=temp[i1];
    }
    return s;
}

Solution US(Solution s,int p)
{
    if(p>s.pathlength-1) p=s.pathlength-1;
    int t=1;
    Solution s_star=s;
    for(int i=0;t<=s.pathlength+1;i=(i+1)%s.pathlength)
    {
        Solution temps=s_star;
        int tempv=INF;
        int Np[M][p];
        int Np_v[M][p];
        memset(Np,0x3f,sizeof(Np));
        memset(Np_v,0x3f,sizeof(Np_v));
        for(int i=0;i<M;++i)
        {
            for(int j=0;j<s.pathlength;++j)
            {
                if(i==s.path[j]) continue;
                for(int j1=0;j1<p;++j1)
                {
                    if(G[i][s.path[j]]<=Np_v[i][j1])
                    {
                        for(int k=p-2;k>=j1;--k)
                        {
                            Np[i][k+1]=Np[i][k];
                            Np_v[i][k+1]=Np_v[i][k];
                        }
                        Np[i][j1]=j;
                        Np_v[i][j1]=G[i][s.path[j]];
                        break;
                    }
                }
            }
        }
        int vip1=s.path[(i+1)%s.pathlength];//vi+1
        int vim1=s.path[(i-1+s.pathlength)%s.pathlength];//vi-1
        for(int j=0;j<p;++j)
        {
            for(int k=0;k<p;++k)
            {
                Solution _t=type1unstring(temps,i,Np[vip1][j],Np[vim1][k]);
                _t=GENI(_t,p);
                int _tempv=travelingCost(_t);
                if(_tempv<tempv)
                {
                    temps=_t;
                    tempv=_tempv;
                }
                _t=type1unstring(temps,i,Np[vim1][j],Np[vip1][k]);
                _t=GENI(_t,p);
                _tempv=travelingCost(_t);
                if(_tempv<tempv)
                {
                    temps=_t;
                    tempv=_tempv;
                }
                for(int l=0;l<p;++l)
                {
                    int vkp1=s.path[(Np[vim1][k]+1)%s.pathlength];
                    _t=type2unstring(temps,i,Np[vip1][j],Np[vim1][k],Np[vkp1][l]);
                    _t=GENI(_t,p);
                    int _tempv=travelingCost(_t);
                    if(_tempv<tempv)
                    {
                        temps=_t;
                        tempv=_tempv;
                    }
                    vkp1=s.path[(Np[vim1][k]-1+s.pathlength)%s.pathlength];
                    _t=type2unstring(temps,i,Np[vip1][j],Np[vim1][k],Np[vkp1][l]);
                    _t=GENI(_t,p);
                    _tempv=travelingCost(_t);
                    if(_tempv<tempv)
                    {
                        temps=_t;
                        tempv=_tempv;
                    }
                    vkp1=s.path[(Np[vip1][k]+1)%s.pathlength];
                    _t=type2unstring(temps,i,Np[vip1][j],Np[vim1][k],Np[vkp1][l]);
                    _t=GENI(_t,p);
                    _tempv=travelingCost(_t);
                    if(_tempv<tempv)
                    {
                        temps=_t;
                        tempv=_tempv;
                    }
                    vkp1=s.path[(Np[vip1][k]-1+s.pathlength)%s.pathlength];
                    _t=type2unstring(temps,i,Np[vip1][j],Np[vim1][k],Np[vkp1][l]);
                    _t=GENI(_t,p);
                    _tempv=travelingCost(_t);
                    if(_tempv<tempv)
                    {
                        temps=_t;
                        tempv=_tempv;
                    }
                }
            }
        }
        if(travelingCost(temps)<travelingCost(s_star))
        {
            s_star=temps;
        }else{
            ++t;
        }
    }
    return s_star;
}

Solution GENIUS(Solution s)
{
    //cout<<"traveling cost "<<travelingCost(s)<<endl;
    int plength=s.pathlength;
    s.pathlength=3;
    int p=8;
    s=GENI(s,p);
    //cout<<"traveling cost "<<travelingCost(s)<<endl;
    s=US(s,p);
    //cout<<"traveling cost "<<travelingCost(s)<<endl;

    if(s.pathlength!=plength)
    {
        cout<<"ERROR in GENIUS()!"<<endl;
    }
    int _0=0;
    for(int i=0;i<plength;++i)
    {
        if(s.path[i]==0)
        {
            _0=i;
            break;
        }
    }
    int _temp_p[plength];
    int _p=0;
    for(int i=_0;i<plength;++i)
    {
        _temp_p[_p]=s.path[i];
        ++_p;
    }
    for(int i=0;i<_0;++i)
    {
        _temp_p[_p]=s.path[i];
        ++_p;
    }
    for(int i=0;i<plength;++i)
    {
        s.path[i]=_temp_p[i];
    }
    return s;
}

int purchase_price(Solution s)
{
    int value=0;
    for(int k=0;k<K;++k)
    {
        int _p=INF;
        for(int i=1;i<M;++i)
        {
            if(s.market[i]==1 && P[i][k]!=0)
            {
                if(P[i][k]<_p){
                    _p=P[i][k];
                }
            }
        }
        value=value+_p;
    }
    if(value>INF)
    {
        return INF;
    }
    return value;
}

int M_star[MaxM];
void  budgetRestore(Solution &s,const int current_purchase_cost)
{
    const int _size=M*M+M;
    int purchase_cost[_size];
    int insertion_cost[_size];
    int purchase_cost_saving[_size];
    memset(purchase_cost_saving,0,sizeof(purchase_cost_saving));
    memset(purchase_cost,0x3f,sizeof(purchase_cost));
    memset(insertion_cost,0x3f,sizeof(insertion_cost));
    Solution temp[_size];
    memset(temp,0,sizeof(Solution));
    int p=0;
    for(int i=1;i<M;++i)
    {
        for(int j=1;j<M;++j)
        {
            if(s.market[i]==0 && s.market[j]==0)
            {
                for(int i1=1;i1<M;++i1)
                {
                    temp[p].market[i1]=s.market[i1];
                }
                temp[p].market[i]=1;
                temp[p].market[j]=1;
                purchase_cost[p]=purchase_price(temp[p]);
                //insertion cost
                //insert i
                int tempv=INF;
                int tempi=0;
                for(int i1=0;i1<s.pathlength-1;++i1)
                {
                    if(G[s.path[i1]][i]+G[i][s.path[i1+1]]<tempv)
                    {
                        tempv=G[s.path[i1]][i]+G[i][s.path[i1+1]];
                        tempi=i1;
                    }
                }
                for(int i1=0;i1<=tempi;++i1)
                {
                    temp[p].path[i1]=s.path[i1];
                }
                temp[p].path[tempi+1]=i;
                temp[p].pathlength=s.pathlength+1;
                for(int i1=tempi+1;i1<s.pathlength;++i1)
                {
                     temp[p].path[i1+1]=s.path[i1];
                }
                insertion_cost[p]=insertion_cost[p]+tempv;
                //insert j
                if(i!=j)
                {
                    tempv=INF;
                    tempi=0;
                    for(int i1=0;i1<temp[p].pathlength-1;++i1)
                    {
                        if(G[temp[p].path[i1]][j]+G[j][temp[p].path[i1+1]]<tempv)
                        {
                            tempv=G[temp[p].path[i1]][j]+G[j][temp[p].path[i1+1]];
                            tempi=i1;
                        }
                    }
                    for(int i1=temp[p].pathlength-1;i1>tempi;--i1)
                    {
                        temp[p].path[i1+1]=temp[p].path[i1];
                    }
                    temp[p].path[tempi+1]=j;
                    ++temp[p].pathlength;
                    insertion_cost[p]=insertion_cost[p]+tempv;
                }else{
                    purchase_cost_saving[p]=current_purchase_cost-purchase_cost[p];
                }
                ++p;
            }
        }
    }
    int tempv=INF;
    int tempi=-1;
    for(int i=0;i<p;++i)
    {
        if(purchase_cost[i]<=B && insertion_cost[i]<tempv)
        {
            tempv=insertion_cost[i];
            tempi=i;
        }
    }
    if(tempi!=-1)
    {
        s.pathlength=temp[tempi].pathlength;
        for(int i=1;i<M;++i)
        {
            s.market[i]=temp[tempi].market[i];
        }
        for(int i=0;i<s.pathlength;++i)
        {
            s.path[i]=temp[tempi].path[i];
        }
        return;
    }
    tempv=0;
    tempi=0;
    for(int i=0;i<p;++i)
    {
        if(purchase_cost_saving[i]>=tempv)
        {
            if(purchase_cost_saving[i]==tempv)
            {
                if(insertion_cost[i]<insertion_cost[tempi])
                {
                    tempv=purchase_cost_saving[i];
                    tempi=i;
                    continue;
                }
            }
            tempv=purchase_cost_saving[i];
            tempi=i;
        }
    }
    s.pathlength=temp[tempi].pathlength;
    for(int i=1;i<M;++i)
    {
        s.market[i]=temp[tempi].market[i];
    }
    for(int i=0;i<s.pathlength;++i)
    {
        s.path[i]=temp[tempi].path[i];
    }
    int ret=1;
    for(int i=1;i<M;++i)
    {
        if(s.market[i]==0)
        {
            ret=0;
        }
    }
    if(ret)
    {
        return;
    }
    int current=purchase_price(s);
    if(current>B)
    {
        budgetRestore(s,current);
    }
}

void getAll(Solution &s)
{
    int check[K];
    memset(check,0,sizeof(check));
    for(int i=1;i<M;++i)
    {
        if(s.market[i]==1)
        {
            for(int j=0;j<K;++j)
            {
                if(P[i][j]!=0)
                {
                    check[j]=1;
                }
            }
        }
    }
    int ret=1;
//    cout<<'k'<<' ';
    for(int i=0;i<K;++i)
    {
//        cout<<check[i]<<' ';
        if(check[i]==0)
        {
            ret=0;
        }
    }
//    cout<<endl;
    if(ret)
    {
        return;
    }
    int tempv=INF;
    int tempi=0;
    int tempj=0;
    for(int i=1;i<M;++i)
    {
        if(s.market[i]==0)
        {
            int tempv1=INF;
            int tempj1=0;
            for(int j=0;j<s.pathlength-1;++j)
            {
                if(G[s.path[j]][i]+G[i][s.path[j+1]]<tempv1)
                {
                    tempv1=G[s.path[j]][i]+G[i][s.path[j+1]];
                    tempj1=j;
                }
            }
            if(tempv1<tempv)
            {
                tempv=tempv1;
                tempi=i;
                tempj=tempj1;
            }
        }
    }
    s.market[tempi]=1;
    for(int i=s.pathlength-1;i>tempj;--i)
    {
        s.path[i+1]=s.path[i];
    }
    s.path[tempj+1]=tempi;
    ++s.pathlength;
    getAll(s);
}

Solution initial_sol()
{
    memset(M_star,0,sizeof(M_star));
    for(int i=1;i<M;++i)
    {
        int check[K];
        memset(check,0,sizeof(check));
        for(int j=1;j<M;++j)
        {
            if(i==j) continue;
            for(int k=0;k<K;++k)
            {
                if(P[j][k]!=0)
                {
                    check[k]=1;
                }
            }
        }
        int add=0;
        for(int k=0;k<K;++k)
        {
            if(check[k]==0)
            {
                add=1;
            }
        }
        if(add)
        {
            M_star[i]=1;
        }
    }

    Solution inisol;
    memset(&inisol,0,sizeof(Solution));
    int _m[M];
    int _p[K];
    memset(_m,0,sizeof(_m));
    memset(_p,0,sizeof(_p));
    for(int i=1;i<M;++i)
    {
        _m[i]=M_star[i];
    }
    for(int i=1;i<M;++i)
    {
        if(_m[i]!=0)
        {
            for(int j=0;j<K;++j)
            {
                if(P[i][j]!=0)
                {
                    _p[j]=1;
                }
            }
        }
    }
    for(int i=1;i<M;++i)
    {
        int finish=1;
        for(int j=0;j<K;++j)
        {
            if(_p[j]==0)
            {
                finish=0;
            }
        }
        if(finish)
        {
            break;
        }
        if(_m[i]==1) continue;
        _m[i]=1;
        for(int j=0;j<K;++j)
        {
            if(P[i][j]!=0)
            {
                _p[j]=1;
            }
        }
    }
//    for(int i=1;i<M;++i)
//    {
//        cout<<_m[i]<<' ';
//    }
//    cout<<endl;
//    for(int i=0;i<K;++i)
//    {
//        cout<<_p[i]<<' ';
//    }
//    cout<<endl;
for(int i=0;i<M;++i)
{
    inisol.market[i]=_m[i];
}
inisol.market[0]=1;
int pathlength=0;
for(int i=0;i<M;++i)
{
    if(inisol.market[i]!=0)
    {
        inisol.path[pathlength]=i;
        ++pathlength;
    }
}
inisol.pathlength=pathlength;
int current=purchase_price(inisol);
//cout<<current<<endl;
if(current>B)
{
    budgetRestore(inisol,current);
}
current=purchase_price(inisol);
//cout<<current<<endl;
return inisol;
}

Random r(1,10);

Solution randomIns(Solution s,int q)
{
    Solution retSol=s;
    int count0=0;
    for(int i=1;i<M;++i)
    {
        if(retSol.market[i]==0)
        {
            ++count0;
        }
    }
    if(q==0 || count0==0)
    {
        return retSol;
    }
    r.resetRange(1,count0);
    int p=int(r.getRandom()+0.5);
    count0=0;
    for(int i=1;i<M;++i)
    {
        if(retSol.market[i]==0)
        {
            ++count0;
            if(count0==p)
            {
                retSol.market[i]=1;
                int tempv=INF;
                int tempj=0;
                for(int j=0;j<retSol.pathlength-1;++j)
                {
                    if(G[retSol.path[j]][i]+G[i][retSol.path[j+1]]<tempv)
                    {
                        tempv=G[retSol.path[j]][i]+G[i][retSol.path[j+1]];
                        tempj=j;
                    }
                }
                for(int j=retSol.pathlength-1;j>tempj;--j)
                {
                    retSol.path[j+1]=retSol.path[j];
                }
                retSol.path[tempj+1]=i;
                ++retSol.pathlength;
                break;
            }
        }
    }
    return randomIns(retSol,q-1);
}

int checkFeasibility(Solution s)//0:infeasible
{
    int check[K];
    memset(check,0,sizeof(check));
    for(int i=1;i<M;++i)
    {
        if(s.market[i]==1)
        {
            for(int j=0;j<K;++j)
            {
                if(P[i][j]!=0)
                {
                    check[j]=1;
                }
            }
        }
    }
    int ret=0;
//    cout<<'k'<<' ';
    for(int i=0;i<K;++i)
    {
//        cout<<check[i]<<' ';
        if(check[i]==0)
        {
            ret=1;
        }
    }
    if(ret)
    {
        return 0;
    }
    if(purchase_price(s)>B)
    {
        return 0;
    }
    return 1;
}

Solution DRF(Solution s)
{
    int tempi;
    int p=8;
    int tempv=-1;
    int ret=1;
    for(int i=1;i<M;++i)
    {
        if(s.market[i]==1)
        {
            Solution temps=s;
            temps.market[i]=0;
            if(checkFeasibility(temps))
            {
                for(int j=0;j<temps.pathlength;++j)
                {
                    if(temps.path[j]==i)
                    {
                        if(j!=temps.pathlength-1)
                        {
                            int v1=G[temps.path[j-1]][i]+G[i][temps.path[j+1]];
                            int v2=G[temps.path[j-1]][temps.path[j+1]];
                            if(v1-v2>tempv)
                            {
                                ret=0;
                                tempv=v1-v2;
                                tempi=i;
                            }
                        }
                        if(j==temps.pathlength-1)
                        {
                            int v1=G[temps.path[j-1]][i]+G[i][0];
                            int v2=G[temps.path[j-1]][0];
                            if(v1-v2>tempv)
                            {
                                ret=0;
                                tempv=v1-v2;
                                tempi=i;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    if(ret)
    {
        return s;
    }
    if(tempv!=-1)
    {
        s.market[tempi]=0;
        for(int j=0;j<s.pathlength;++j)
        {
            if(s.path[j]==tempi)
            {
                if(j==s.pathlength-1)
                {
                    --s.pathlength;
                }else{
                    for(int k=j;k<s.pathlength-1;++k)
                    {
                        s.path[k]=s.path[k+1];
                    }
                    --s.pathlength;
                }
                break;
            }
        }
    }
    s=GENIUS(s);
    return DRF(s);
}

Solution improvement(Solution s, int l)
{
    //cout<<"IMPROVEMENT"<<endl;
    Solution temp[s.pathlength];
    memset(temp,0,sizeof(temp));
    int tcr[s.pathlength];//traveling cost reduction
    memset(tcr,0,sizeof(tcr));
    int s_tcost=travelingCost(s);
    int num=0;
    for(int i=0;i<s.pathlength-l-1;++i)
    {
        int jump=0;
        for(int j=1;j<=l;++j)
        {
            if(M_star[s.path[i+j]]==1)
            {
                jump=1;
                break;
            }
        }
        if(jump)
        {
            continue;
        }
        temp[num]=s;
        for(int j=1;j<=l;++j)
        {
            temp[num].market[temp[num].path[i+j]]=0;
        }
        for(int k=i+1;k<s.pathlength-l;++k)
        {
            temp[num].path[k]=temp[num].path[k+l];
        }
        temp[num].pathlength=temp[num].pathlength-l;
        if(!checkFeasibility(temp[num]))
        {
            getAll(temp[num]);
            budgetRestore(temp[num],purchase_price(temp[num]));
        }
        tcr[num]=s_tcost-travelingCost(temp[num]);
        //cout<<tcr[num]<<endl;
        ++num;
    }
    int tempi=-1;
    int tempv=0;
    for(int i=0;i<num;++i)
    {
        if(tcr[i]>tempv)
        {
            tempi=i;
            tempv=tcr[i];
        }
    }
    if(tempi!=-1)
    {
        return temp[tempi];
    }
    return s;
}

int cost(Solution s)
{
    return travelingCost(s)+purchase_price(s);
}

int minimum_purchase_price()
{
    Solution s;
    for(int i=0;i<M;++i)
    {
        s.market[i]=1;
    }
    return purchase_price(s);
}

Solution MVNS()
{
    Solution s=initial_sol();
    int q,qmax,qmin,qstep;
    int t,tmax;
    int l,lmax,lmin;
    int lpercent;
    Solution sVNS=GENIUS(s);
    qmax=M/5;
    qstep=2;
    qmin=1;
    tmax=5;
    lpercent=0.05;
    lmin=1;
    q=qmin;
    while(q<=qmax)
    {
        t=1;
        int _move=0;
        while(t<=tmax)
        {
            Solution s1=randomIns(sVNS,q);
            lmax=5;
            l=lmax;
            while(l>=lmin)
            {
                Solution s2=improvement(s1,l);
                if(cost(s2)<cost(s1))
                {
                    s1=s2;
                    lmax=5;
                    l=lmax;
                }else{
                    --l;
                }
            }
            Solution s2=DRF(s1);
            if(travelingCost(s2)<travelingCost(sVNS))
            {
                sVNS=s2;
                _move=1;
                t=tmax;
            }else{
                ++t;
            }
        }
        if(_move)
        {
            q=qmin;
        }else{
            q=q+qstep;
        }
    }
    return sVNS;
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
    read(argv[1],m,k,0);
    int b=minimum_purchase_price();
    B=b*i;
    time_t begin,end;
    cout<<"optimal object value: ";
    begin=clock();
    Solution s=MVNS();
    cout<<travelingCost(s);
    end=clock();
    cout<<endl;
    cout<<"time: ";
    cout<<double(end-begin)/CLOCKS_PER_SEC<<endl;
    return 0;
}
