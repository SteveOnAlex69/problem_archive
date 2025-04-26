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

// #include "tower.h"

vector<pair<int,int>> ask(int i, int j, int k){
    cout << "? " << i << " " << j << " " << k << endl;
    int n; cin >> n;
    vector<pair<int, int>> arr;
    for(int i = 0; i < n; ++i){
        int u, v; cin >> u >> v;
        arr.push_back({u, v});
    }
    return arr;
}

void answer(vector<int> v){
    cout << "! "; printArr(v);
    cout.flush();
}
int t, k; 

namespace Sub1{
    void solve(int n){
        vector<int> ans(n);
        vector<bool> check(n);
        check[0] = 1;
        for(int i = 1; i < n; ++i){
            int u = ans[i-1], v = -1;
            for(int j = 0; j < n; ++j) if (!check[j]){
                if (v == -1) {
                    v = j;
                    continue;
                }
                vector<pair<int, int>> ans = ask(u, v, j);
                for(pair<int, int> k: ans){
                    if (k.first != u) swap(k.first, k.second);
                    if (k.first == u){
                        v = k.second;
                        break;
                    }
                }
            }
            ans[i] = v;
            check[v] = true;
        }
        answer(ans);

    }
}

namespace Sub2{
    void solve(int n, int BLOCK){
        vector<int> ans(n);
        vector<bool> check(n);
        check[0] = 1;
        for(int i = 1; i <= BLOCK; ++i){
            int u = ans[i-1], v = -1;
            for(int j = 0; j < n; ++j) if (!check[j] && j != v){
                if (v == -1){
                    v = j;
                    continue;
                }
                vector<pair<int, int>> ans = ask(u, v, j);
                for(pair<int, int> k: ans){
                    if (k.first != u) swap(k.first, k.second);
                    if (k.first == u){
                        v = k.second;
                        break;
                    }
                }
            }
            ans[i] = v;
            check[v] = true;
        }

        int i = BLOCK + 1;
        vector<int> perm(n);
        for(int i = 0; i < n; ++i) perm[i] = i;
        while(i < n){
            vector<int> pending;
            int u = ans[i - BLOCK], v = ans[i - 1];
            for(int j = 0; j < n; ++j) if (!check[j]){
                vector<pair<int, int>> ans = ask(u, v, j);
                for(pair<int, int> k: ans){
                    if (k == make_pair(u, v) || k == make_pair(v, u)) continue;
                    if (k.first != v) swap(k.first, k.second);
                    if (k.first == v){
                        pending.push_back(k.second);
                    }
                }
            }
            for(int it = 0; it < (int) pending.size(); ++it){
                int u = ans[i-1], v = -1;
                for(int j:pending) if (!check[j]){
                    if (v == -1){
                        v = j;
                        continue;
                    }
                    vector<pair<int, int>> ans = ask(u, v, j);
                    for(pair<int, int> k: ans){
                        if (k.first != u) swap(k.first, k.second);
                        if (k.first == u){
                            v = k.second;
                            break;
                        }
                    }
                }
                ans[i++] = v;
                check[v] = true;
            }
        }
        answer(ans);

    }
}


namespace Sub3{
    void solve(int n, int BLOCK){
        vector<int> ans(n);
        vector<bool> check(n);

        for(int i = 0; i < 200; ++i) {
            ans[i] = i + 200;
            check[ans[i]] = 1;
        }

        int i = 200;
        while(i < n){
            vector<int> pending;
            int u = ans[i - BLOCK], v = ans[i - 1];
            for(int j = 0; j < n; ++j) if (!check[j]){
                vector<pair<int, int>> ans = ask(u, v, j);
                for(pair<int, int> k: ans){
                    if (k == make_pair(u, v) || k == make_pair(v, u)) continue;
                    if (k.first != v) swap(k.first, k.second);
                    if (k.first == v){
                        pending.push_back(k.second);
                    }
                }
            }
            for(int it = 0; it < (int) pending.size(); ++it){
                int u = ans[i-1], v = -1;
                for(int j:pending) if (!check[j]){
                    if (v == -1){
                        v = j;
                        continue;
                    }
                    vector<pair<int, int>> ans = ask(u, v, j);
                    for(pair<int, int> k: ans){
                        if (k.first != u) swap(k.first, k.second);
                        if (k.first == u){
                            v = k.second;
                            break;
                        }
                    }
                }
                ans[i++] = v;
                check[v] = true;
            }
        }
        answer(ans);

    }
}


namespace Sub4{
    void dnc(vector<int> &ans, vector<bool> &check, vector<int> pending, int l, int r){
        if (pending.size() == 1){
            ans[r + 1] = pending[0];
            check[ans[r + 1]] = true;
            return;
        }
        int mid = (l + r) >> 1;
        int po = r - mid;
        vector<int> left, right;
        for(int j: pending){
            if ((int) left.size() == po){
                right.push_back(j);
                continue;
            }
            if ((int) right.size() == po){
                left.push_back(j);
                continue;
            }
            int u = ans[mid], v = ans[r];
            vector<pair<int,int>> arr = ask(u, v, j);

            bool check = false;
            for(auto k: arr){
                if (k == make_pair(u, v) || k == make_pair(v, u)) continue;
                if (k.first != v) swap(k.first, k.second);
                if (k.first == v){
                    check = true;
                    break;
                }
            }
            if (check) left.push_back(j);
            else right.push_back(j);
        }
        dnc(ans, check, left, mid, r);
        dnc(ans, check, right, r, r + po);
    }

    void solve(int n){
        vector<int> ans(n);
        vector<bool> check(n);
        check[0] = 1;
        vector<int> perm(n);
        for(int i = 0; i < n; ++i) perm[i] = i;
        shuffle(ALL(perm), rng);
        for(int i = 1; i <= 1; ++i){
            int u = ans[i-1], v = -1;
            for(int j = 0; j < n; ++j) if (!check[j] && j != v){
                if (v == -1){
                    v = j;
                    continue;
                }
                vector<pair<int, int>> ans = ask(u, v, j);
                for(pair<int, int> k: ans){
                    if (k.first != u) swap(k.first, k.second);
                    if (k.first == u){
                        v = k.second;
                        break;
                    }
                }
            }
            ans[i] = v;
            check[v] = true;
        }

        for(int i = 1; i + 1 < n; ){
            int po = 1;
            while(true){
                if (po * 2 > i) break;
                if (i + po * 2 >= n) break;
                po *= 2;
            }
            int u = ans[i - po], v = ans[i];
            vector<int> pending;
            for(int j: perm) if (!check[j]){
                vector<pair<int, int>> ans = ask(u, v, j);
                for(pair<int, int> k: ans){
                    if (k == make_pair(u, v) || k == make_pair(v, u)) continue;
                    if (k.first != v) swap(k.first, k.second);
                    if (k.first == v){
                        pending.push_back(k.second);
                        break;
                    }
                }
                if ((int)pending.size() == po) break;
            }

            shuffle(ALL(pending), rng);
            dnc(ans, check, pending, i - po, i);
            i += po;
        }
        answer(ans);
    }
}

void solve(int n, int k){
    if (n <= 50) Sub1::solve(n);
    else if (n <= 100 && k == 3000){
        Sub2::solve(n, 9);
    }
    else if (n == 400 && k == 4500){
        Sub3::solve(n, 15);
    }
    else {
        Sub4::solve(n);
    }
}

int main(void){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);
 
    clock_t start = clock();

    cin >> t >> k;
    while(t--){
        int n; cin >> n;
        solve(n, k);
    }

    cerr << "Time elapsed: " << clock() - start << "ms!\n";
 
    return 0;
}