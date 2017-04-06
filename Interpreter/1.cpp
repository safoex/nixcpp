#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>
#include <stack>
#include <set>

using namespace std;
map<string, int> vars;
int op_level = 1;
int skip_next_operator = 0;
stack<int> while_lvl;
stack<int> while_g;
map<pair<string,string>, pair<string, string> > automate;
#define p make_pair
set<string> coms1{"if","while","inc","dec","print"};
set<string> coms2{"move","set"};

//ofstream olog("log.txt");


streampos program(istream& fin,ostream& fout, bool first = false) {

string com;
string num1;
string num2;
bool whilejump = false;
do {
	streampos g = fin.tellg();
	fin >> com;
	whilejump = false;
	//olog <<"com: "<< com << " pos " << g << endl;;
	if(coms1.count(com)) {
		fin >> num1;
		//olog << num1;
	}
	if(coms2.count(com)) {
		fin >> num1 >> num2;
		//olog << num1 << ' ' << num2;
	}
	//olog << endl;
	//olog << com << endl;
	//olog << com << endl;
	//olog << while_lvl.size() << endl;
	if(com == "begin") {
		op_level ++;
	}
	if(com == "end") {
		op_level --;
		//olog <<"while ~: " <<  while_lvl.empty()  << ' ' << op_level << ' ' << (while_lvl.empty() ? -1 :while_g.top()) << endl;
		if( !while_lvl.empty() &&  op_level == while_lvl.top()) {
			while_lvl.pop();
			if(!first) {fin.seekg(while_g.top());whilejump = true;}
			while_g.pop();
		}
		if(skip_next_operator == op_level) skip_next_operator = 0;
		
	}
	
	if(com == "while") {
		if(!skip_next_operator) {
			//olog << "in while " << num1 << " = " << vars[num1] << endl;
			if(vars[num1] != 0) {
				while_lvl.push(op_level);
				while_g.push(g);
				//olog << g << endl;
			}
			else skip_next_operator = op_level;
		}
		//else if(skip_next_operator == op_level) skip_next_operator = 0;
	}
	//olog << op_level << ' ' << while_lvl.size() << endl;
	if(first && (op_level > 1 || !while_lvl.empty() || skip_next_operator)) continue;
	else if(first) break;
	if(com == "inc" ) {
		if(!skip_next_operator)	vars[num1]++;
		else if(skip_next_operator == op_level) skip_next_operator = 0;
	}
	if(com == "dec" ) {
		//cout << num1 << ' ' << skip_next_operator << endl;
		if(!skip_next_operator) vars[num1]--;
		else if(skip_next_operator == op_level) skip_next_operator = 0;

	}
	if(com == "if") {
		if(!skip_next_operator) if(vars[num1] == 0) skip_next_operator = op_level;
		//else if(skip_next_operator == op_level) skip_next_operator = 0;
	}
	
	
	if(com == "move")  {
		if(!skip_next_operator)	vars[num1] = vars[num2]; 
		else if(skip_next_operator == op_level) skip_next_operator = 0;
	}
	
	if(com == "set") {
		if(!skip_next_operator) {
			stringstream snum2(num2);
			int inum2;
			snum2 >> inum2;
			vars[num1] = inum2;
	//		fout << com << ' ' << num1 << ' ' << num2 << ' ' <<vars[num1] << endl;
		}
		else if(skip_next_operator == op_level) skip_next_operator = 0;
	}
	if(com == "print") {
		if(!skip_next_operator) {
			fout << vars[num1] << endl;
		}
		else if(skip_next_operator == op_level) skip_next_operator = 0;
	}

	//olog << op_level << ' ' << while_lvl.size() << endl;
} while(whilejump || op_level > 1 || !while_lvl.empty() || skip_next_operator);

return fin.tellg();
}


#define fin cin
#define fout cout
int main() {

//automate.insert(p(p("
//ifstream fin("input.txt");
//ofstream fout("output.txt");
//for(auto s: coms2) cout << s << endl;

int a = program(fin, fout, true);


//cout << "!!!!!!" << endl;
int N;
fin >> N;
auto g = fin.tellg();
//cout << N << endl;
for( int i = 0; i < N;i++) {
	fin.seekg(g, fin.beg);
	vars.clear();
	int M;
	fin >> M;
	//cout << "!!!" << endl;
	//cout << 2*M << endl;
	for(int i =0; i < M; i++) {
		string var; int val;
		fin >> var >> val;
		vars[var] = val;
	}
	g = fin.tellg();	
	//fin.seekg(0,fin.beg);
	//string buf;
	//fin >> buf ;
	//cout << buf << ' ' << "!!!" << endl;
	fin.seekg(0, fin.beg);
	program(fin,fout);	
}

}
