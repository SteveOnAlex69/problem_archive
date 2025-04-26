// FOR DEBUGGING PURPOSES

#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define MASK(i) (1ULL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()
 

void solve(int n, int k);
int n;
vector<int> perm, pos, ans;
int op_cnt = 0;


vector<pair<int,int>> ask(int i, int j, int k){
    op_cnt++;
    if (i == j || j == k || k == i) assert(false);
    int ans = 1e9;
    for(int it = 0; it < 3; ++it){
        int cost = abs(pos[i] - pos[j]);
        cost = min(cost, n - cost);
        minimize(ans, cost);
        swap(i, j);
        swap(j, k);
    }
    vector<pair<int,int>> arr;
    for(int it = 0; it < 3; ++it){
        int cost = abs(pos[i] - pos[j]);
        cost = min(cost, n - cost);
        if (ans == cost)
            arr.push_back(make_pair(i, j));
        swap(i, j);
        swap(j, k);
    }
    return arr;
}

void answer(vector<int> v){
    ans = v;
}

vector<int> rotate_to_anchor(vector<int> perm){
    int idx = min_element(ALL(perm)) - perm.begin();
    reverse(perm.begin(), perm.begin() + idx);
    reverse(idx + ALL(perm));
    reverse(ALL(perm));
    if (perm[1] > perm.back()) reverse(1 + ALL(perm));
    return perm;
}

bool equavilent(vector<int> perm1, vector<int> perm2){
    perm1 = rotate_to_anchor(perm1), perm2 = rotate_to_anchor(perm2);
    return perm1 == perm2;
}

double get_point(int op_cnt){
    double wow = 12000 - op_cnt;
    return 44 + min((double)1, wow / 7800) * 56;
}

int main(void){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);
 
    clock_t start = clock();

    mt19937_64 gurt(1);

    int max_op = 0;
    for(int it = 0; it < 1000; ++it){
        n = rngesus(400, 500);
        int k = 12000; 
        perm.resize(n); pos.resize(n); ans.clear();
        for(int i = 0; i < n; ++i) perm[i] = i;

        shuffle(ALL(perm), gurt);
        for(int i = 0; i < n; ++i) pos[perm[i]] = i;

        solve(n, k);

        cout << "Operation used: " << op_cnt << "\n";
        maximize(max_op, op_cnt);
        if (equavilent(perm, ans) && op_cnt <= k) cout << "Accepted\n";
        else {
            cout << "Wrong answer!\n";
            break;
        }
        op_cnt = 0;

    }
    cout << "Maximum number of operation used: " << max_op << "\n";
    cout << "Point attained: " << get_point(max_op) << "\n";
    

    cerr << "Time elapsed: " << clock() - start << "ms!\n";
 
    return 0;
}