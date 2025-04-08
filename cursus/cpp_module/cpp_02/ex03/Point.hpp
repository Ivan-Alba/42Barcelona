#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

class Point
{
	private:
		const Fixed x;
		const Fixed y;

	public:
		Point();
		Point(const float x, const float y);
		Point(const Point& other);

		Point& operator=(const Point& other);

		~Point();

		Fixed	getX(void) const;
		Fixed	getY(void) const;
};

#endif
