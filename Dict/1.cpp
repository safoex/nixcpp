#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <cctype>
#include <vector>
#include <functional>
using namespace std;


template<class T1, class T2> 
class Comparator2 {
	public:
	Comparator2() {}
	bool operator() (const std::pair<T1, T2>& lhs,
			 const std::pair<T1, T2>& rhs) const
	{
		if(lhs.first == rhs.first)
			return lhs.second > rhs.second;
		else
			return lhs.first < rhs.first;
	}

};
#define fin cin
#define fout cout
int main() {
	map<string, unsigned long> freq;
	//ifstream fin("input.txt");
	//ofstream fout("output.txt");
	char c;
	string word("");
	priority_queue<pair<unsigned long,string>,vector<pair<unsigned long, string>>, Comparator2<unsigned long, string>> q;
	while(fin >> noskipws >> c) {
		if(isalpha(c)) {
			word+=tolower(c);	
		}
		else {
			if(word.length() > 0) {
				freq[word] ++;
				word = "";
			}
		}		
	}
	for(auto it = freq.begin(); it != freq.end(); it++) {
		q.push(make_pair(it->second, it->first));
		fout << it->first << ' ' << it->second << endl;
	} 
	while(q.size()) {
		fout << q.top().first << ' ' << q.top().second << endl;
		q.pop();
	}

	return 0;

}
