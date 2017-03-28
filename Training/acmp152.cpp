#include <map>
#include <vector>
#include <fstream>


using namespace std;


map<int, vector<int>> es;
vector<int> color;
vector<int> times_out;
bool hasCycle = false;

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
	times_out[sv] = time_out;
	return time_out;
}

int main() {
	
	ifstream I("input.txt");
	ofstream O("output.txt");
	
	int N, M;
	
	I >> N >> M;

	for(int i = 0; i < M; i++) {
		int A, B;
		I >> A >> B;
		es[A].push_back(B);
	}
	
	color = vector<int>(N+1,0);
	times_out = vector<int>(N+1,0);
		
	
	for(int i = 1; i <= N; i++) {
		if(! color[i]) dfs(i, 0);
	}	
	
	if(hasCycle) O << "No" << endl;
	else O << "Yes" << endl;
return 0;
}
