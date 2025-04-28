#include <bits/stdc++.h>
#include "cyberland.h"

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define MASK(i) (1LL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()

ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}

ll LASTBIT(ll mask){return (mask) & (-mask);}
int pop_cnt(ll mask){return __builtin_popcountll(mask);}
int ctz(ll mask){return __builtin_ctzll(mask);}
int logOf(ll mask){return __lg(mask);}

mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
ll rngesus(ll l, ll r){return l + (ull) rng() % (r - l + 1);}

template <class T1, class T2>
    bool maximize(T1 &a, T2 b){
        if (a < b) {a = b; return true;}
        return false;
    }

template <class T1, class T2>
    bool minimize(T1 &a, T2 b){
        if (a > b) {a = b; return true;}
        return false;
    }

template <class T>
    void printArr(T& container, char separator = ' ', char finish = '\n'){
        for(auto item: container) cout << item << separator;
        cout << finish;
    }


template <class T>
    void remove_dup(vector<T> &a){
        sort(ALL(a));
        a.resize(unique(ALL(a)) - a.begin());
    }

struct P{
    int i; double w;
    P(){}
    P(int _i, double _w){i = _i, w = _w;}
};

struct compare{
    bool operator () (P a, P b){return a.w > b.w;}
};

const int N = 1e5 + 69;
const int K = 100;
const ll INF = 2e18 + 69;
const double EPS = 1e-6;
int h;
bool visited[N];
double dis[N];
vector<P> graph[N];

void dfs(int u){
    visited[u] = true;
    if (u == h) return;
    for(auto v: graph[u]) if (!visited[v.i]) dfs(v.i);
}

double solve(int n, int m, int k, int _h, vector<int> x, vector<int> y, vector<int> c, vector<int> arr) {
    h = _h;
    minimize(k, K);
    for(int i= 0; i<n; ++i){
        graph[i].clear();
        visited[i] = false;
        dis[i] = INF;
    }

    for(int i = 0; i<m; ++i){
        int u = x[i], v = y[i], w = c[i];
        graph[u].push_back(P(v, w));
        graph[v].push_back(P(u, w));
    }

    dfs(0);
    if (!visited[h]) return -1;

    priority_queue<P, vector<P>, compare> pq;
    for(int i = 0; i<n; ++i) if (visited[i] && (arr[i] == 0 || i == 0)){
        dis[i] = 0;
        pq.push(P(i, 0));
    }

    double ans = INF;
    for(int iteration = 0; iteration <= k; ++iteration){
        if (pq.empty()) break;
        while(pq.size()){
            P u = pq.top(); pq.pop();

            if (u.i == h) continue;
            if (dis[u.i] + EPS < u.w) continue;

            for(P v: graph[u.i]) if (minimize(dis[v.i], dis[u.i] + v.w)) 
                pq.push(P(v.i, dis[v.i]));
        }
        minimize(ans, dis[h]);

        vector<P> yap;
        for(int i = 0; i<n; ++i) if (visited[i]){
            if (arr[i] == 2) yap.push_back(P(i, dis[i] / 2));
            dis[i] = INF;
        }
        for(auto u: yap){
            for(P v: graph[u.i]) minimize(dis[v.i], u.w + v.w);
        }
        for(int i= 0; i<n; ++i) if (visited[i] && dis[i] < INF){
            pq.push(P(i, dis[i]));
        }
    }

    return ans;
}

// int main(void){
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//     cout << solve(4, 4, 30, 3, {0, 0, 1, 2}, {1, 2, 3, 3}, {5, 4, 2, 4}, {1, 0, 2, 1}) << "\n";

//     return 0;
// }
