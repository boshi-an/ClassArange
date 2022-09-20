// luogu-judger-enable-o2
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>

#define MX 50001
#define oo 1000000000

using namespace std;

class MinCostFlow{

    public:

    int fst[MX],nxt[MX*2],u[MX*2],v[MX*2],w[MX*2],c[MX*2],lnum;
    int n,m,s,t;

    MinCostFlow () {init();}

    void init()
    {
        memset(fst,0xff,sizeof(fst));
        lnum=-1;
    }

    void addeg(int nu,int nv,int nw,int nc)
    {
        lnum++;
        nxt[lnum]=fst[nu];
        fst[nu]=lnum;
        u[lnum]=nu;
        v[lnum]=nv;
        w[lnum]=nw;
        c[lnum]=nc;
    }

    //滚动!!!

    int book[MX],q[MX],dist[MX],pre[MX],frnt,rare,now;
    int spfa(int frm,int to,int *flow,int *cost)
    {
        memset(dist,0x3f,sizeof(dist));
        frnt=rare=1;
        q[rare]=frm;
        dist[frm]=0;
        book[frm]=1;
        pre[frm]=-1;
        while(frnt>=rare)
        {
            book[q[rare]]=0;
            now=q[rare++];
            for(int i=fst[now];i!=-1;i=nxt[i])
            {
                if(w[i]>0&&dist[v[i]]>dist[now]+c[i])
                {
                    dist[v[i]]=dist[now]+c[i];
                    pre[v[i]]=i;
                    if(book[v[i]]==0)
                    {
                        book[v[i]]=1;
                        q[++frnt]=v[i];
                    }
                }
            }
        }
        if(dist[to]>+oo)return 0;
        int mxfl=+oo,mxcs=0;
        now=pre[to];
        while(now!=-1)
        {
            mxfl=min(mxfl,w[now]);
            mxcs+=c[now];
            now=pre[u[now]];
        }
        now=pre[to];
        while(now!=-1)
        {
            w[now]-=mxfl;
            w[now^1]+=mxfl;
            now=pre[u[now]];
        }
        *flow+=mxfl;
        *cost+=mxcs*mxfl;
        return 1;
    }

    pair<int, int> mincost(int from,int to)
    {
        int flow=0,cost=0;
        while(spfa(from,to,&flow,&cost));
        return make_pair(flow, cost);
    }

};

extern "C" {
    MinCostFlow* newMinCostFlow(){ return new MinCostFlow(); }
}