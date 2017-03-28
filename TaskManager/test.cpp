#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

int main() {

	char buffer[200];
	cin >> buffer;
	long long num;
	char buf2[200];
	double db;
	int success = sscanf(buffer,"%lf%s",&db, buf2);
	cout << endl <<success<<endl << db << endl;
	return 0;
}
