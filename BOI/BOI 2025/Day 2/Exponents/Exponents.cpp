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

const ll INF = 1e18 + 69;

void solve(){
    int n, q; cin >> n >> q;
    vector<int> a(n+1);
    for(int i = 1; i <= n; ++i) cin >> a[i];

    vector<vector<pair<int,int>>> pp(n+1);
    for(int i = n; i >= 1; --i){
        pp[i].push_back(make_pair(a[i], i));
        while(true){
            int j = pp[i].back().second + 1;
            if (j > n) break;
            int val = pp[i].back().first;
            int idx = upper_bound(ALL(pp[j]), make_pair(val + 1, -1)) - pp[j].begin() - 1;
            if (idx != -1){
                pp[i].push_back(make_pair(val + 1, pp[j][idx].second));
            }
            else{
                idx++;
                val = max(val, pp[j][idx].first) + 1;
                pp[i].push_back(make_pair(val, pp[j][idx].second));
            }
        }
    }

    while(q--){
        int l, r; cin >> l >> r;
        int ans = a[l];
        for(int i = 1; i < (int) pp[l].size(); ++i){
            if (pp[l][i-1].second < r)
                maximize(ans, pp[l][i].first);
        }

        cout << ans << "\n";
    }
}

int main(void){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);
 
    clock_t start = clock();

    solve();

    cerr << "Time elapsed: " << clock() - start << "ms!\n";
 
    return 0;
}