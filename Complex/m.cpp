#include "c.cpp"
#include <iostream>
int main() {

	C a(0);
	C b(0,1);
	C c(0,1);
	C d(3,4);
	cout << a + d << endl;
	cout << b + d << endl;
	cout << b * d << endl;
	cout << d / b << endl;
	cout << a /b << endl;
	cout << "==abs==" << endl;
	cout << a.abs() << endl;
	cout << (b/c).abs() << endl;
	cout << d.abs() << endl;
	cout << (b *a) << endl;
	cout << b*c << endl;
	
}
