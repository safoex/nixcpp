#include <exception>
#include <utility>
#include <iostream>

namespace student {


template <class T>
class Counter {
	int strong_refs;
	int weak_refs;
	T* data;
	template<class TT> friend class shared_ptr;
public:
	Counter(T* ptr = nullptr):strong_refs(0), weak_refs(0),data(ptr) {}
	virtual ~Counter() { if(data != nullptr) delete data;}
	Counter* add_strong_ref() {strong_refs++; return this;}
	Counter* add_weak_ref() {weak_refs++; return this;}
	int count_strong_refs() {return strong_refs;}
	int count_weak_refs() {return weak_refs;}
	void remove_strong_ref() {--strong_refs;}
	void remove_weak_ref() {--weak_refs;}
	bool remove_ready() { return (weak_refs ==0 && strong_refs == 0);}
	bool expired() {return strong_refs == 0;}
	void try_remove() {if(expired() && data != nullptr) {delete data; data = nullptr;} }
	T* get() {return data;}
};


template <class T>
class shared_ptr {

	Counter<T> *counter; 
	template<class TT> friend class weak_ptr;

public:
    shared_ptr() : counter(nullptr) {}    //создание пустого объекта, который ничем не владеет
    shared_ptr(T* pointer) : counter(new Counter<T>(pointer)) {
		counter->add_strong_ref();
	}           //создание объекта, владеющего pointer
    shared_ptr(shared_ptr &&other) : counter(other.counter) {  
		other.counter = nullptr; 
	}  //rvalue копирование
    shared_ptr(shared_ptr const &other) : counter(other.counter) { 
	if(counter != nullptr) 
		counter->add_strong_ref(); 
	} //конструктор копирования, реализует равные права на владения обоими shared_ptr
    virtual ~shared_ptr() { 
		if(counter != nullptr) { 
			counter->remove_strong_ref();
			counter->try_remove();
			if(counter->remove_ready()) {
				delete counter;
			}
		}
	}                       //разрушение объекта, которым владеет этот shared_ptr, если он больше никому не принадлежит
    T& operator* () {
		try {
			if (counter == nullptr || counter->get() == nullptr) throw std::exception();			
			else {
				return *(counter->get());
			}
		}
		catch(std::exception& e) {
			std::cout << "nullptr" << std::endl;	
		}

	  }             //операторы разыменовывания
    T* operator -> () {
		try {
			if (counter == nullptr || counter->get() == nullptr) throw std::exception();			
			else return counter->get();
		}
		catch(std::exception& e) {
			std::cout << "nullptr" << std::endl;	
		}
	}
    shared_ptr& operator =(shared_ptr<T> &&other) {
		if(counter != nullptr) {
			counter->remove_strong_ref();
			counter->try_remove();
			if(counter->remove_ready()) { delete counter;  }
		}
		counter = other.counter;
		other.counter = nullptr;	
		return *this;
		
	}      //присваивание rvalue
    shared_ptr& operator =(shared_ptr<T> const& other) {
		return (*this = std::move(shared_ptr<T>(other)));
	}  //присваивание (с разделением прав)
    void reset(T *p = nullptr) {
		*this = std::move(shared_ptr<T>(p));
	}  //смена владения с разрушением по необходимости предыдущего объекта
    T* get() { 
		try {
			if (counter == nullptr) throw std::exception();			
			else return counter->get();
		}
		catch(std::exception& e) {
			std::cout << "nullptr" << std::endl;	
		}
	}                                       //необходимо отдать сырой указатель на объект, которым владеем
    void swap(shared_ptr<T> &x) {
		Counter<T> *tmp = x.counter;
		x.counter = counter;
		counter = tmp;
	}                    //необходимо поменять местами объекты, которыми владеют this и x без разрушения и копирования оных
    operator bool() {
		return !(counter == nullptr);
	}                                //приведение к типу bool. true, если объект, которым владеем существует, false иначе
    int use_count() {if(counter == nullptr) return 0; else return counter->count_strong_refs();};                               //возвращает количество shared_ptr, разделяющих владение, включая данный};
    //void pr_c() {std::cout << counter << ' ';if(counter != nullptr) std::cout << counter->data << '\n';}
};

template<class T>
class weak_ptr
{
	Counter<T> *counter;
	//friend class shared_ptr<T>;
public:
	weak_ptr() :counter(nullptr) {};
	weak_ptr(weak_ptr const & other) {
		counter = other.counter;
		if(counter != nullptr) counter->add_weak_ref();
	}
	weak_ptr(weak_ptr && other) {
		counter = other.counter;
		other.counter = nullptr;
	};
	weak_ptr(shared_ptr<T> const &master) {
		counter = master.counter;
		if(counter != nullptr) counter->add_weak_ref();
		
	} 		//создание weak_ptr, разделяющего владение с shared
	virtual ~weak_ptr() { 
			if(counter !=nullptr) {
				counter->remove_weak_ref(); 
				if(counter->remove_ready()) delete counter; 
				}
			}
	weak_ptr& operator = (weak_ptr && other) {
			if(counter != nullptr) {
				counter-> remove_weak_ref();
				if(counter->remove_ready()) { delete counter; }
			}
			counter = other.counter;
			other.counter = nullptr;
			return *this;
		}
	weak_ptr& operator = (weak_ptr const & other) { 			
			return (*this = std::move(shared_ptr<T>(other)));
		}
	
	void swap (weak_ptr &other) {
			Counter<T> *tmp = other.counter;
			other.counter = counter;
			counter = tmp;
		} 				//обмен без копирования и стирания
	void reset() {
			*this = std::move(shared_ptr<T>());
		}								//сброс владения
	int use_count() {
			if(counter == nullptr) return 0;
			else return counter->count_strong_refs();
		} 							//число shared_ptr владеющих объектом
	bool expired() {
		return counter == nullptr || counter->expired();
	}								//проверка на валидность. true, если объект "испортился", false, если объект валиден
	shared_ptr<T> lock() {
		if(expired()) return shared_ptr<T>();
		shared_ptr<T> tmp;
		tmp.counter = counter;
		counter->add_strong_ref();
		return tmp; 
	};						//возвращает shared_ptr, владеющий тем же объектом
};


};
/*
int main() {

	
	student::shared_ptr<int> A(new int(4));

	student::weak_ptr<int> wA(A);
	student::shared_ptr<int> V(new int(5));
	V = wA.lock();
	student::shared_ptr<int> Y(new int(7));
	Y = wA.lock();
	std::cout << student::shared_ptr<int>(new int(5)).use_count();
	//std::cout << *V <<' '<< V.use_count() << std::endl;
	//std::cout << "I'm heree! "<<std::endl;
	//std::cout << "I'm still heree! "<<std::endl;

	//student::weak_ptr<int> Z;
	
	student::shared_ptr<int> X(new int(6));
		//Z = student::weak_ptr<int>(X);
	//A.pr_c(); V.pr_c(); Y.pr_c();X.pr_c();
	//std::cout << V.use_count() << ' ' << A.use_count() << ' '<< std::endl;
	return 0;
}*/
