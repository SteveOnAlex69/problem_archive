#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define MASK(i) (1ULL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()
 
ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}
ll gcd(ll a, ll b){return __gcd(abs(a), abs(b));}
ll lcm(ll a, ll b){return abs(a) / gcd(a, b) * abs(b);}
 
ll LASTBIT(ll mask){return (mask) & (-mask);}
int pop_cnt(ull mask){return __builtin_popcountll(mask);}
int ctz(ull mask){return __builtin_ctzll(mask);}
int logOf(ull mask){return 63 - __builtin_clzll(mask);}
 
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
mt19937_64 rng(1);
ll rngesus(ll l, ll r){return l + (ull) rng() % (r - l + 1);}
double rngesus_d(double l, double r){
    double cur = rngesus(0, MASK(60) - 1);
    cur /= MASK(60) - 1;
    return l + cur * (r - l);
}
 
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
    void printArr(T container, string separator = " ", string finish = "\n", ostream &out = cout){
        for(auto item: container) out << item << separator;
        out << finish;
    }
 
template <class T>
    void remove_dup(vector<T> &a){
        sort(ALL(a));
        a.resize(unique(ALL(a)) - a.begin());
    }

struct DSU{
    int n;
    vector<int> parent, sz;

    DSU(int _n){
        n = _n;
        parent.resize(n+1); sz.resize(n+1, 1);
        for(int i = 1; i<=n; ++i) parent[i] = i;
    }

    int find_set(int u){return (u == parent[u]) ? u : (parent[u] = find_set(parent[u]));}
    bool same_set(int u, int v){return find_set(u) == find_set(v);}

    bool join_set(int u, int v){
        u = find_set(u), v = find_set(v);
        if (u != v){
            if (sz[u] < sz[v]) swap(u, v);
            parent[v] = u;
            sz[u] += sz[v];
            return true;
        }
        return false;
    }

    int get_size(int u){return sz[find_set(u)];}
};

const int N = 30003;
int n, k, sum2;
vector<pair<int, int>> graph[N * 2];
int visited[N * 2];
pair<int, int> parent[N * 2];
vector<int> cycle;

void dfs(int u, int p){
    if (visited[u] == 2) return;
    if (visited[u] == 1){
        int v = u;
        while(visited[v] == 1){
            visited[v] = 2;
            cycle.push_back(v);
            if (v > n) sum2 -= parent[v].second;
            else sum2 += parent[v].second;
            v = parent[v].first;
        }
        return;
    }
    visited[u] = 1;
    for(pair<int, int> v: graph[u]) {
        if (v.first == p) {
            p = -1;
            continue;
        }
        parent[v.first] = {u, v.second};
        dfs(v.first, u);
    }
    visited[u] = 2;
}

bool banned[N * 2];

int get_sum(int u, int p, int w){
    int sum = 0;
    if (u > n) sum -= w;
    else sum += w;
    for(pair<int, int> v: graph[u]) if (v.first != p){
        sum += get_sum(v.first, u, v.second);
    }
    return sum;
}

bitset<N*20+1> dp;

bool solve(){
    cin >> n >> k;
    vector<array<int, 3>> arr;
    DSU mst(n * 2);
    for(int i = 0; i < 2*n; ++i){
        int l, r, k; cin >> l >> r >> k;
        r += n;
        mst.join_set(l, r);
        arr.push_back({{l, r, k}});
    }

    sort(ALL(arr));

    vector<int> sum(n*2+1);
    for(int i= 0; i < 2*n; ++i){
        int u = arr[i][0], v = arr[i][1], w = arr[i][2];
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});

        sum[mst.find_set(arr[i][0])]++;
    }

    for(int i = 1; i <= 2 * n; ++i) if (i == mst.find_set(i)){
        if (mst.get_size(i) != sum[i]) return false;
    }

    int tot = 0;
    vector<int> sum_list;
    for(int i = 1; i <= 2 * n; ++i) if (mst.find_set(i) == i){
        sum2 = 0;
        dfs(i, 0);
        sum_list.push_back(abs(sum2));
        tot -= abs(sum2);
        for(int j: cycle) banned[j] = true;

        for(int j: cycle){
            for(pair<int, int> k: graph[j]) if (!banned[k.first]){
                tot += get_sum(k.first, j, k.second);
            }
        }

        cycle.clear();
    }
    sort(ALL(sum_list));

    dp[0] = 1;
    for(int i: sum_list){
        dp |= (dp << i);
    }

    for(int i = 0; i < N*20+1; ++i) if (dp[i]){
        int cur = tot + i * 2;
        if (abs(cur) <= k) return true;
    }

    return false;
}

int main(void){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);
 
    clock_t start = clock();

    if (solve()) cout << "YES\n";
    else cout << "NO\n";

    cerr << "Time elapsed: " << clock() - start << "ms!\n";
 
    return 0;
}