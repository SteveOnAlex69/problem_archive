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


namespace OddEvenMergeSort{
    vector<pair<int, int>> oddeven_merge(int n){
        if (n == 1){
            vector<pair<int, int>> ans;
            return ans;
        }
        if (n == 2){
            vector<pair<int, int>> ans;
            ans.push_back(make_pair(0, 1));
            return ans;
        }
        vector<pair<int, int>> even = oddeven_merge(n / 2);
        vector<pair<int, int>> ans;
        for(auto i: even){
            ans.push_back(make_pair(i.first * 2, i.second * 2));
            ans.push_back(make_pair(i.first * 2 + 1, i.second * 2 + 1));
        }

        for(int i = 1; i < n; ++i) ans.push_back(make_pair(i-1, i));
        return ans;
    }

    vector<pair<int, int>> get_merging_network(int n) { // API call
        assert((n & (n - 1)) == 0);
        return oddeven_merge(n);;
    }

}

namespace Permutation{
    vector<pair<int, int>> sortperm_network(int n){
        if (n == 1){
            vector<pair<int, int>> ans;
            return ans;
        }
        vector<pair<int, int>> ans;
        for(int i = 0; i < n/2; ++i) ans.push_back(make_pair(i, i + n / 2));
        vector<pair<int, int>> half_time = sortperm_network(n / 2);
        for(auto i: half_time) {
            ans.push_back(i);
        }
        for(auto i: half_time){
            i.first += n / 2, i.second += n / 2;
            ans.push_back(i);
        }
        for(int i = 0; i < n/2; ++i) ans.push_back(make_pair(i, i + n / 2));
        return ans;
    }

    const int N = 1024;
    int val[N];
    bool visited[N];
    vector<pair<int,int>> graph[N];

    void dfs(int u){
        visited[u] = 1;
        for(pair<int, int> v: graph[u]) if (!visited[v.first]){
            val[v.first] = val[u] ^ v.second;
            dfs(v.first);
        }
    }

    vector<int> sortperm_verify(int n, vector<int> &perm){
        if (n == 1){
            vector<int> ans;
            return ans;
        }
        vector<int> ans;
        for(int i = 0; i < n / 2; ++i) {
            graph[i].clear();
            visited[i] = 0, val[i] = 0;
        }
        vector<vector<int>> pos(n/2);
        int lolo = logOf(n);
        for(int i = 0; i < n; ++i) pos[perm[i] % (n / 2)].push_back(i);
        for(int i = 0; i < n/2; ++i) {
            int u = pos[i][0], v = pos[i][1];
            int x = u % (n/2), y = v % (n / 2);
            if ((u < n / 2) == (v < n / 2)) {
                graph[x].push_back(make_pair(y, 1));
                graph[y].push_back(make_pair(x, 1));
            }
            else{
                graph[x].push_back(make_pair(y, 0));
                graph[y].push_back(make_pair(x, 0));
            }
        }

        for(int i = 0; i < n / 2; ++i) if (!visited[i]){
            dfs(i);
        }

        for(int i = 0; i < n / 2; ++i) {
            ans.push_back(val[i]);
            if (val[i]) swap(perm[i], perm[i+n/2]);
        }

        vector<int> left, right;
        for(int i= 0; i < n; ++i){
            if (i < n/2) left.push_back(perm[i]);
            else right.push_back(perm[i]);
        }

        vector<int> dnc_left = sortperm_verify(n/2, left), dnc_right = sortperm_verify(n/2, right);
        for(int i = 0; i < n/2; ++i){
            perm[i] = left[i];
            perm[i+n/2] = right[i];
        }

        for(int i: dnc_left) ans.push_back(i);
        for(int i: dnc_right) ans.push_back(i);

        for(int i = 0; i < n/2; ++i) {
            if (GETBIT(perm[i], lolo-1) > GETBIT(perm[i + n / 2], lolo-1)){
                ans.push_back(1);
                swap(perm[i], perm[i + n / 2]);
            }
            else ans.push_back(0);
        }

        return ans;
    }
}

#include "abc.h"

