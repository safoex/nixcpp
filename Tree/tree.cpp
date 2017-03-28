#include <iostream>
#include <string>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
bool isNumber(char c) {
	return c == '-' || ( c <= '9' && c >= '0'); 
}
bool isBracket(char c) {
	return c == ')' || c =='(';
}
bool isWhiteSpace(char c) {
	return c == ' ' || c == '\t' ;
}

class FiniteAutomat {
	map<pair<string,string>, pair<string,string> > table;
public:
	FiniteAutomat() {}
	
	FiniteAutomat& operator+=(const pair<pair<string, string>,pair<string, string> >& action) {
		table.insert(action);
		return *this;
	}

	pair<string,string>& operator[](const pair<string,string>& go) { 
		return table[go];
	}
	
	/*const string operator[] (const pair<string,string>& go) const {
		return table[go];
	}*/
};
#define p make_pair
int main() {
	stack<char> s;
	string number("");
	char c;
	FiniteAutomat a;
	a += p(p("number","whitespace"),p("ready", "count_number"));
	a += p(p("number",")"),p("ready","count_number_push_bracket"));
	a += p(p("ready","("),p("ready","push_bracket"));
	a += p(p("ready","whitespace"), p("ready","nothing"));
	a += p(p("ready",")"),p("ready","push_bracket"));
	a += p(p("number","number"),p("number","push_number"));
	a += p(p("number","("),p("ready", "count_number_push_bracket"));
	a += p(p("ready", "number"),p("number","push_number"));
	string state = "ready";
	string action = "";
	double average = 0;
	while( cin >> noskipws>> c) {
		if(isBracket(c)) {
			string act("1");
			act[0] = c;
			auto d = a[p(state,act)];
			state = d.first;
			action = d.second;
		}
		else if(isNumber(c)) {
			auto d = a[p(state,"number")];
			state = d.first;
			action = d.second;
		}
		else if(isWhiteSpace(c)) {
			auto d = a[p(state,"whitespace")];
			state = d.first;
			action = d.second;
		}
		else break;
		if(action == "count_number" || action == "count_number_push_bracket") {
			int a = stoi(number);
			//cout << a << endl;
			average += ((double)a)/pow(2,s.size());
			number = "";
		}
		if(action == "push_bracket" || action == "count_number_push_bracket") {
			if(c == ')') {
				s.pop();
			}
			if(c == '(') {
				s.push('(');
			}
		}
		if(action == "push_number") {
			number += c;
		}	
		if(action == "nothing") {
			//
		}
	}

	cout << average;
	return 0;
	
}
