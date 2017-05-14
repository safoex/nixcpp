#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <cctype>
#include <cmath>
#include <vector>
#include <functional>
using namespace std;


bool isunary(char c) {
	return c == '-';
}

bool delim (char c) {
	return c == ' ';
}
 
bool is_op (char c) {
	return c=='-' || c=='|' || c=='^' || c=='v';
}
/* 
int priority (char op) {
	if (op < 0)
		return 4; // op == -'+' || op == -'-'
	return
		op == '+' || op == '-' ? 1 :
		op == '*' || op == '/' ? 2 :
		op == '^' ? 3 :
		-1;
}
*/
int priority (char op) {
	if (op == '-' || op == -'-') return 4;
	if (op == '|') return 3;
	if (op == 'v') return 2;
	if (op == '^') return 1;
	return -1;
}
 
void process_op (vector<bool> & st, char op) {
	if (op < 0) {
		bool l = st.back();  st.pop_back();
		switch (-op) {
			case '+':  st.push_back (l);  break;
			case '-':  st.push_back (!l);  break;
		}
	}
	else {
		bool r = st.back();  st.pop_back();
		bool l = st.back();  st.pop_back();
		switch (op) {
			case '^':  st.push_back (l && r);  break;
			case '|':  st.push_back (!(l && r));  break;
			case 'v':  st.push_back (l || r);  break;
			//case '/':  st.push_back (l / r);  break;
			//case '%':  st.push_back (l % r);  break;
			//case '^':  st.push_back (pow(l, r));  break;
		}
	}
}
 
float calc (string & s) {
	bool may_unary = true;
	vector<bool> st;
	vector<char> op;
	for (size_t i=0; i<s.length(); ++i)
		if (!delim (s[i]))
			if (s[i] == '(') {
				op.push_back ('(');
				may_unary = true;
			}
			else if (s[i] == ')') {
				while (op.back() != '(')
					process_op (st, op.back()),  op.pop_back();
				op.pop_back();
				may_unary = false;
			}
			else if (is_op (s[i])) {
				char curop = s[i];
				if (may_unary && isunary (curop))  curop = -curop;
				while (!op.empty() && (
					curop >= 0 && priority(op.back()) >= priority(curop)
					|| curop < 0 && priority(op.back()) > priority(curop))
					)
					process_op (st, op.back()),  op.pop_back();
				op.push_back (curop);
				may_unary = true;
			}
			else {
				string operand;
				while (i < s.length() && (isalnum (s[i]) || s[i] == '.' ))
					operand += s[i++];
				--i;
				//cout << s << ' ' << isalnum(s[0]) << isalnum(s[1]) << endl;
				if (isdigit (operand[0]) )
					st.push_back (atof (operand.c_str()));
				//else
				//	st.push_back (get_variable_val (operand));
				may_unary = false;
			}
	while (!op.empty())
		process_op (st, op.back()),  op.pop_back();
	return st.back();
}
#define fin cin
#define fout cout
int main() {
	
	string c;
	getline(cin, c);
	cout << calc(c) << endl;
	return 0;

}
