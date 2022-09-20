// luogu-judger-enable-o2
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>

#define MX 200001
#define oo 1000000000

using namespace std;

class MinCostFlow
{

public:
    int fst[MX], nxt[MX * 2], u[MX * 2], v[MX * 2], w[MX * 2], c[MX * 2], lnum;
    int n, m, s, t;

    MinCostFlow() { init(); }

    void init()
    {
        memset(fst, 0xff, sizeof(fst));
        lnum = -1;
    }

    void addeg(int nu, int nv, int nw, int nc)
    {
        lnum++;
        nxt[lnum] = fst[nu];
        fst[nu] = lnum;
        u[lnum] = nu;
        v[lnum] = nv;
        w[lnum] = nw;
        c[lnum] = nc;
    }

    //滚动!!!

    int book[MX], q[MX], dist[MX], pre[MX], frnt, rare, now;
    int spfa(int frm, int to, int *flow, int *cost)
    {
        memset(dist, 0x3f, sizeof(dist));
        frnt = rare = 1;
        q[rare] = frm;
        dist[frm] = 0;
        book[frm] = 1;
        pre[frm] = -1;
        while (frnt >= rare)
        {
            book[q[rare]] = 0;
            now = q[rare++];
            for (int i = fst[now]; i != -1; i = nxt[i])
            {
                if (w[i] > 0 && dist[v[i]] > dist[now] + c[i])
                {
                    dist[v[i]] = dist[now] + c[i];
                    pre[v[i]] = i;
                    if (book[v[i]] == 0)
                    {
                        book[v[i]] = 1;
                        q[++frnt] = v[i];
                    }
                }
            }
        }
        if (dist[to] > +oo)
            return 0;
        int mxfl = +oo, mxcs = 0;
        now = pre[to];
        while (now != -1)
        {
            mxfl = min(mxfl, w[now]);
            mxcs += c[now];
            now = pre[u[now]];
        }
        now = pre[to];
        while (now != -1)
        {
            w[now] -= mxfl;
            w[now ^ 1] += mxfl;
            now = pre[u[now]];
        }
        *flow += mxfl;
        *cost += mxcs * mxfl;
        return 1;
    }

    int mincost_flow(int from, int to)
    {
        int flow = 0, cost = 0;
        while (spfa(from, to, &flow, &cost))
            ;
        return flow;
    }

    int get_flow_of_edge(int x, int y)
    {
        for (int i=fst[x]; i != -1; i=nxt[i])
        {
            if (u[i]==x && v[i]==y)
                return w[i^1];
        }
        return 0;
    }

    void hello()
    {
        printf("HELLO!");
    }
};

extern "C"
{
    // include below each method you want to make visible outside
    MinCostFlow *init() { return new MinCostFlow(); }
    void addeg(MinCostFlow *obj, int nu, int nv, int nw, int nc)
    {
        obj->addeg(nu, nv, nw, nc);
        obj->addeg(nv, nu, 0, -nc);
    }
    int mincost_flow(MinCostFlow *obj, int from, int to) { return obj->mincost_flow(from, to); }
    int get_flow_of_edge(MinCostFlow *obj, int x, int y) { return obj->get_flow_of_edge(x, y); }
    // __declspec(dllexport) void setInt(Test *self, int k) {self->setInt(k);}
    // __declspec(dllexport) int getInt(Test *self) {return self->getInt();}

    // Note: the '__declspec(dllexport)' is only necessary in Windows
}