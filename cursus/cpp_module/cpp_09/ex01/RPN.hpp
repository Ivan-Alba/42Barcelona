#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RPN
{
	private:
		std::stack<unsigned int> stack;

		void	trim(std::string &s) const;

	public:
		RPN();
		RPN(const RPN &other);
		~RPN();

		RPN& operator=(const RPN &other);

		bool			isFormatValid(std::string &line) const;
		unsigned int	calculate(const std::string &line);
		unsigned int	operate(unsigned int a, unsigned int b, char op) const;
};

#endif
