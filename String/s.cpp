#include <fstream>
//#include <iostream>
//using namespace std;
class S {
private:
	char* s;
	int len;
public:
	S(char c) { s = new char[2]; len = 1; s[0] = c;s[1] = 0; }
	S() {
		s = new char[1];
		s[0] = 0;
		len = 0;
	}	
	S(const char* str) {
		len = 0;
		//std::cout <<"!";
		if (str[0] != 0)
		while (str[len] != 0) len++;
		s = new char[len + 1];
		if(len != 0)
		for (int i = 0; i < len; i++)
			s[i] = str[i];
		s[len] = 0;
	}
	S(const S& str) {
		s = new char[str.length() + 1];
		for (int i = 0; i < str.length(); i++)
			s[i] = str.s[i];
		s[str.length()] = 0;
	}
	unsigned int length() const {
		int _len = 0;
		while(s[_len] != 0) _len++;
		return (unsigned)_len;
	}
	
	S& operator+= (const S& rstr) {
		//std::cout << "+=";
		int tmp_len = length() + rstr.length() ;
		char *tmp = new char[tmp_len + 1];
		int i = 0;
		for (; i < length(); i++)
			tmp[i] = s[i];
		int j = 0;
		for (i = length(), j = 0; i <= tmp_len; i++,j++)
			tmp[i] = rstr.s[j];
		//tmp[tmp_len] = 0;
		//len = len + rstr.len;
		
		delete[] s;
		s = tmp;
		return (*this);
	}

	S operator+ (const S& rstr) const{
		//std::cout << "+";
		S res(s);
		res+=rstr;
		return res;
	}
	S& operator= (const S& rstr) {
		//std::cout << "=";
		delete[] s;
		s = new char[rstr.length()+1];
		for(int i =0; i < rstr.length(); i++)
			s[i] = rstr.s[i];	
		return (*this);
	}
	char& operator[] ( int i) {
		return s[i];
	}
	const char operator[] ( int i) const  {
		return s[i];
	}
	const char* str() const {
		return s;
	}

	~S() {delete[] s;}	
	friend std::ostream& operator<< (std::ostream& os, const S& s) {
		for(int i = 0; i < s.length(); i++)
			os << s[i];
		return os;
	}


};

