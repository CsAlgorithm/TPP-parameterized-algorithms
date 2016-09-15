#ifndef INSTANCE_ACCESS_H_INCLUDED
#define INSTANCE_ACCESS_H_INCLUDED

#include <string>
#include <strstream>
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

int get_instance(int *&graph, int *&product_distribution, int m,int k,char *p)
{
    graph=new int[m*m];
    product_distribution=new int[m*k];
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<m;++j)
        {
            graph[i*m+j]=0;
        }
    }
    for(int i=0;i<m;++i)
    {
        for(int j=0;j<k;++j)
        {
            product_distribution[i*k+j]=0;
        }
    }
    ifstream fin;
    fin.open(p);
    if(fin.is_open())
    {
        string s;
        while(fin>>s)
        {
            if(s=="NODE_COORD_SECTION")
            {
                fin>>s;
                int num;
                double x[m];
                double y[m];
                for(int i=0;i<m;++i)
                {
                    fin>>num;
                    fin>>x[i];
                    fin>>y[i];
                }
                for(int i=0;i<m;i++)
                {
                    for(int j=0;j<m;j++)
                    {
                        double xd=x[i]-x[j];
                        double yd=y[i]-y[j];
                        int d=(int)(sqrt(xd*xd+yd*yd)+0.5);
                        graph[i*m+j]=d;
                    }
                }
            }
            if(s=="OFFER_SECTION")
            {
                fin>>s;
                int id;
                int num=0;
                for(int i=0;i<m;++i)
                {
                    fin>>id;
                    fin>>num;
                    int product_id;
                    int cost;
                    int dem;
                    for(int j=0;j<num;++j)
                    {
                        fin>>product_id;
                        fin>>cost;
                        product_distribution[i*k+product_id-1]=cost;
                        fin>>dem;
                    }
                }
            }
        }
        return 1;
    }else{
     return 0;
    }
}
#endif // INSTANCE_ACCESS_H_INCLUDED
