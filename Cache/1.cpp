#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>
#include <stack>
#include <set>
#include <unordered_map>

using namespace std;
unordered_map<long, pair<long, long> > cache;

long head = -1;
long tail = -1;
long M = 0;

bool insert_user( long id) {
	if(cache.count(id)) {
		return true;
	}
	else {
		if(cache.size() == M) {
			auto kick_id = cache[tail];
			long new_tail = kick_id.first;
			cache[new_tail].second = -1;
			cache.erase(tail);
			tail = new_tail;
		}
		long new_head = id;
		cache[head].first = new_head;
		cache[new_head] = make_pair(-1, head);
		head = new_head;
		return false;
		
	}
}


#define I cin
#define O cout

int main() {
	
	//ifstream I("input.txt");
	//ofstream O("output.txt");
	//ofstream L("log.txt");
	I >> M;
	long new_id;
	while( I >> new_id) {
		//I >> new_id;
		O << (int)!insert_user(new_id) << ' ';
		//L << new_id << ' ';
	}
}
