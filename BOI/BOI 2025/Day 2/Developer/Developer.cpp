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


struct FenwickTree{
    int n;
    vector<ll> a;

    FenwickTree(int _n = 0){
        n = _n;
        a.resize(n+1);
    }

    void update(int i, ll v){
        while(i <= n){
            a[i] += v;
            i += LASTBIT(i);
        }
    }

    ll get(int i){
        ll ans = 0;
        while(i > 0){
            ans += a[i];
            i -= LASTBIT(i);
        }
        return ans;
    }

    ll get(int l, int r){return get(r) - get(l-1);}

    int binary_lift(ll x){
        int p = MASK(logOf(n)), idx =0;
        while(p > 0){
            if (idx + p <= n && x > a[idx + p]){
                idx += p;
                x -= a[idx];
            }
            p >>= 1;
        }
        return idx + 1;
    }
};

struct SumSet{
    int n;
    vector<int> val;
    FenwickTree bit, sum;

    SumSet(int _n, vector<int> _val){
        n = _n; 
        val = _val;
        bit = FenwickTree(n);
        sum = FenwickTree(n);
    }

    void add_number(int x){
        int idx = lower_bound(ALL(val), x) - val.begin();
        bit.update(idx, 1);
        sum.update(idx, x);
    }

    ll get_taxicab(){
        int total = bit.get(n);
        int med = bit.binary_lift((total + 1) / 2);

        int left = bit.get(med);
        ll ans = 1LL * val[med] * left - sum.get(med) + sum.get(med + 1, n) - 1LL * val[med] * (total - left);
        return ans;
    }
};

namespace Sub1{
    void solve(int n, vector<int> a){
        a.erase(a.begin());

        vector<int> b = a; 
        b.push_back(-2); b.push_back(1e9 + 69);
        for(int i: a){
            b.push_back(i-1); b.push_back(i); b.push_back(i+1);
        }
        remove_dup(b);

        int m = b.size();
        ll dp[2][m][2];
        for(int x = 0; x <= 1; ++x) for(int y = 0; y < m; ++y) for(int z = 0; z <= 1; ++z){
            dp[x][y][z] = INF;
        }
        dp[0][0][0] = 0;
        dp[0][m-1][1] = 0;

        for(int i: a){
            ll pref[m], suff[m];
            fill(pref, pref + m, INF);
            fill(suff, suff + m, INF);
            for(int j = 0; j < m; ++j){
                minimize(dp[1][j][0], dp[0][j][0] + abs(b[j] - i));
                minimize(dp[1][j][1], dp[0][j][1] + abs(b[j] - i));
                if (j + 1 < m){
                    pref[j+1] = dp[0][j][0];
                }
                if (j > 0){
                    suff[j-1] = dp[0][j][1];
                }
            }
            for(int j = 1; j < m; ++j) minimize(pref[j], pref[j-1]);
            for(int j = m - 2; j >= 0; --j) minimize(suff[j], suff[j+1]);

            for(int j = 0; j < m; ++j){
                minimize(dp[1][j][1], pref[j] + abs(b[j] - i));
                minimize(dp[1][j][0], suff[j] + abs(b[j] - i));
            }

            for(int j = 0; j < m; ++j){
                for(int z = 0; z <= 1; ++z){
                    dp[0][j][z] = dp[1][j][z];
                    dp[1][j][z] = INF;
                }
            }
        }

        ll ans = INF;
        for(int j = 0; j < m; ++j) for(int z = 0; z <= 1; ++z)
            minimize(ans, dp[0][j][z]);

        cout << ans << "\n";
    }
}

namespace Sub2{
    void solve(int n, vector<int> a){
        vector<ll> dp(n+1, INF);
        dp[0] = 0;
        SumSet sus(n, a);
        for(int i = 1; i <= n; ++i){
            sus.add_number(a[i]);
            dp[i] = sus.get_taxicab();
        }
        for(int i = 0; i < n; ++i){
            for(int j = i+2; j <= min(i + 3, n); ++j){
                ll cost = INF;
                for(int k = i+1; k <= j; ++k){
                    ll cur = 0;
                    for(int t = i + 1; t <= j; ++t) {
                        cur += abs(a[t] - a[k]);
                    }
                    minimize(cost, cur);
                }
                minimize(dp[j], dp[i] + cost + 1);
            }
        }

        sus = SumSet(n, a);
        for(int i = n; i >= 1; --i){
            sus.add_number(a[i]);

            minimize(dp[n], dp[i-1] + sus.get_taxicab());
        }
        cout << dp[n] << "\n";
    }
}

void solve(){
    int n; cin >> n;
    vector<int> a(n+1, -100);
    for(int i = 1; i <= n; ++i) cin >> a[i];

    if (n <= 2000) Sub1::solve(n, a);
    else Sub2::solve(n, a);
}

int main(void){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);
 
    clock_t start = clock();

    // int t; cin >> t;
    // while(t--)
    solve();

    cerr << "Time elapsed: " << clock() - start << "ms!\n";
 
    return 0;
}