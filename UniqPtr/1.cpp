#include <exception>
#include <utility>
#include <iostream>

namespace student {


class illegal_operation : public std::exception {
	virtual const char* what() const throw()	{
    		return "illegal expection";
  	}
};                            //класс исключения



template <class T>
class unique_ptr {
private:
	T* ptr;

public:
    unique_ptr() {                                   //создание пустого объекта, который ничем не владеет
		ptr = nullptr;
	}
    unique_ptr(T* const pointer) {                   //создание объекта, владеющего pointer
		ptr = pointer;
	}
    unique_ptr(unique_ptr<T>&& x) {                  //rvalue копирование
		ptr = x.ptr;
		x.ptr = nullptr;
	}
    unique_ptr(unique_ptr<T> &x) = delete;    //недопустимая операция
    virtual ~unique_ptr() {                                  //разрушение объекта, которым владеет unique_ptr, если он сущесвует
		if (ptr != nullptr) {
			delete ptr;
		}
	}
    T& operator * () {                               //операторы разыменовывания
		try {
			if (ptr == nullptr) throw std::exception();			
			else return *ptr;
		}
		catch(std::exception& e) {
			std::cout << "nullptr" << std::endl;	
		}
	}
    T* operator -> () {
		try {
			if (ptr == nullptr) throw std::exception();
			else return ptr;
		}
		catch(std::exception& e) {
			std::cout << "nullptr" << std::endl;
		}
	}
    unique_ptr& operator =(unique_ptr<T> &&x) {      //присваивание rvalue
		if (ptr == nullptr) {
			ptr = x.ptr;
			x.ptr = nullptr;
		}
		else {
			delete ptr;
			ptr = x.ptr;
			x.ptr = nullptr;
		}
		return *this;
	}
    unique_ptr& operator =(unique_ptr<T> &x) {  //недопустимая операция, необходимо выбрасывать исключение типа illegal_operation
		throw student::illegal_operation();
	}
    T* release() {                                   //сброс прав владения без разрушения объекта, которым владеем с передачей указателя на него
		T* tmp = ptr;
		ptr = nullptr;
		return tmp;
	}
    void reset(T * const p) {                        //смена владения с разрушением предыдущего объекта
		if (ptr == nullptr) {
			ptr = p;
		}
		else {
			delete ptr;
			ptr = p;
		}
	}
    T* get() {                                       //необходимо отдать сырой указатель на объект, которым владеем
		return ptr;
	}
    void swap(unique_ptr<T> &x) {                    //необходимо поменять местами объекты, которыми владеют this и x без разрушения и копирования оных
	T* tmp = ptr;
	ptr = x.ptr;
	x.ptr = tmp;
	
}
    operator bool() {                                //приведение к типу bool. true, если объект, которым владеем существует, false иначе
		if( ptr == nullptr) return false;
		else return true;
	}
};


}
/*
int main() {

	student::unique_ptr<int> A(new int);
	student::unique_ptr<int> B(new int);
	A = std::move(B);
	student::unique_ptr<int> C;
	std:: cout << C << std::endl;
	return 0;
}*/
