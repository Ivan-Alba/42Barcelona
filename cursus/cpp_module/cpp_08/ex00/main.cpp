#include "easyfind.hpp"

int	main()
{
	std::vector<int> vec; //push_back() & pop_back() only
	vec.push_back(3);
	vec.push_back(42);
	vec.push_back(-50);
	vec.pop_back(); //Delete -50

	std::list<int> list; //push_back(), push_front(), pop_back() & pop_front()
	list.push_back(1);
	list.push_back(2);
	list.push_front(0);

	std::deque<int> deq; //push_back(), push_front(), pop_back() & pop_front()
	deq.push_back(50);
	deq.push_back(-12);
	deq.push_front(2);
	deq.pop_front(); //Delete 2
	deq.pop_back(); //Delete -12

	try
	{
		::easyfind(vec, 42);
		::easyfind(list, 1);
		::easyfind(deq, 2);
	}
	catch (const std::runtime_error &e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	return (0);
}
