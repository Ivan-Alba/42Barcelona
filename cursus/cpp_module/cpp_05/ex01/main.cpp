#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main(void)
{
	try
	{
		Bureaucrat a("Carolina", 150);
		Bureaucrat b("Jaume", 1);
		Form f("42Form", 15, 1);
		
		std::cout << a << std::endl;
		std::cout << b << std::endl;

		std::cout << f << std::endl;

		//f.beSigned(a);
		//std::cout << f << std::endl;
		
		b.signForm(f);
		//a.signForm(f);
		std::cout << f << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return (0);
}
