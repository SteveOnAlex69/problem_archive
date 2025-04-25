#include <bits/stdc++.h>
#include "Alice.h"
 
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
 
ll setN(ll n){
    cerr << n << "\n";
    ll x; cin >> x;
    return x;
}
 
vector<pair<int, int>> Alice(){
    int n = 1000;
    ll x = setN(n);
    vector<pair<int,int>> ans;
    for(int i = 2; i<=n; ++i) {
        ans.push_back({x % (i-1) + 1, i});
    }
    return ans;
}
 
// int main(void){
//     ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
//     freopen("transfer.txt", "w", stdout);
 
//     vector<pair<int, int>> bru = Alice();
 
//     cout << bru.size() << "\n";
//     for(pair<int, int> i: bru) cout << i.first << " " << i.second << "\n";
 
//     return 0;
// }