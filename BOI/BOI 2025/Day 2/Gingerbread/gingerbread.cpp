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

const int N = 1e7 + 69;
bool e[N];
int next_prime[N];

void prepare(){
    e[2] = 1;
    for(int i = 3; i < N; i += 2) e[i] = 1;
    for(int i = 3; i * i < N; i += 2) if (e[i])
    for(int j = i * i; j < N; j += i + i) e[j] = 0;

    for(int j = N-2; j >= 0; --j) {
        if (e[j]) next_prime[j] = j;
        else next_prime[j] = next_prime[j+1];
    }
}

const int INF = 1e9 + 69;
int dp[2][N];

void solve(){
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) cin >> a[i];

    memset(dp, 63, sizeof dp);
    dp[0][0] = 0;
    vector<int> cur, tmp;
    cur.reserve(1000); tmp.reserve(1000);
    cur.push_back(0);
    for(int i: a){
        for(int j: cur){
            for(int k = i; k <= next_prime[i] + 1; ++k){
                int t = gcd(j, k);
                if (dp[1][t] >= INF){
                    tmp.push_back(t);
                }
                minimize(dp[1][t], dp[0][j] + (k - i));
                if (t == 1) break;
            }
        }
        for(int j: cur) dp[0][j] = INF;
        for(int j: tmp){
            dp[0][j] = dp[1][j];
            dp[1][j] = INF;
        }
        cur = tmp; tmp.clear();
    }
    cout << dp[0][1] << "\n";
}

int main(void){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);
 
    clock_t start = clock();

    prepare();
    solve();

    cerr << "Time elapsed: " << clock() - start << "ms!\n";
 
    return 0;
}