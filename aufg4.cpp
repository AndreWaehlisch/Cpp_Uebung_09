#include <iostream>
#include <cmath>
#include "threedim.h"
using namespace std;

class Funktor3D
{
    // paramters, defined at constructor
    const double a, b, c;

public:

    // upper and lower x-boundaries, defined at constructor
    double x0, x1;

    // upper y-boundary
    double y1(const double x)
    {
        double result;

        if ( abs(0.5 - (x/a)*(x/a)) < 1e-14 )	// ohne diese zusätzliche Prüfung kann die Funktion "nan" zurückgeben (es wird versucht sqrt(-|z|) zu berechnen, wobei z fast 0 ist), dies führt dann später zu einem "segmentation fault" error
            result = 0;
        else
            result = b*sqrt(0.5 - (x/a)*(x/a));

        return result;
    }

    // lower y-boundary
    double y0(const double x)
    {
        return -y1(x);
    }

    // lower z-boundary
    double z0(const double x, const double y)
    {
        return c*sqrt((x/a)*(x/a) + (y/b)*(y/b));
    }

    // upper z-boundary
    double z1(const double x, const double y)
    {
        return c*sqrt(1. - (x/a)*(x/a) - (y/b)*(y/b));
    }

    // CONSTRUCTOR
    Funktor3D(): a(1), b(2), c(3), x0(-sqrt(0.5)), x1(+sqrt(0.5))
    {
    }

    // function to integrate (provide dummy parameters x,y,z because underlying header call needs it this way)
    double operator() (const double x, const double y, const double z)
    {
        return 1;
    }
};

int main()
{
    cout.precision(15);
    Funktor3D f;
    Quad3D<Funktor3D> myQuad(f);
    cout << "Ergebnis der Integration: " << myQuad.integrate() << endl; //

    // Das Ergebnis (3.68 ...) stimmt bis auf die 12te Nachkommastelle mit dem analytischen Ergebnis überein.
}
