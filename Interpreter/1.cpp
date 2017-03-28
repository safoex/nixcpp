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
bool skip_next_operator = false;
stack<int> while_lvl;
stack<int> while_g;
map<pair<string,string>, pair<string, string> > automate;
#define p make_pair


int program(istream& fin, bool first = false) {
do {
	int g = fin.tellg();
	fin >> com;
	if(coms1.count(com)) {
		fin >> num1;
		//cout << num1;
	}
	if(coms2.count(com)) {
		fin >> num1 >> num2;
		//cout << num1 << num2;
	}
	
	if(com == "begin") {
		op_level ++;
	}
	if(com == "end") {
		op_level --;
		if(!first && !while_lvl.empty() && op_level == while_lvl.top()) {
			while_lvl.pop();
			fin.seekg(while_g.top(), fin.beg);
			while_g.pop();
		}
	}

	if(first) continue;

	if(com == "inc" ) {
		if(skip_next_operator)	vars[num1]++;
		else if(skip_next_operator == op_level) skip_next_operator = 0;
	}
	if(com == "dec" ) {
		if(skip_next_operator) vars[num1]--;
		else if(skip_next_operator == op_level) skip_next_operator = 0;

	}
	if(com == "if" && skip_next_operator) {
		if(vars[num1] == 0) skip_next_operator = op_level;
	}
	if(com == "while" && skip_next_operator) {
		if(vars[num1] == 0) {
			while_lvl.push(op_level);
			while_g.push(g);
		}
		else skip_next_operator = op_level;
	}
	
	if(com == "move")  {
		if(skip_next_operator)	vars[num1] = vars[num2]; 
		else if(skip_next_operator == op_level) skip_next_operator = 0;
	}
	
	if(com == "set") {
		if(skip_next_operator) {
			stringstream snum2(num2);
			int inum2;
			snum2 >> inum2;
			vars[num1] = inum2;
	//		fout << com << ' ' << num1 << ' ' << num2 << ' ' <<vars[num1] << endl;
		}
		else if(skip_next_operator == op_level) skip_next_operator = 0;
	}


}while(op_level > 1);

return fin.tellg();
}

int main() {

//automate.insert(p(p("
ifstream fin("input.txt");
ofstream fout("output.txt");
set<string> coms1{"if","while","inc","dec","print"};
set<string> coms2{"move","set"};

for(auto s: coms2) cout << s << endl;

int a = program(fin, true);


string com;
string num1;
string num2;

}
