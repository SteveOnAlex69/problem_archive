#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
 
#define MASK(i) (1ULL << (i))
#define GETBIT(mask, i) (((mask) >> (i)) & 1)
#define ALL(v) (v).begin(), (v).end()

// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
mt19937_64 rng(10);
ll rngesus(ll l, ll r){return l + (ull) rng() % (r - l + 1);}

int alice(const int n, const char names[][5], const unsigned short numbers[], bool outputs_alice[]);
int bob(const int m,const char senders[][5],const char recipients[][5],bool outputs_bob[]);
int circuit(const int la, const int lb, int operations[],int operands[][2],int outputs_circuit[][16]);

int gate(int x, int y, int num){
	return GETBIT(num, x + y * 2);
}

namespace Data{
	const int ALICE_LIMIT = 1e5 + 69, BOB_LIMIT = 1e5 + 69, CIRCUIT_LIMIT = 4e7 + 69;
	bool outputs_alice[ALICE_LIMIT], outputs_bob[BOB_LIMIT];
	int operations[CIRCUIT_LIMIT], operands[CIRCUIT_LIMIT][2];
	bool tape[CIRCUIT_LIMIT];

	void print_segment(int l, int r){
		for(int i = l; i <= r; ++i) cout << tape[i];
		cout <<" \n";
	}

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

	string decode(ll x){
		int po = 26, n = 1;
		while(x >= po){
			x -= po;
			po *= 26;
			n++;
		}

		string ans(n, 'a');
		for(char &c: ans){
			po /= 26;
			c += x / po;
			x %= po;
		}
		return ans;
	}
}

bool solve(){
	using namespace Data;

	int n = 700, m = 1000;
	unsigned short numbers[n];
	for(int i = 0; i < n; ++i) numbers[i] = (unsigned short) rng();
	char names[n][5];

	set<string> S;
	vector<string> arr;
	for(int i = 0; i < n; ++i){
		string s;
		while(true){
			s = decode(rngesus(0, 475000));
			if (S.insert(s).second) break;
		}
		arr.push_back(s);
	}

	// sort(ALL(arr), [](string x, string y){return encode(x) < encode(y);});
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < (int) arr[i].size(); ++j) names[i][j] = arr[i][j];
		names[i][arr[i].size()] = '\0';
	}

	int lA = alice(n, names, numbers, outputs_alice);
	cout << "Alice used " << lA << " gates" << endl;

	char senders[m][5], recipients[m][5];
	unsigned short ans[n]; memset(ans, 0, sizeof ans);
	for(int i = 0; i < m; ++i){
		int u = rngesus(0, n-1), v = rngesus(0, n-1);
		ans[v] += numbers[u];
		for(int j = 0; j < (int) arr[u].size(); ++j){
			senders[i][j] = arr[u][j];
		}
		senders[i][arr[u].size()] = '\0';

		for(int j = 0; j < (int) arr[v].size(); ++j){
			recipients[i][j] = arr[v][j];
		}
		recipients[i][arr[v].size()] = '\0';
	}

	int lB = bob(m, senders, recipients, outputs_bob);
	cout << "Bob used " << lB << " gates" << endl;

	int outputs_circuit[n][16];
	memset(outputs_circuit, 0, sizeof outputs_circuit);
	int lC = circuit(lA, lB, operations, operands, outputs_circuit);

	cout << "Circuit used " << lC << " gates" << endl;

	for(int i = 0; i < lA; ++i) tape[i] = outputs_alice[i];
	for(int i = 0; i < lB; ++i) tape[i+lA] = outputs_bob[i];
	for(int i = lA + lB; i < lC; ++i){
		int x = operands[i][0], y = operands[i][1], op = operations[i];
		tape[i] = gate(tape[x], tape[y], op);
	}

	bool check = true;
	for(int i = 0; i < n; ++i){
		unsigned short cur = 0;
		for(int j = 0; j < 16; ++j) if (tape[outputs_circuit[i][j]]) {
			cur += MASK(j);
		}

		if (cur != ans[i]) {
			check = false;
		}
	}
	return check;
}

vector<int> debug_highway;
void push_highway(int x){
	debug_highway.push_back(x);
}


void print_arr_set(vector<array<int, 55>> &a){
    for(auto i: a) {
        for(int j = 0; j < 19; ++j) push_highway(i[j]);
        push_highway(-2);
        for(int j = 0; j < 19; ++j) push_highway(i[j + 19]);
        push_highway(-2);
        for(int j = 0; j < 16; ++j) push_highway(i[j + 38]);
        push_highway(-2);
        for(int j = 0; j < 1; ++j) push_highway(i[j + 54]);
        push_highway(-1);
    }
    push_highway(-1);
}

int main(void){
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);
 
    clock_t start = clock();

    if (solve()){
    	cout << "Accepted!\n";
    }
    else{
    	cout << "Wrong Answer!\n";
    }

    for(auto i: debug_highway){
    	if (i == -1) cout << "\n";
    	else if (i == -2) cout << " ";
    	else{
    		cout << Data::tape[i];
    	}
    }
 
    cerr << "Time elapsed: " << clock() - start << "ms!\n";
 
    return 0;
}