const int OP_ZERO    = 0;  // f(OP_ZERO,    x0, x1) = 0
const int OP_NOR     = 1;  // f(OP_NOR,     x0, x1) = !(x0 || x1)
const int OP_GREATER = 2;  // f(OP_GREATER, x0, x1) = (x0 > x1)
const int OP_NOT_X1  = 3;  // f(OP_NOT_X1,  x0, x1) = !x1
const int OP_LESS    = 4;  // f(OP_LESS,    x0, x1) = (x0 < x1)
const int OP_NOT_X0  = 5;  // f(OP_NOT_X0,  x0, x1) = !x0
const int OP_XOR     = 6;  // f(OP_XOR,     x0, x1) = (x0 ^ x1)
const int OP_NAND    = 7;  // f(OP_NAND,    x0, x1) = !(x0 && x1)
const int OP_AND     = 8;  // f(OP_AND,     x0, x1) = (x0 && x1)
const int OP_EQUAL   = 9;  // f(OP_EQUAL,   x0, x1) = (x0 == x1)
const int OP_X0      = 10; // f(OP_X0,      x0, x1) = x0
const int OP_GEQ     = 11; // f(OP_GEQ,     x0, x1) = (x0 >= x1)
const int OP_X1      = 12; // f(OP_X1,      x0, x1) = x1
const int OP_LEQ     = 13; // f(OP_LEQ,     x0, x1) = (x0 <= x1)
const int OP_OR      = 14; // f(OP_OR,      x0, x1) = (x0 || x1)
const int OP_ONE     = 15; // f(OP_ONE,     x0, x1) = 1

int encode(string s){
    int ans = 0;
    int po = 1;
    for(int i = 1; i < (int) s.size(); ++i){
        ans += po *= 26;
    }
    for(int i = 0; i < (int) s.size(); ++i){
        ans += po * (s[i] - 'a');
        po /= 26;
    }
    return ans;
}

int alice(const int n, const char names[][5], const unsigned short numbers[], bool outputs_alice[]) {
    vector<string> namek;
    for(int i = 0; i < n; ++i){
        namek.emplace_back();
        for(int j =0; j < 5; ++j){
            if (names[i][j] == '\0') break;
            namek.back().push_back(names[i][j]);
        }
    }

    vector<array<int, 4>> arr;
    for(int i = 0; i < n; ++i){
        int x = encode(namek[i]);
        arr.push_back({{x, x, numbers[i], 0}});
    }
    sort(ALL(arr));


    int idx = 0;
    for(auto i: arr){
        for(int j = 0; j < 19; ++j) outputs_alice[idx++] = GETBIT(i[0], j);
        for(int j = 0; j < 19; ++j) outputs_alice[idx++] = GETBIT(i[1], j);
        for(int j = 0; j < 16; ++j) outputs_alice[idx++] = GETBIT(i[2], j);
        outputs_alice[idx++] = 0;
    }

    vector<int> sigma(n);
    for(int i = 0; i < n; ++i) sigma[i]= encode(namek[i]);
    sort(ALL(sigma));

    vector<int> perm(n);
    for(int it = 0; it < n; ++it){
        int j = encode(namek[it]);
        int idx = lower_bound(ALL(sigma), j) - sigma.begin();
        perm[idx] = it;
    }
    while(LASTBIT(perm.size()) != perm.size()) 
        perm.push_back(perm.size());

    vector<int> seq = Permutation::sortperm_verify(perm.size(), perm);
    for(int i: seq){
        outputs_alice[idx++] = i;
    }
    return idx;
}


int bob(const int m,const char senders[][5],const char recipients[][5],bool outputs_bob[]) {
    if (m == 0) return 0;
    vector<string> senders_name;
    for(int i = 0; i < m; ++i){
        senders_name.emplace_back();
        for(int j =0; j < 5; ++j){
            if (senders[i][j] == '\0') break;
            senders_name.back().push_back(senders[i][j]);
        }
    }
    vector<string> recipients_name;
    for(int i = 0; i < m; ++i){
        recipients_name.emplace_back();
        for(int j =0; j < 5; ++j){
            if (recipients[i][j] == '\0') break;
            recipients_name.back().push_back(recipients[i][j]);
        }
    }

    vector<array<int, 4>> arr;
    for(int i = 0; i < m; ++i){
        int x = encode(senders_name[i]);
        int y = encode(recipients_name[i]);
        arr.push_back({{x, y, 0, 1}});
    }
    sort(ALL(arr));

    int idx = 0;
    for(auto i: arr){
        for(int j = 0; j < 19; ++j) outputs_bob[idx++] = GETBIT(i[0], j);
        for(int j = 0; j < 19; ++j) outputs_bob[idx++] = GETBIT(i[1], j);
        for(int j = 0; j < 16; ++j) outputs_bob[idx++] = GETBIT(i[2], j);
        outputs_bob[idx++] = 1;
    }


    vector<array<int, 3>> by_second(m);
    for(int i = 0; i < m; ++i) by_second[i] = {{encode(senders_name[i]), encode(recipients_name[i]), 0}};

    sort(ALL(by_second), [](array<int, 3> x, array<int, 3> y){return x[1] < y[1];});
    for(int i = 0; i < m; ++i) by_second[i][2] = i;
    sort(ALL(by_second));

    vector<int> perm(m);
    for(int it = 0; it < m; ++it){
        perm[it] = by_second[it][2];
    }
    while(LASTBIT(perm.size()) != perm.size()) 
        perm.push_back(perm.size());

    vector<int> seq = Permutation::sortperm_verify(perm.size(), perm);
    for(int i: seq){
        outputs_bob[idx++] = i;
    }

    return idx;
}

