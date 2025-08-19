#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>

template <typename T>
class MutantStack : public std::stack<T>
{
	private:

	public:
		typedef typename std::stack<T>::container_type::iterator iterator;
		MutantStack<T>::iterator begin();
		MutantStack<T>::iterator end();	

};

#include "MutantStack.tpp"

#endif
