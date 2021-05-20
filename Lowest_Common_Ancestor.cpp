#pragma once
#include<bits/stdc++.h>

template <typename G>
struct DoublingLowestCommonAncestor // ex) DoublingLowestCommonAncestor<vector<vector<int>>> lca(g)
{
    const int LOG;
    vector<int> dep;
    const G &g;
    vector<vector<int>> table;
    vector<int> ord;

    DoublingLowestCommonAncestor(const G &g) : g(g), dep(g.size()), ord(g.size()), LOG(32 - __builtin_ctz(g.size()))
    {
        table.assign(LOG, vector<int>(g.size(), -1));
        build();
    }

    void dfs(int idx, int par, int d, int& num)
    {
        table[0][idx] = par;
        dep[idx] = d;
        ord[idx] = num++;
        for (auto &to : g[idx])
        {
            if (to != par)
                dfs(to, idx, d + 1, num);
        }
    }

    void build()
    {   
        int num = 0;
        dfs(0, -1, 0, num);
        for (int k = 0; k + 1 < LOG; k++)
        {
            for (int i = 0; i < table[k].size(); i++)
            {
                if (table[k][i] == -1)
                    table[k + 1][i] = -1;
                else
                    table[k + 1][i] = table[k][table[k][i]];
            }
        }
    }

    int query(int u, int v)
    {
        if (dep[u] > dep[v])
            swap(u, v);
        for (int i = LOG - 1; i >= 0; i--)
        {
            if (((dep[v] - dep[u]) >> i) & 1)
                v = table[i][v];
        }
        if (u == v)
            return u;
        for (int i = LOG - 1; i >= 0; i--)
        {
            if (table[i][u] != table[i][v])
                {
                u = table[i][u];
                v = table[i][v];
                }
        }
        return table[0][u];
    }
    
    int dist(int u, int v){
        int w = query(u,v);
        return dep[u] + dep[v] - 2*dep[w];
    }
};