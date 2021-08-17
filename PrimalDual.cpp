#include<bits/stdc++.h>

template<typename Cap, typename Cost> class PrimalDual{
    // グラフがDAGなら負辺があっても初期ポテンシャルの計算がDPで求められるので
    // O(|F|m log n)で求められる
public:
    struct edge{
        int to, rev;
        Cap cap;
        Cost cost;
        bool isrev;
        edge(int to, int rev, Cap cap, Cost cost, bool isrev):to(to),rev(rev),cap(cap),cost(cost), isrev(isrev){}
    };
    const int V;
    const Cost inf;
    bool has_neg_edge;
    std::vector<std::vector<edge>> G;
    std::vector<Cost> h, dist;
    std::vector<int> deg, ord, prevv, preve;
    using pti = std::pair<Cost,int>;
    PrimalDual(const int node_size): V(node_size), inf(std::numeric_limits<Cost>::max()),
     G(V), h(V, 0), dist(V), deg(V, 0), prevv(V), preve(V), has_neg_edge(false){}
    
    void add_edge(const int from, const int to, const Cap cap, const Cost cost){
        assert(0 <= from && from < V);
        assert(0 <= to && to < V);
        assert(0 <= cap);
        G[from].emplace_back(to, G[to].size(), cap, cost, false);
        G[to].emplace_back(from, G[from].size()-1, 0, -cost, true);
        if(cost < 0)has_neg_edge = true;
        ++deg[to];
    }
    bool topological_sort(){
        std::queue<int> que;
        for(int i = 0; i < V; ++i){
            if(deg[i] == 0)que.push(i);
        }
        while(!que.empty()){
            const int p = que.front();que.pop();
            ord.emplace_back(p);
            for(const edge& e: G[p]){
                if(e.cap > 0 && --deg[e.to] == 0)que.push(e.to);
            }
        }
        return (*std::max_element(deg.begin(), deg.end()) == 0);
    }

    void calc_potential(const int s){
        h[s] = 0;
        for(const int v: ord){
            if(h[v] == inf)continue;
            for(const edge& e: G[v]){
                if(e.cap > 0)h[e.to] = std::min(h[e.to], h[v] + e.cost);
            }
        }
    }

    void Dijkstra(const int s){
        std::priority_queue<pti, std::vector<pti>, std::greater<pti>> que;
        fill(dist.begin(), dist.end(), inf);
        dist[s] = 0;
        que.emplace(0, s);
        while(!que.empty()){
            auto [cost, v] = que.top();que.pop();
            if(dist[v] < cost)continue;
            for(int i = 0; i < G[v].size(); ++i){
                edge& e = G[v][i];
                if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]){
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v, preve[e.to] = i;
                    que.emplace(dist[e.to], e.to);
                }
            }
        }
    }

    void update(const int s, const int t, Cap& f, Cost& res){
        for(int i = 0; i < V; ++i){
            if(dist[i] != inf)h[i] += dist[i];
        }
        Cap d = f;
        for(int v = t; v != s; v = prevv[v]){
            d = std::min(d, G[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += h[t] * d;
        for(int v = t; v != s; v = prevv[v]){
            edge& e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    Cost min_cost_flow(int s, int t, Cap f){
        if(has_neg_edge){
            fill(h.begin(), h.end(), inf);
            if(!topological_sort())assert(false);
            calc_potential(s);
        }
        Cost res = 0;
        while(f > 0){
            Dijkstra(s);
            if(dist[t] == inf)return -1;
            update(s, t, f, res);
        }
        return res;
    }

    void print(){
        for(int i = 0; i < G.size()){
            for(auto &e: G[i]){
                if(e.isrev)continue;
                auto &rev_e = G[e.to][e.rev];
                std::cout << i << "->" << e.to << " (flow: " << rev_e.cap << "/" << rev_e.cap + e.cap << ")" << std::endl;
            }
        }
    }
};

// https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_B
int main(){
    int n,m,f;std::cin >> n >> m >> f;
    PrimalDual<int,int> pd(n);
    for(int i = 0; i < m; ++i){
        int u,v,c,d;std::cin >> u >> v >> c >> d;
        pd.add_edge(u, v, c, d);
    }
    std::cout << pd.min_cost_flow(0, n-1, f) << std::endl;
    pd.print();
}