struct LogicGate{
    int x, y, type;
    LogicGate(int x = -1, int y = -1, int type = -1): x(x), y(y), type(type){}
};
int CACHE_ZERO, CACHE_ONE;
vector<LogicGate> gay;

int create_new_gate(int x, int y, int OP){
    gay.emplace_back(LogicGate(x, y, OP));
    return gay.size() - 1;
}

vector<int> op_add(vector<int> x, vector<int> y){  // op_add(x[], y[]) = x[] + y[]
    if (x.size() != y.size()) assert(false);
    int carry = create_new_gate(x[0], y[0], OP_AND);
    x[0] = create_new_gate(x[0], y[0], OP_XOR);
    for(int i = 1; i < (int) x.size(); ++i){
        int zur = create_new_gate(x[i], y[i], OP_XOR);
        int zem = create_new_gate(zur, carry, OP_XOR);
        if (i + 1 < (int) x.size()){
            int and1 = create_new_gate(x[i], y[i], OP_AND);
            int and2 = create_new_gate(zur, carry, OP_AND);
            carry = create_new_gate(and1, and2, OP_OR);
        }
        x[i] = zem;
    }
    return x;
}

vector<int> op_xor(vector<int> x, vector<int> y){  // op_add(x[], y[]) = x[] ^ y[]
    if (x.size() != y.size()) assert(false);
    for(int i = 0; i < (int) x.size(); ++i){
        x[i] = create_new_gate(x[i], y[i], OP_XOR);
    }
    return x;
}

int is_greater(vector<int> x, vector<int> y){
    if (x.size() != y.size()) assert(false);
    int ma_diff = CACHE_ZERO;
    vector<int> z(x.size());
    for(int i = 0; i < (int) x.size(); ++i){
        int tmp = create_new_gate(x[i], y[i], OP_XOR);
        if (ma_diff == CACHE_ZERO) {
            z[i] = tmp;
            ma_diff = tmp;
        }
        else{
            z[i] = create_new_gate(tmp, ma_diff, OP_GREATER);
            ma_diff = create_new_gate(tmp, ma_diff, OP_OR);
        }
    }

    int ans = CACHE_ZERO;
    for(int i = 0; i < (int) x.size(); ++i){
        int tmp = create_new_gate(x[i], y[i], OP_GREATER);
        tmp = create_new_gate(tmp, z[i], OP_AND);
        ans = create_new_gate(tmp, ans, OP_OR);
    }
    return ans;
}

void swap_number(array<int, 55> &a, array<int, 55> &b, int x, array<int, 55> swap_mask){
    for(int i = 0; i < 55; ++i) if (swap_mask[i]) {
        int c;
        c = create_new_gate(a[i], b[i], OP_XOR);
        c = create_new_gate(c, x, OP_AND);
        a[i] = create_new_gate(a[i], c, OP_XOR);
        b[i] = create_new_gate(b[i], c, OP_XOR);
    }
}

int swapIf(array<int, 55> &a, array<int, 55> &b, vector<int> sorting_function, array<int, 55> swap_mask){
    vector<int> compared_bit1, compared_bit2;
    for(int k: sorting_function){
        compared_bit1.push_back(a[k]);
        compared_bit2.push_back(b[k]);
    }

    int x = is_greater(compared_bit1, compared_bit2);
    swap_number(a, b, x, swap_mask);
    return x;
}

vector<int> make_merging_network(vector<array<int, 55>> &a, vector<int> sorting_function, array<int, 55> swap_mask){
    int n = a.size();
    vector<int> history;
    vector<pair<int, int>> network = OddEvenMergeSort::get_merging_network(n);
    for(auto it: network){
        int i, j;
        tie(i, j) = it;
        int cur = swapIf(a[i], a[j], sorting_function, swap_mask);
        history.push_back(cur);
    }
    return history;
}
void reverse_merging_network(vector<array<int, 55>> &a, vector<int> proxy_vertex, array<int, 55> swap_mask){
    int n = a.size();
    vector<pair<int, int>> network = OddEvenMergeSort::get_merging_network(n);
    reverse(ALL(network)); reverse(ALL(proxy_vertex));
    if (network.size() != proxy_vertex.size()) assert(false);
    for(int it = 0; it < (int)network.size(); ++it){
        int i, j;
        tie(i, j) = network[it];
        swap_number(a[i], a[j], proxy_vertex[it], swap_mask);
    }
}


