#include "Bureaucrat.hpp"

int	main(void)
{
	try
	{
		Bureaucrat a("Carolina", 150);
		Bureaucrat b("Jaume", 1);
		//Bureaucrat c("Ivan", 0);
		//Bureaucrat d("Ana", 151);

		//a.decrementGrade();
		//b.incrementGrade();
		
		std::cout << a << std::endl;
		std::cout << b << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}
