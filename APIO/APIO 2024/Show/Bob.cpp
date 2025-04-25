#include <bits/stdc++.h>
#include "Bob.h"
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define MASK(i) (1ULL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()
 
ll max(ll a, ll b){return (a > b) ? a : b;}
ll min(ll a, ll b){return (a < b) ? a : b;}
ll gcd(ll a, ll b){return __gcd(a, b);}
 
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
 
const ll INF = 2e18;
 
ll Bob(vector<pair<int, int>> E){
    int n = 1000;
    vector<int> par(n+1, -1);
    for(pair<int, int> i: E){
        if (i.first > i.second) swap(i.first, i.second);
        par[i.second] = i.first;
    }
 
    ll x = 0;
    ll mud = 1;
 
    for(int i = 3; i <= n; ++i) if (par[i] != -1){
        int r = par[i] - 1, m = i - 1;
        while(x % m != r){
            x += mud;
        }
 
        mud /= gcd(mud, m);
        if (INF / mud <= m){
            break;
        }
        mud *= m;
    }
 
    return x;
}
 
// int main(void){
//     ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
 
//     freopen("transfer.txt", "r", stdin);
 
//     int m; cin >> m;
//     vector<pair<int, int>> E;
//     for(int i = 0; i<m; ++i){
//         int u, v; cin >> u >> v;
//         E.push_back({u, v});
//     }
//     cout << Bob(E) << "\n";
 
//     return 0;
// }