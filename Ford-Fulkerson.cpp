#include<bits/stdc++.h>

template<class Cap>
struct Ford_Fulkerson{
    public:
        struct edge{
            int to, rev; 
            Cap cap;
            edge(int to, Cap cap, int rev):to(to),cap(cap),rev(rev){}
        };

        Ford_Fulkerson():_n(0){}
        Ford_Fulkerson(int n):_n(n),G(n), used(n){};

        void add_edge(int from, int to, Cap cap){
            assert(0 <= from && from < _n && 0 <= to && to < _n);
            G[from].emplace_back(to, cap, G[to].size());
            G[to].emplace_back(from, 0, G[from].size() - 1);
        }

        int dfs(int v, int t, Cap f){
            if(v == t)return f;
            used[v] = true;
            for(int i = 0; i < G[v].size(); i++){
                edge &e = G[v][i];
                if(!used[e.to] && e.cap > 0){
                    Cap d = dfs(e.to, t, std::min(f, e.cap));
                    if(d > 0){
                        e.cap -= d;
                        G[e.to][e.rev].cap += d;
                        return d;
                    }
                }
            }
            return 0;
        }

        Cap max_flow(int s, int t){
            Cap flow = 0;
            for(;;){
                fill(used.begin(), used.end(), false);
                Cap f = dfs(s, t, INF);
                if(f == 0)return flow;
                flow += f;
            }
        }
    private:
        int _n;
        const int INF = std::numeric_limits<Cost>::max();
        std::vector<std::vector<edge>> G;
        std::vector<bool> used;   
};


void solve(){
    // https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_A
    int V,e;std::cin >> V >> e;
    Ford_Fulkerson<int> ff(V);
    for(int i = 0; i < e; i++){
        int u,v,c;std::cin >> u >> v >> c;
        ff.add_edge(u,v,c);
    }
    std::cout << ff.max_flow(0, V-1) << '\n';
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);
    //cout << setprecision(20);
    int codeforces = 1;
    //cin >> codeforces;
    while(codeforces--){
        solve();
    }
    return 0;
}