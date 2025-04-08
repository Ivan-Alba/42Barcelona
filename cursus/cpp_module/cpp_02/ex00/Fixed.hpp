#ifndef FIXED_HPP
# define FIXED_HPP

class Fixed {

private:
	int					number;
	static const int	fractional = 8;

public:
	Fixed();
	Fixed(const Fixed &other);
	~Fixed(void);

	Fixed &operator=(const Fixed &other);

	void	setRawBits(int const raw);
	int		getRawBits(void) const;

};


#endif
