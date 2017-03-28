#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;


map<int, vector<int>> es;
vector<int> color;
vector<int> times_out;
bool hasCycle = false;
vector<int> ans;
int dfs(int sv, int time_in) {
	
	color[sv] = 1;
	int time_out = time_in + 1;
	for (int i = 0; i < es[sv].size() ; i++)  {
		if( color[es[sv][i]] == 0 ) {
			time_out = dfs(es[sv][i], time_out );
		}
		else if(color[es[sv][i]] == 1) {
			hasCycle = true;
		}
	}
	color[sv] = 2;
	ans.push_back(sv);
	times_out[sv] = time_out;
	return time_out;
}

#define I cin
#define O cout
int main() {
	
	//ifstream I("input.txt");
	//ofstream O("output.txt");
	
	int N, M;
	
	I >> N >> M;

	for(int i = 0; i < M; i++) {
		int A, B;
		I >> A >> B;
		es[A].push_back(B);
	}
	int extra;
	I >> extra >> extra;
	color = vector<int>(N+1,0);
	times_out = vector<int>(N+1,0);
		
	long int last_time = 0;
	for(int i = 1; i <= N; i++) {
		if(! color[i]) {
			last_time = dfs(i, last_time) + 1;
		}
	}	
	
	//if(hasCycle) O << "No" << endl;
	//else O << "Yes" << endl;
	
	vector<pair<int,int> > times_order(N,make_pair(0,0));
		
	for(int i = 1; i <= N; i++) {
		times_order[i-1] = make_pair(times_out[i], i);
	}
	sort(times_order.begin(),times_order.end());
	
	/*for(auto p:times_order) {
		O << p.second << ' ';// << p.first << endl;
	}
	O << endl;*/
	for(auto it = ans.rbegin(); it != ans.rend(); it++) {
		O << *it << ' ';
	}	
	O << endl;
return 0;
}