int get_n(int x){
    if (x == 0) return 0;
    int po = 1;
    for(int i = 1; i <= 1000; ++i){
        while(po < i) po *= 2;
        if (x == i * 55 + po * logOf(po)) return i;
    }
    return -1;
}

int circuit(const int la, const int lb, int operations[],int operands[][2],int outputs_circuit[][16]) {
    gay.clear();
    int n = get_n(la), m = get_n(lb);
    gay.reserve(2e7);
    for(int i = 0; i < la + lb; ++i) gay.emplace_back();

    CACHE_ZERO = create_new_gate(0, 0, OP_ZERO);
    CACHE_ONE = create_new_gate(0, 0, OP_ONE);
    array<int, 55> NULL_ITEM_ZERO;
    fill(ALL(NULL_ITEM_ZERO), CACHE_ZERO);
    for(int j = 0; j < 38; ++j)
        NULL_ITEM_ZERO[j] = CACHE_ONE;

    int gay_shit = 1;
    while(gay_shit < max(n, m)) gay_shit *= 2;

    vector<array<int, 55>> sigma;
    for(int i = 0; i < n; ++i){
        sigma.emplace_back();
        for(int j = 0; j < 55; ++j) 
            sigma.back()[j] = i * 55 + j;
    }
    for(int i= n; i < gay_shit; ++i) sigma.push_back(NULL_ITEM_ZERO);
    for(int i = 0; i < m; ++i){
        sigma.emplace_back();
        for(int j = 0; j < 55; ++j) 
            sigma.back()[j] = la + i * 55 + j;
    }
    for(int i= m; i < gay_shit; ++i) sigma.push_back(NULL_ITEM_ZERO);


    // // sort by (a, d)
    vector<int> sorting_function;
    for(int i = 18; i >= 0; --i) sorting_function.push_back(i);
    sorting_function.push_back(54);

    array<int, 55> swap_mask; fill(ALL(swap_mask), 1);
    vector<int> proxy_vertex = make_merging_network(sigma, sorting_function, swap_mask);
    vector<int> sum(16, CACHE_ZERO);
    for(auto &i: sigma){
        for(int &j: sum){
            j = create_new_gate(j, i[54], OP_AND);
        }

        for(int j = 0; j < 16; ++j){
            sum[j] = create_new_gate(sum[j], i[j + 38], OP_XOR);
            i[j + 38] = create_new_gate(sum[j], i[j + 38], OP_XOR);
        }
    }
    for(int i = 0; i < 19; ++i) swap_mask[i] = 0;
    reverse_merging_network(sigma, proxy_vertex, swap_mask);

    vector<int> seq;
    for(int i = m * 55; i < lb; ++i) seq.push_back(la + i);

    int go_pro = 1;
    while(go_pro < m) go_pro *= 2;

    vector<pair<int, int>> network = Permutation::sortperm_network(go_pro);
    for(int it = 0; it < (int) seq.size(); ++it){
        int i, j; tie(i, j) = network[it];
        swap_number(sigma[i + gay_shit], sigma[j + gay_shit], seq[it], swap_mask);
    }
    

    sorting_function.clear();
    for(int i = 37; i >= 19; --i) sorting_function.push_back(i);
    sorting_function.push_back(54);

    proxy_vertex = make_merging_network(sigma, sorting_function, swap_mask);
    reverse(ALL(sigma));

    sum = vector<int>(16, CACHE_ZERO);
    for(auto &i: sigma){
        vector<int> cur;
        for(int j = 38; j < 54; ++j) {
            cur.push_back(i[j]);
            i[j] = sum[j - 38];
        }

        sum = op_add(sum, cur);
        for(int &j: sum) j = create_new_gate(j, i[54], OP_AND);
    }
    reverse(ALL(sigma));
    swap_mask[54] = 0;
    for(int i= 19; i < 38; ++i) swap_mask[i] = 0;
    reverse_merging_network(sigma, proxy_vertex, swap_mask);

    seq.clear();
    for(int i = n * 55; i < la; ++i) seq.push_back(i);
    go_pro = 1;
    while(go_pro < n) go_pro *= 2;
    network = Permutation::sortperm_network(go_pro);
    for(int it = 0; it < (int) seq.size(); ++it){
        int i, j; tie(i, j) = network[it];
        swap_number(sigma[i], sigma[j], seq[it], swap_mask);
    }

    for(int i = la + lb; i < (int)gay.size(); ++i){
        operations[i] = gay[i].type;
        operands[i][0] = gay[i].x;
        operands[i][1] = gay[i].y;
    }

    for(int i = 0; i < n; ++i) for(int j = 0; j < 16; ++j){
        outputs_circuit[i][j] = sigma[i][j + 38];
    }
    return gay.size();
}

 