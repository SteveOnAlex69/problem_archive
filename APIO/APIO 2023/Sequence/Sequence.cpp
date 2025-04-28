#include <bits/stdc++.h>
#include "sequence.h"
 
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


struct Node{
    int sum, pref, suff;
    Node(int sum = 0, int pref = 0, int suff = 0) : sum(sum), pref(pref), suff(suff){}
};

struct SegmentTreeMax{
    int n;
    vector<Node> a;

    Node combine(Node a, Node b){
        return Node(a.sum + b.sum, max(a.pref, a.sum + b.pref), max(b.suff, b.sum + a.suff));
    }

    SegmentTreeMax(int _n){
        n = _n;
        a.resize(n * 2 + 2);
        for(int i = 1; i<=n; ++i) a[i+n] = Node(-1, 0, 0);
        for(int i = n; i >= 1; --i) a[i] = combine(a[i * 2], a[i * 2 + 1]);
    }

    void update(int i){
        i += n; a[i] = Node(1, 1, 1);
        while(i > 1){
            i >>= 1;
            a[i] = combine(a[i * 2], a[i * 2 + 1]);
        }
    }

    Node get(int l, int r){
        l += n; r += n + 1;
        Node L(0, 0, 0), R(0, 0, 0);
        while(l < r){
            if (l & 1) L = combine(L, a[l++]);
            if (r & 1) R = combine(a[--r], R);
            l >>= 1; r >>= 1;
        }
        return combine(L, R);
    }
};


struct SegmentTreeMin{
    int n;
    vector<Node> a;

    Node combine(Node a, Node b){
        return Node(a.sum + b.sum, min(a.pref, a.sum + b.pref), min(b.suff, b.sum + a.suff));
    }

    SegmentTreeMin(int _n){
        n = _n;
        a.resize(n * 2 + 2);
        for(int i = 1; i<=n; ++i) a[i+n] = Node(-1, -1, -1);
        for(int i = n; i >= 1; --i) a[i] = combine(a[i * 2], a[i * 2 + 1]);
    }

    void update(int i){
        i += n; a[i] = Node(1, 0, 0);
        while(i > 1){
            i >>= 1;
            a[i] = combine(a[i * 2], a[i * 2 + 1]);
        }
    }

    Node get(int l, int r){
        l += n; r += n + 1;
        Node L(0, 0, 0), R(0, 0, 0);
        while(l < r){
            if (l & 1) L = combine(L, a[l++]);
            if (r & 1) R = combine(a[--r], R);
            l >>= 1; r >>= 1;
        }
        return combine(L, R);
    }
};

const int N = 5e5 + 69;
vector<int> pos[N];

int sequence(int n, vector<int> a) {
    for(int i = 0; i<n; ++i) pos[a[i]].push_back(i+1);
    int ans = 0;
    SegmentTreeMax st_max(n);
    SegmentTreeMin st_min(n);
    for(int i = 1; i<=n; ++i) if (pos[i].size()){
        for(int j: pos[i]) st_max.update(j);
        int l = 0;
        for(int j = 0; j < pos[i].size(); ++j){
            while(l <= j){
                int cnt1 = st_min.get(pos[i][l], pos[i][j]).sum + st_min.get(1, pos[i][l]-1).suff + st_min.get(pos[i][j]+1, n).pref;
                int cnt2 = st_max.get(pos[i][l], pos[i][j]).sum + st_max.get(1, pos[i][l]-1).suff + st_max.get(pos[i][j]+1, n).pref;
                if (cnt1 < 1 && cnt2 >= 0) break;
                l++;
            }
            maximize(ans, j - l + 1);
        }
        for(int j: pos[i]) st_min.update(j);
    }
    return ans;
}


// int main(){
//     ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//     clock_t start = clock();
//     int n; cin >> n;
//     vector<int> a(n);
//     for(int i = 0; i<n; ++i) cin >> a[i];

//     cout << sequence(n, a) << "\n";

//     // SegmentTreeMin st_min(9);
//     // cout << st_min.get(1, 2).suff << "\n";

//     cerr << "Time elapsed: " << clock() - start << " ms\n";
//     return 0;
// }