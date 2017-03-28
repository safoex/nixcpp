#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;
bool isGoodID(const char* ID) {
	bool correct = true;
	for(int i = 0; i < strlen(ID); i++) {
		correct &= (ID[i] >= '0' && ID[i] <= '9') || (ID[i] >= 'A' && ID[i] <= 'Z') || (ID[i] >= 'a' && ID[i] <= 'z');
	}
	//correct &= (priority >= 0 && priority <= 1);
	correct &= (strlen(ID) == 32);
	return correct;

}
bool isGoodPriority(double _priority) {
	return _priority >= 0 && _priority <= 1;
}
class Node {
public:
	double priority;
	char* ID;
	int time;
	static int global_time;
	Node(): ID(nullptr) {}
	Node(double priority, const char* ID) : priority(priority), ID(strcpy(new char[strlen(ID)+1], ID)) {
		time = Node::global_time;
		Node::global_time ++;
	}
	~Node() {
		delete[] ID;
	}
	

	bool isCorrect() {
		/*bool correct = true;
		for(int i = 0; i < strlen(ID); i++) {
			correct &= (ID[i] >= '0' && ID[i] <= '9') || (ID[i] >= 'A' && ID[i] <= 'Z');
		}
		correct &= (priority >= 0 && priority <= 1);
		correct &= (strlen(ID) == 32);
		return correct;*/
		return isGoodID(ID) && isGoodPriority(priority);
	}
	bool operator<(const Node& right) {
		return (this->priority < right.priority || ( this->priority == right.priority && time < right.time)); 
	}
	
};

int Node::global_time = 0;
template<class T> class ListNode {
public:
	ListNode *prev, *next;
	T* value;
	ListNode(T* value= nullptr, ListNode* prev = nullptr, ListNode* next = nullptr) : value(value), prev(prev), next(next) {}
	
};
template<class T> class List {
public:	
	ListNode<T>* head;
	ListNode<T>* tail;
	int size;
	List(ListNode<T>* head = nullptr, ListNode<T>* tail = nullptr) : head(head), tail(tail), size(0) {}
	~List() {
		auto it = head;
		while(it != nullptr) {
			auto todelete = it;
			it = it->next;
			delete todelete->value;
			delete todelete;
		}
	}
	void insert(T* node) {
		auto it = head;
		//std::cout <<'\t'<< Node::global_time <<std::endl;
		while(it != nullptr && (*(it->value) < *node)) {
			it = it->next;
		}
		if(it == nullptr) {
			if(tail == nullptr) {
				head = tail = new ListNode<T>(node);
			}
			else {
				tail = tail->next = new ListNode<T>(node, tail, nullptr);
			}
		}
		else {
			if (it == head) {
				head = head->prev = new ListNode<T>(node,nullptr,head); 
			}
			else {
				it->prev = it->prev->next = new ListNode<T>(node, it->prev, it);
			}
		}
		++size;
	}
	T* pop() {
		if(head == nullptr) {
			return nullptr;
		}
		auto  todelete = head;
		//std::cout << (void*)(head) <<std::endl;
		//std::cout << (void*)(head->value) << std::endl;
		//std::cout << (void*)(head->next) << std::endl;
		T* toreturn = head->value;
		//std::cout << size << std::endl;
		if(head == tail) {
			head = tail = nullptr;	
		}
		if(head != tail) {
			(head = head->next)->prev = nullptr;
		}
		--size;
		delete todelete;
		return toreturn;
	}
	int length() {return size;}
};


class FiniteAutomat {
        List<pair<pair<string,string>, pair<string,string> > > table;
public:
        FiniteAutomat() {}

        FiniteAutomat& operator+=(const pair<pair<string, string>,pair<string, string> >& action) {
                table.insert(new pair<pair<string,string>,pair<string,string>>(action));
                return *this;
        }

        pair<string,string>& operator[](const pair<string,string>& go) {
                for(auto it = table.head; it != table.tail; it = it->next) {
			if(it->value->first == go) return it->value->second;
		}
        }

        /*const string operator[] (const pair<string,string>& go) const {
                return table[go];
        }*/
};


