#ifndef _QUADRATURE_H_
#define _QUADRATURE_H_
using namespace std;

// **********
// Abstract base class Quadrature
class Quadrature
{
	protected:
	int n;

	public:
	Quadrature() : n(0)
	{
	}

// 	Abstract method to be redefined in any class derived from Quadrature
	virtual double next() = 0;
};

// **********
// TODO: Derived class Trapzd to implement the trapezoidal rule
template <class T>
class Trapzd : public Quadrature
{
	...

// 	TODO: Implement integration routine
	double next()
	{
		...

};

#endif
