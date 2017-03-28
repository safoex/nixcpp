#include <iostream>
#include <stack>
#include <string>
char f(char c) {
	if(c == '(') return ')';
	if(c == '{') return '}';
	if(c == '[') return ']';
	return 0;
}
using namespace std;
int main() {
	stack<char> s;
	char c;
	bool correct = true;
	while(cin >> c) {
		if(c == '(' ) s.push(c);
		else if(c == ')' ) {
			if(s.size() > 0) {
					
				char x = s.top();
				s.pop();
				if(f(x) != c ) {
				//cout << "here" << endl;
				correct = false;
				break;
				}
			}
			else {
				//cout << endl << c << endl; 
				correct = false;
				break;
			} 
		}
		else break;
	}
	//cout << s.empty() << endl;
	correct = correct & s.empty();
	if(correct) cout << "YES";
	else cout << "NO";
	return 0;
}
