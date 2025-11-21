#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe
{
	private:
		std::vector<size_t>	generateJacobsthal(size_t n) const;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		~PmergeMe();

		PmergeMe& operator=(const PmergeMe &other);

		void	mergeInsertionSort(const std::deque<unsigned int> &input,
					std::deque<unsigned int> &sorted) const;
		void	mergeInsertionSort(const std::vector<unsigned int> &input,
					std::vector<unsigned int> &sorted) const;

		unsigned int	parseNumber(const std::string &str) const;
};

#endif
