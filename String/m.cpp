#include "s.cpp"
#include <iostream>
using namespace std;
int main() {
	S str("abc");
	S a,b,c;
	cout << str << endl;
	S str2(str);
	cout <<str2 <<endl;
	str2+=str;
	cout <<str2 << endl;
	cout <<str2.length() << endl;
	cout <<str2[1] << endl;
	str2 = str2+ str;
	a = str2 + str;
	b = a + c;
	S v, l;
	S z = v + l;
	cout << z << '\n' << z.length() << endl;
	z = v + b;
	cout << a << endl;
	cout << z << endl;
	cout << z.length() << endl;;
	cout << str2.length() << endl;
	S A("ab_c");
	A = S("");
	cout << A << endl;
	cout << A.length();
	A = S("abc");
	cout << A << endl;
}
