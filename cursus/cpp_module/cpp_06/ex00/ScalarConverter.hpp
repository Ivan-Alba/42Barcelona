#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class	ScalarConverter
{
	public:
		static void convert(const std::string& literal);

	private:
		static bool isCharLiteral(const std::string& literal);
		static bool isSpecialLiteral(const std::string& literal);
		static void printConversions(char c, int i, float f, double d, bool impossible = false);
		static bool isNan(double d);
};

#endif

