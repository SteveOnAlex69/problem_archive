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

const int N = 2002;
int n, cc;
int _grid[N][N];
int grid[N][N];
int pref[N];
int cc_sz[N];

void go(int depth, vector<int> &v){
    if (depth > cc){
        int cnt[3]; memset(cnt, 0, sizeof cnt);
        for(int i = 1; i <= cc; ++i) cnt[v[i]] += cc_sz[i];

        vector<int> perm = {0, 1, 2};
        sort(ALL(perm), [&cnt](int x, int y){return cnt[x] > cnt[y];});

        vector<int> pos;
        int l = 1;
        for(int i = 1; i <= cc; ++i) {
            if (v[i] == perm[0]) {
                for(int j = 0; j < cc_sz[i]; ++j) 
                    pos.push_back(l + j);
            }
            l += cc_sz[i];
        }

        printArr(pos);

        exit(0);
    }

    for(int x = 0; x < 3; ++x){
        if (v.back() == x) continue;

        v.push_back(x);
        int r = depth;

        int cnt[3]; memset(cnt, 0, sizeof cnt);
        int ma = 0;
        bool check = true;
        for(int l = r; l >= 1; --l){
            cnt[v[l]] += cc_sz[l];
            maximize(ma, cnt[v[l]]);
            if (ma != grid[l][r]) {
                check = false;
                break;
            }
        }

        int vcl = 0;
        for(int i = 0; i < 3; ++i) if (cnt[i] == grid[1][cc])
            vcl++;

        if (vcl >= 2) check = false;

        if (check){
            go(depth + 1, v);
        }

        v.pop_back();
    }
}

void solve(){
    cin >> n;
    for(int i = 1; i <= n; ++i) for(int j = i; j <= n; ++j) cin >> _grid[i][j];

    cc_sz[1] = 1;
    cc = 1;
    for(int i = 2; i <= n; ++i){
        if (_grid[i-1][i] == 1){
            cc_sz[++cc] = 1;
        }
        else{
            cc_sz[cc]++;
        }
    }

    int l = 1;
    for(int i = 1; i <= cc; ++i){
        int r = l - 1;
        for(int j = i; j <= cc; ++j){
            r += cc_sz[j];
            grid[i][j] = _grid[l][r];
        }
        l += cc_sz[i];
    }

    vector<int> v; v.push_back(-1);
    go(1, v);
}

int main(void){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);
 
    clock_t start = clock();

    solve();

    cerr << "Time elapsed: " << clock() - start << "ms!\n";
 
    return 0;
}