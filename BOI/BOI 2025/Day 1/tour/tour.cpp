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

namespace FastIO{
    string buffer;
    vector<int> king;
    void init(int _n = 0){
        getline(cin, buffer, '\0');
        buffer += "\n";
        king.reserve(_n);
        int cur = 0;
        for(char c: buffer){
            if (c <= '9' && c >= '0'){
                if (cur == -1) cur = 0;
                cur = cur * 10 + (c - '0');
            }
            else{
                if (cur != -1) king.push_back(cur);
                cur = -1;
            }
        }
        
        reverse(ALL(king));
    }
    
    int read(){
        int u = king.back(); king.pop_back();
        return u;
    }
}
 

const int N = 1e6 + 69;
int n, m; 
vector<pair<int, int>> graph[N], rgraph[N];
int color[N];

bool cmp(pair<int, int> x, pair<int, int> y){
    return color[x.second] < color[y.second];
}


int z;
int visited[N * 3];
pair<int, int> actual_graph[N * 12];
pair<int, int> parent[N * 4];
int l[N * 3], r[N * 3];

int total_edge = 0;
void reset_everything(){
    for(int i = 1; i <= n; ++i){
        graph[i].clear();
        rgraph[i].clear();
    }
    for(int i = 1; i <= z; ++i){
        visited[i] = 0;
        l[i] = r[i] = 0;
    }
    total_edge = 0;
}

int a[N * 6], b[N * 6], c[N * 6];
void add_edge(int u, int v, int w){
    total_edge++;
    a[total_edge] = u;
    b[total_edge] = v;
    c[total_edge] = w;
    r[u]++;
}

void init_graph(){
    for(int i = 1; i <= z; ++i) {
        r[i] += r[i-1];
        l[i] = r[i-1];
    }
    for(int i = 1; i <= total_edge; ++i){
        int u = a[i], v = b[i], w = c[i];
        actual_graph[l[u]++] = make_pair(v, w);
    }
    for(int i = 1; i <= z; ++i) l[i] = r[i-1];
}

void dfs(int u, vector<int> &ans){
    if (visited[u] == 2) return;
    if (visited[u] == 1){
        int v = u;
        while(visited[v] == 1){
            visited[v] = 2;
            if (parent[v].second)
                ans.push_back(parent[v].second);
            v = parent[v].first;
        }
        return;
    }
    visited[u] = 1;
    for(int it = l[u]; it < r[u]; ++it) {
        pair<int,int> v = actual_graph[it];
        if (ans.size()) return;
        parent[v.first] = make_pair(u, v.second);
        dfs(v.first, ans);
    }
    visited[u] = 2;
}

void solve(){
    n = FastIO::read(), m = FastIO::read();
    for(int i = 1; i <= m; ++i){
        int u = FastIO::read(), v = FastIO::read(), w = FastIO::read();
        color[i] = w;
        graph[u].push_back({v, i});
        rgraph[v].push_back({u, i});
    }

    vector<pair<int, int>> vertices;
    vertices.push_back({-1, -1});
    for(int i = 1; i <= n; ++i){
        for(pair<int, int> j: rgraph[i]){
            vertices.push_back(make_pair(i, color[j.second]));
        }
    }
    remove_dup(vertices);
    z = vertices.size() - 1;

    for(int i = 1; i <= n; ++i){
        vector<int> sucky;
        for(pair<int, int> j: rgraph[i]){
            sucky.push_back(color[j.second]);
        }
        remove_dup(sucky);

        sort(ALL(graph[i]), cmp);

        int x = graph[i].size();
        vector<int> cox;
        for(pair<int, int> i: graph[i]) cox.push_back(color[i.second]);
        vector<int> pref(x), suff(x);
        for(int j = 0; j < x; ++j){
            pref[j] = ++z;
            suff[j] = ++z;

            int idx = lower_bound(ALL(vertices), make_pair(graph[i][j].first, cox[j])) - vertices.begin();
            add_edge(pref[j], idx, graph[i][j].second);
            add_edge(suff[j], idx, graph[i][j].second);
        }
        for(int j = 1; j < x; ++j) add_edge(pref[j], pref[j-1], 0); 
        for(int j = 0; j + 1 < x; ++j) add_edge(suff[j], suff[j+1], 0); 

        for(int j: sucky){
            pair<int, int> cur = make_pair(i, j);
            int u = lower_bound(ALL(vertices), cur) - vertices.begin();

            int v = lower_bound(ALL(cox), j) - cox.begin() - 1;
            if (v >= 0){
                add_edge(u, pref[v], 0);
            }
            v = upper_bound(ALL(cox), j) - cox.begin();
            if (v < (int) cox.size()){
                add_edge(u, suff[v], 0);
            }
        }
    }
    init_graph();

    vector<int> ans;
    for(int i = 1; i <= z; ++i) if (!visited[i]){
        dfs(i, ans);
        if (ans.size()){
            cout << "YES\n";
            cout << ans.size() << " ";
            reverse(ALL(ans));
            printArr(ans);
            reset_everything();
            return;
        }
    }


    cout << "NO\n";
    reset_everything();
}

int main(void){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);
 
    clock_t start = clock();

    FastIO::init(6e6);

    int t = FastIO::read();
    while(t--)
        solve();

    cerr << "Time elapsed: " << clock() - start << "ms!\n";
 
    return 0;
}