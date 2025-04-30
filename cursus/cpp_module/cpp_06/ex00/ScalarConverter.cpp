#include "ScalarConverter.hpp"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include <cctype>

bool	ScalarConverter::isNan(double d)
{
    return d != d;
}

bool	ScalarConverter::isCharLiteral(const std::string& literal)
{
    return literal.length() == 1 && !std::isdigit(literal[0]);
}

bool	ScalarConverter::isSpecialLiteral(const std::string& literal)
{
    return literal == "nan" || literal == "nanf" ||
           literal == "+inf" || literal == "+inff" ||
           literal == "-inf" || literal == "-inff" ||
           literal == "inf" || literal == "inff";
}

void	ScalarConverter::printConversions(
		char c, int i, float f, double d, bool impossible)
{
    std::cout << "char: ";
    if (impossible || d < 0 || d > 127 || isNan(d))
        std::cout << "impossible" << std::endl;
    else if (!std::isprint(c))
        std::cout << "Non displayable" << std::endl;
    else
        std::cout << "'" << c << "'" << std::endl;

    std::cout << "int: ";
    if (impossible || d > std::numeric_limits<int>::max() || d < std::numeric_limits<int>::min() || isNan(d))
        std::cout << "impossible" << std::endl;
    else
        std::cout << i << std::endl;

    std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << d << std::endl;
}

void	ScalarConverter::convert(const std::string& literal)
{
    char	c;
    int		i;
    float	f;
    double	d;

    if (isCharLiteral(literal))
	{
        c = literal[0];
        i = static_cast<int>(c);
        f = static_cast<float>(c);
        d = static_cast<double>(c);
        printConversions(c, i, f, d);
        return;
    }

    if (isSpecialLiteral(literal))
	{
        if (literal.find('f') != std::string::npos)
		{
            f = static_cast<float>(std::atof(literal.c_str()));
            d = static_cast<double>(f);
        }
		else
		{
            d = std::atof(literal.c_str());
            f = static_cast<float>(d);
        }
        printConversions(0, 0, f, d, true);
        return;
    }

    char* end;
    d = std::strtod(literal.c_str(), &end);

    bool isFloat = (*end == 'f' && *(end + 1) == '\0');
    bool isValid = (*end == '\0' || isFloat);

    if (!isValid)
	{
        std::cout << "Invalid literal format" << std::endl;
        return;
    }

    f = static_cast<float>(d);
    i = static_cast<int>(d);
    c = static_cast<char>(d);

    printConversions(c, i, f, d);
}
