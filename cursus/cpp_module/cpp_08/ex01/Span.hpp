#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>

class Span
{
	private:
		std::vector<int>	vec;
		unsigned int		maxSize;

	public:
		Span();
		Span(unsigned int n);
		Span(const Span &other);
		~Span();

		Span& operator=(const Span &other);

		void	addNumber(int nb);

		template <typename Iterator>
		void	addNumber(Iterator begin, Iterator end)
		{
			for (Iterator i = begin; i != end; ++i)
			{
				addNumber(*i);
			}
		}

		int		shortestSpan();
		int		longestSpan() const;

};

#endif
