#include <iostream>
#include "Point.hpp"

extern bool bsp(Point const a, Point const b, Point const c, Point const p);

int main(void)
{
    Point A(0, 0), B(5, 0), C(2, 5);
    Point P(1, 1), P2(2, 5), P3(6, 0), P4(2.5, 3);

    if (bsp(A, B, C, P)) {
        std::cout << "El punto P está dentro del triángulo." << std::endl;
    } else {
        std::cout << "El punto P está fuera del triángulo." << std::endl;
    }

   if (bsp(A, B, C, P2)) {
        std::cout << "El punto P2 está dentro del triángulo." << std::endl;
    } else {
        std::cout << "El punto P2 está fuera del triángulo." << std::endl;
    }

  if (bsp(A, B, C, P3)) {
        std::cout << "El punto P3 está dentro del triángulo." << std::endl;
    } else {
        std::cout << "El punto P3 está fuera del triángulo." << std::endl;
    }


  if (bsp(A, B, C, P4)) {
        std::cout << "El punto P4 está dentro del triángulo." << std::endl;
    } else {
        std::cout << "El punto P4 está fuera del triángulo." << std::endl;
    }	

    return (0);
}
