#include "RPN.hpp"
#include <stdexcept>
#include <cctype>

RPN::RPN() {}

RPN::RPN(const RPN &other)
{
	*this = other;
}

RPN::~RPN() {}

RPN& RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		stack = other.stack;
	}

	return (*this);
}

bool	RPN::isFormatValid(std::string &line) const
{
	trim(line);

	for (size_t i = 0; i < line.size(); ++i)
	{
		if (i % 2 == 0 && (!std::isdigit(line[i]) && line[i] != '+'
			&& line[i] != '-' && line[i] != '*' && line[i] != '/'))
		{
			return (false);
		}

		if (i % 2 == 1 && line[i] != ' ')
		{	
			return (false);
		}	
	}

	return (true);
}

unsigned int	RPN::operate(unsigned int a, unsigned int b, char op) const
{
	switch (op)
	{
		case '+':
			return (a + b);
		case '-':
			return (a - b);
		case '*':
			return (a * b);
		case '/':
			return (a / b);
		default:
			throw std::invalid_argument("wrong operator");
	}
}

unsigned int	RPN::calculate(const std::string &line)
{
	unsigned int	tmpA;
	unsigned int	tmpB;
	unsigned int	result;

	for (size_t i = 0; i < line.size(); ++i)
	{
		if (std::isdigit(line[i]))
		{
			stack.push(line[i] - '0');
		}
		else if (line[i] != ' ')
		{
			if (!stack.empty())
			{
				tmpB = stack.top();
				stack.pop();
				if (!stack.empty())
				{
					tmpA = stack.top();
					stack.pop();
				}
				else
					throw std::runtime_error("wrong format.");
			}
			else
				throw std::runtime_error("wrong format.");

			stack.push(operate(tmpA, tmpB, line[i]));
		}
	}

	if (stack.empty())
		throw std::runtime_error("wrong format.");
	
	result = stack.top();
	stack.pop();

	if (!stack.empty())
		throw std::runtime_error("wrong format.");

	return (result);
}


void	RPN::trim(std::string& s) const
{
    // Trim left
    std::string::size_type start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }

    // Trim right
    std::string::size_type end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) {
        --end;
    }

    s = s.substr(start, end - start);
}


