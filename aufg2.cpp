#include <iostream>
#include <cmath>
#include "adapt.h"

using namespace std;

class Funktor
{
    const double s, lambda;

public:

    double t;

    Funktor(const double t_in = 0.): s(5./3.), lambda(3.), t(t_in)
    {
    }

    inline double g(const double k)
    {
        return pow(1+k*k,-s*0.5);
    }

    inline double radi(const double k) //radicand
    {
        return ( 1/(4.*lambda*lambda) - k*k/3. );
    }

    double critTerm(const double k)
    {
        if ( k > sqrt(3.)/(2.*lambda) )
        {
            return sin(t * sqrt(-radi(k))) / sqrt(-radi(k));
        } else
        {
            return sinh(t * sqrt(radi(k))) / sqrt(radi(k));
        }
    }

    inline double f(const double k)
    {
        return g(k) * critTerm(k) * exp(-t/(2.*lambda));
    }

    inline double operator ()(const double k)
    {
        return f(k) + f(1./k)/(k*k);
    }
};

int main()
{
    Funktor func;
    Adapt a;

    // TODO: Implement open integration formula for [0,1] integration interval.

    const double step = 1000;

    for ( int i = 1; i < 100./step + 1; i++ )
    {
        const double ergebnis = a.integrate(func, 0, 1);
        cout << func.t << " Ergebnis der Integration: " << ergebnis << endl;
        func.t += step;
    }
}
