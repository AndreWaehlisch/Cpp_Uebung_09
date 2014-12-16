#include <iostream>
#include <cmath>
#include <cstdlib>
#include "xorshift.h"
#include <time.h> 
using namespace std;

class Func
{
	double c;
	
	inline double f(const double x)
	{
		return c*x*log(x);
	}
	
	public:
	
		Func(const double cIN): c(cIN)
		{	
		}
		
		inline double operator () (const double x)
		{
			return f(x);
		}
		
		//N: number of random values; a/b: boundaries; mean/meansquared: result
		inline void calcMeans(const int N, const double a, const double b, double &mean, double &meansquared)
		{
			static Xorshift RNG(time(NULL));	// comes from xorshift.h
			
			mean = 0;
			meansquared = 0;
			
			for (int i=0; i<N; i++)
			{
				const double fRandom = f(RNG.doub(a,b));
				mean += fRandom;
				meansquared += (fRandom*fRandom);
			}
			
			mean *= (1./N);
			meansquared *= (1./N);
		}
};

int main()
{
	Func myFunc(-4);	// function to integrate
	
	const double a = 0.;	// lower integration boundary
	const double b = 1.;	// upper integration boundary
	const double V = b-a;	// "volume" in 1D
	
	for ( int N=2; N < (2<<20); N=N<<1 )	// Number of random numbers used for MC-integration
	{
		double fMean;
		double fMeanSquared;
		
		myFunc.calcMeans(N, a, b, fMean, fMeanSquared);	// calculate fMean and fMeanSquared

		const double s = V * sqrt( (fMeanSquared-(fMean*fMean))/ ((double) N) );	// standard deviation
		const double result = V*fMean;	// approximation for the integral
		
		cout << "N=" << N << "\t\tF=" << result << "\ts=" << s << endl;
	}
}
