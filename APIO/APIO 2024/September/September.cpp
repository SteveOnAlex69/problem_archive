#include <bits/stdc++.h>
#include "september.h"
 
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
 
int solve(int n, int m, vector<int> F, vector<vector<int>> S){
    vector<vector<int>> graph(n);
    for(int i = 1; i<n; ++i){
        graph[F[i]].push_back(i);
    }
 
    int perm_diff = 0;
    vector<int> cnt(n);
 
    vector<bool> visited(n);
    int inversion_cnt = 0;
 
    int ans = 0;
    for(int i = 0; i < n-1; ++i){
        int x = S[0][i];
        if (visited[F[x]]) inversion_cnt--;
        visited[x] = 1;
        for(int y: graph[x]) if (!visited[y]) inversion_cnt++;
 
        for(int j = 0; j < m; ++j){
            int x = S[j][i];
            if (cnt[x] == 0) perm_diff++;
            cnt[x]++;
            if (cnt[x] == m) perm_diff--;
        }
 
        if (perm_diff == 0 && inversion_cnt == 0) ans++;
    }
    return ans;
}
 
// int main(void){
//     ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
//     cout << solve(5, 2, {-1, 0, 0, 1, 1}, {{1, 2, 3, 4}, {4, 1, 2, 3}}) << "\n";
 
//     return 0;
// }