#include <cmath>
#include <fstream>
using namespace std;
class C {
public:
	double re, im;
	C(double _re = 0, double _im = 0) : re(_re), im(_im) {}
	/*C& operator+= (const C& rc) {
		re += rc.re;
		im += rc.im;
		return (*this);
	}*/
	C operator+  (const C& rc) const {
		return C(re + rc.re, im + rc.im);
	}
	
	C operator+  (double rc) const {
		return (*this) + C(rc);
	}
	
	C operator-  (const C& rc) const {
		return C(re - rc.re, im - rc.im);
	}
	
	C operator-  (double rc) const {
		return (*this) - C(rc);
	}
	
	C operator*  (const C& rc) const {
		return C(re*rc.re - im*rc.im, re*rc.im + im*rc.re);
	}
	
	C operator*  (double rc) const {
		return C(re*rc, im*rc);
	}
	
	C operator/  (double rd) const {
		return C(re/rd, im/rd);
	}
	double abs() const {
		return sqrt(re*re + im*im);
	}
	C operator/  (const C& rc) const {
		return (*this)*C(rc.re, -rc.im)/rc.abs()/rc.abs();
	}
	bool operator== (const C& rc) const {
		return re == rc.re && im == rc.im;
	}
	bool operator!= (const C& rc) const {
		return !( *this == rc );
	}
	
	bool operator== (double rc) const {
		return re == rc && im == 0;
	}
	
	bool operator!= (double rc) const {
		return !( *this == rc );
	}
	friend C operator- (double ld, const C& rc)  {
		return C(ld) - rc;
	}
	friend C operator+ (double ld, const C& rc)  {
		return C(ld) + rc;
	}
	friend C operator* (double ld, const C& rc)  {
		return rc*ld;
	}
	friend C operator/ (double ld, const C& rc)  {
		return C(ld)/rc;
	}
	friend bool operator== (double ld, const C& rc)  {
		return rc == ld;
	}
	friend bool operator!= (double ld, const C& rc) {
		return rc != ld;
	}
	
	friend ostream& operator<<(ostream& os, const C& c) {
		return os << c.re << ' ' << c.im;
	}

	
	
};