#define fin cin
#define fout cout
#define p make_pair
int main() {
	
	string buffer;
	List<Node> storage;
	//ifstream fin("input.txt");
	//ofstream fout("output.txt");
	//ofstream log("log.txt");
	
	FiniteAutomat a;
	// "ready", "add", "finish", "add(s)"
	// "process", "add", "finish", "number", "string","trash"
	a += p(p("ready","process"),p("ready", "process"));
	a += p(p("ready","add"),p("add", "nothing"));
	a += p(p("ready","finish"),p("finish","nothing"));
	a += p(p("ready","number"),p("ready","skipstr"));
	a += p(p("ready","string"),p("ready","skipstr"));
	a += p(p("ready","trash"),p("ready","skipstr"));
	a += p(p("add","number"),p("add(s)","nothing"));
	a += p(p("add","string"),p("ready","skipstr"));
	a += p(p("add","process"),p("ready","skipstr")); // ??
	a += p(p("add","finish"),p("ready","skipstr"));
	a += p(p("add","add"),p("ready","skipstr"));
	a += p(p("add","trash"),p("ready","skipstr"));
	a += p(p("add(s)","finish"),p("ready","skipstr"));
	a += p(p("add(s)","string"),p("ready","tryadd"));
	a += p(p("add(s)","number"),p("ready","skipstr"));
	a += p(p("add(s)","process"),p("ready","skipstr"));
	a += p(p("add(s)","add"),p("ready","skipstr"));
	a += p(p("add(s)","trash"),p("ready","nothing"));
	a += p(p("finish","finish"),p("finish","nothing"));
	a += p(p("finish", "add"),p("skipstr","skipstr"));
	a += p(p("finish", "string"),p("ready","skipstr"));
	a += p(p("finish", "process"), p("ready","skipstr"));
	a += p(p("finish", "number"), p("ready","tryfinish"));
	a += p(p("finish","trash"),p("ready","skipstr"));

	//char state[MAX_LENGTH];
	//strcpy(state, "ready");
	string state("ready");
	//char action[MAX_LENGTH];
	//char event[MAX_LENGTH];
	//strcpy(action,"nothing");
	string action("nothing"),event;
	//char id[MAX_LENGTH];
        string id;
	double prior = 0;
        long long finish_number = 0;
        bool isDouble = false;
	string buffer0;
	while(getline(fin,buffer0)) {
	stringstream sbuffer0(buffer0);
	while(sbuffer0 >> buffer) {
		//cout << buffer << endl;
		//char id[MAX_LENGTH];
		//double priority = 0;
		//long long finish_number = 0;
		//bool isDouble = false;
		if(buffer == "PROCESS") {
			event = "process";
		} 
		else if(buffer == "ADD") {
			event = "add";
		}
		else if(buffer == "FINISH") {
			event = "finish";
		}
		else if(isGoodID(buffer.c_str())) {
			event = "string";
			id = buffer;
		}
		else {
			bool correct_number = true;
			/*bool was_dot = false;
			for(int i = int(buffer[0]=='-'); i < strlen(buffer); i++) {
				if(buffer[i] <= '9' && buffer[i] >= '0') continue;
				if(buffer[i] == '.')  { 
					if(!was_dot) was_dot = true;
					else correct_number = false;
					continue;
				}
				correct_number = false;
			}*/
			char buf2[2000];
			int success_int = sscanf(buffer.c_str(),"%lld%s",&finish_number,buf2);
			int success_double = sscanf(buffer.c_str(),"%lf%s",&prior,buf2);
			if(correct_number && ((success_int || success_double) && success_double<2)) event = "number";
			else event = "trash";
		}

		auto next = a[p(state, event)];
		state = next.first;
		action = next.second;
		//log << state << '\t' << action << endl;
		if(action == "skipstr") {
			break;
		}
		else if(action == "process") {
			if(storage.length() > 0) {
				auto n = storage.pop();
				fout <<n->ID << endl;
				delete n;
			}
		}
		else if(action ==  "tryadd") {
			if(isGoodPriority(prior) && isGoodID(id.c_str())) {
				Node* node = new Node(prior, id.c_str());
				storage.insert(node);
			}
		}
		else if(action ==  "tryfinish") {
			if(finish_number >= 0 && storage.length() >= finish_number) {
				for(int i = 0; i < finish_number; i++) {
					auto n = storage.pop();
					fout << n->ID << endl;
					delete n;
				}
				fout << storage.length() << endl;
				return 0;
			}
		}
		// "process", "add", "finish", "number", "string","trash"
		/*if(!strncmp(buffer, "PROCESS",7)) {
			char buffer2[MAX_LENGTH];
			strcpy(buffer2,"");
			int success = sscanf(buffer+7,"%s",buffer2);
			if(success > 0 && strlen(buffer2)>0) { continue;}
			if(storage.length() > 0) {
				auto n = storage.pop();
				fout << n->ID << endl;
				delete n;
			}
		}
		else if(!strncmp(buffer, "ADD",3)) {
 			double priority;
			char buffer2[MAX_LENGTH];
			char buffer3[MAX_LENGTH];
			int success = sscanf(buffer+3,"%lf%s%s",&priority, buffer2, buffer3);
			if(success != 2) continue;
			Node* node = new Node(priority, buffer2);
			if(node->isCorrect( ) ) {
				storage.insert(node);
			}
			else delete node;
			
		}
		else if(!strncmp(buffer, "FINISH",6)) {
			long long n;
			char buffer3[MAX_LENGTH];
			int success = sscanf(buffer+6,"%lld%s",&n,buffer3);
			if(success != 1) continue;
			if(n >= 1 && n <= storage.length()) {
				for(int i = 0; i < n; i++) {
					//cout << "BBBBBBB" << endl;
					auto n = storage.pop();
					if(n !=nullptr)
					fout << n->ID << endl;
					//cout << "AAAAAAA" << endl;
					delete n;
				}
				fout << storage.length() << endl;
				return 0;
			}
		}*/
	}
	}
	return 0;
}
