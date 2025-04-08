#include "Point.hpp"

int abs(int x)
{
	return (x < 0) ? -x : x;
}

double area(Point A, Point B, Point C)
{
    return (abs(A.getX().toFloat() * (B.getY().toFloat() - C.getY().toFloat()) +
                B.getX().toFloat() * (C.getY().toFloat() - A.getY().toFloat()) +
                C.getX().toFloat() * (A.getY().toFloat() - B.getY().toFloat()))) / 2.0;
}

bool bsp( Point const a, Point const b, Point const c, Point const p)
{
	double	A_ABC, A_ABP, A_BCP, A_CAP;
	double	epsilon = 1e-6;

	A_ABC = area(a, b, c);
	A_ABP = area(a, b, p);
	A_BCP = area(b, c, p);
	A_CAP = area(c, a, p);

	if (A_ABP == 0 || A_BCP == 0 || A_CAP == 0) {
        return (false);
    }

	return (abs(A_ABC - (A_ABP + A_BCP + A_CAP)) < epsilon);
}
