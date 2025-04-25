#include <bits/stdc++.h>
#include "train.h" 
 
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define MASK(i) (1LL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()
#define block_of_code if(true)
 
ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}
ll gcd(ll a, ll b){return __gcd(a, b);}
ll lcm(ll a, ll b){return a / gcd(a, b) * b;}
 
ll LASTBIT(ll mask){return (mask) & (-mask);}
int pop_cnt(ll mask){return __builtin_popcountll(mask);}
int ctz(ull mask){return __builtin_ctzll(mask);}
int logOf(ull mask){return 63 - __builtin_clzll(mask);}
 
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
    void printArr(T container, string separator = " ", string finish = "\n", ostream &out = cout){
        for(auto item: container) out << item << separator;
        out << finish;
    }
 
template <class T>
    void remove_dup(vector<T> &a){
        sort(ALL(a));
        a.resize(unique(ALL(a)) - a.begin());
    }
 
 
const ll INF = 1e18 + 69;
const int INF_T = 1e9 + 69;
const int N = 1e5 + 65;
const int BLOCK = 2000;
 
struct FenwickTree{
    const int BLOCK = 500;
    int n;
    vector<int> a, b_sum;
 
    FenwickTree(int _n){
        n = _n;
        a.resize(n+1);
        b_sum.resize(n / BLOCK + 2);
    }
 
    void update(int i, int v){
        int m = i % BLOCK;
        while(m--)
            a[i--] += v;
        i /= BLOCK;
        while(i) b_sum[i--] += v;
    }
 
    int get(int i){
        int ans = a[i] + b_sum[(i-1) / BLOCK + 1];
        return ans;
    }
};
 
struct SegmentTree{
    #define SZ MASK(19)
    int n, t;
    array<ll, SZ> a;
    array<int, SZ> lazy;
 
    SegmentTree(int _n, int _t){
        n = _n, t = _t;
        for(int i = 0; i < SZ; ++i) {
            a[i] = INF;
            lazy[i] = 0;
        }
    }
 
    void down(int id){
        #define cuhh(i) {lazy[i] += lazy[id]; a[i] += 1LL * t * lazy[id];}
        cuhh(id * 2); cuhh(id * 2 + 1);
        lazy[id] = 0;
    }
 
    void add(int u, int v, int l, int r, int id){
        if (u <= l && r <= v){
            a[id] += t;
            lazy[id] += 1;
            return;
        }
        if (lazy[id]) down(id);
        int mid = (l + r) >> 1;
        if (u <= mid) add(u, v, l, mid, id * 2);
        if (v > mid) add(u, v, mid + 1, r, id * 2 + 1);
        a[id] = min(a[id * 2], a[id * 2 + 1]);
    }
 
    void add(int u, int v){
        if (u <= v) add(u, v, 1, n, 1);
    }
 
 
    ll get(){return a[1];}
 
    void update(int i, ll val){
        int l = 1, r = n, id = 1;
        while(l < r){
            minimize(a[id], val);
            if (lazy[id]) down(id);
            int mid = (l + r) >> 1;
            if (i <= mid){
                r = mid;
                id = id * 2;
            }
            else{
                l = mid + 1;
                id = id * 2 + 1;
            }
        }
        minimize(a[id], val);
    }
}; 
 
vector<pair<int,ll>> relevant_time[N];
vector<pair<int, int>> graph[N * 2];
 
ll solve(int n, int m, int w, vector<int> t, 
                vector<int> x, vector<int> y, vector<int> a, vector<int> b, vector<int> c, 
                vector<int> l, vector<int> r) {
 
    vector<int> timeline = {-1, 0, INF_T};
    for(int i = 0; i<m; ++i){
        timeline.push_back(a[i]);
        timeline.push_back(b[i]);
    }
    remove_dup(timeline);
 
    for(int i= 0; i<m; ++i){
        a[i] = lower_bound(ALL(timeline), a[i]) - timeline.begin();
        b[i] = lower_bound(ALL(timeline), b[i]) - timeline.begin();
    }
 
    vector<pair<int, int>> relevant_pair;
    for(int i = 0; i<m; ++i){
        relevant_pair.push_back({a[i], x[i]});
        relevant_pair.push_back({b[i], y[i]});
    }
    relevant_pair.push_back({1, 0});
    relevant_pair.push_back({timeline.size() - 1, n-1});
    remove_dup(relevant_pair);
 
    vector<int> des_cnt(n);
    for(int i = 0; i<m; ++i) des_cnt[y[i]]++;
 
    vector<int> big_boys;
    vector<SegmentTree> st;
    for(int i = 0; i<n; ++i) if (des_cnt[i] > BLOCK){
        big_boys.push_back(i);
        st.push_back(SegmentTree(timeline.size() - 1, t[i]));
    }
 
    for(int i = 0; i<m; ++i){
        pair<int, int> u = {a[i], x[i]}, v = {b[i], y[i]};
        int idx1 = lower_bound(ALL(relevant_pair), u) - relevant_pair.begin();
        int idx2 = lower_bound(ALL(relevant_pair), v) - relevant_pair.begin();
        graph[idx2].push_back({idx1, c[i]});
    }
 
    vector<pair<int, int>> range;
    for(int i = 0; i<w; ++i) {
        r[i] = upper_bound(ALL(timeline), r[i]) - timeline.begin() - 1;
        l[i] = lower_bound(ALL(timeline), l[i]) - timeline.begin() - 1;
        range.push_back({l[i], r[i]});
    }
    sort(ALL(range), [](pair<int,int> x, pair<int, int> y){
        return x.second > y.second;
    });
 
    FenwickTree bit(timeline.size() - 1);
 
    vector<ll> dis(relevant_pair.size(), INF), dp = dis;
    dis[0] = dp[0] = 0;
    for(int i = 0; i < relevant_pair.size(); ++i){
        pair<int, int> u = relevant_pair[i];
        while(range.size() && u.first > range.back().second){
            pair<int, int> cur = range.back(); range.pop_back();
            bit.update(cur.first, 1);
            for(int j = 0; j < big_boys.size(); ++j){
                st[j].add(1, cur.first);
            }
        }
        for(pair<int, int> j: graph[i]) {
            minimize(dis[i], dis[j.first] + j.second);
            minimize(dp[i], dis[j.first] + j.second);
        }
        if (des_cnt[u.second] <= BLOCK){
            for(pair<int, ll> j: relevant_time[u.second]){
                ll cur = j.second;
                cur += 1LL * bit.get(j.first) * t[u.second];
                minimize(dis[i], cur);
            }
            if (dp[i] < INF) {
                relevant_time[u.second].push_back({u.first, dp[i]});
            }
        }
        else{
            int idx = lower_bound(ALL(big_boys), u.second) - big_boys.begin();
            minimize(dis[i], st[idx].get());
            if (dp[i] < INF) {
                st[idx].update(u.first, dp[i]);
            }
        }
    }
 
    if (dis.back() == INF) return -1;
    return dis.back();
}