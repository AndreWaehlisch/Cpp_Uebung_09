#ifndef _XORSHIFT_H_
#define _XORSHIFT_H_

#ifdef _MSC_VER
typedef unsigned __int64 Ullong;
#else
typedef unsigned long long int Ullong;
#endif

// **********
class Xorshift
{
	Ullong x;
	const Ullong a1, a2, a3, aMWC;
	double div;

	public:
	Xorshift(Ullong j=rand()) : x(4101842887655102017LL), a1(21), a2(35), a3(4), aMWC(2685821657736338717LL)
	{
		x ^= j;
		x = int64();
		div = pow(2.,-64);
	}

	// Calculate 64-bit positive random integer
	Ullong int64()
	{
		x ^= x >> a1;
		x ^= x << a2;
		x ^= x >> a3;
		return x * aMWC;
	}

	// Return random double in [0,1]
	double doub()
	{
		return div * int64();
	}

	// Return random double in [a,b]
	double doub(const double a, const double b)
	{
		return a + (b-a) * doub();
	}
};

#endif
