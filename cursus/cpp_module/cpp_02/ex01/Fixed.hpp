#ifndef FIXED_HPP
# define FIXED_HPP

#include <ostream>

class Fixed {

private:
	int					number;
	static const int	fractional = 8;

public:
	Fixed();
	Fixed(const Fixed &other);
	Fixed(const int value);
	Fixed(const float value);
	~Fixed(void);

	Fixed &operator=(const Fixed &other);

	void	setRawBits(int const raw);
	int		getRawBits(void) const;
	float	toFloat(void) const;
	int		toInt(void) const;

    friend std::ostream& operator<<(std::ostream& out, const Fixed& fixed);
};


#endif
