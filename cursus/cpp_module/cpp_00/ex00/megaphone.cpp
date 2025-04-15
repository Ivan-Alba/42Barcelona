#include <iostream> 
#include <cctype>
#include <cstring>

int	main(int argc, char **argv)
{
	const char	*predefined;

	predefined = "* LOUD AND UNBEARABLE FEEDBACK NOISE *";

	if (argc == 1)
		std::cout << predefined << std::endl;
	else
	{
		for (int j = 1; j < argc; j++)
		{
			for (int i = 0; i < (int)std::strlen(argv[j]); i++)
			{
				std::cout << (char)std::toupper(argv[j][i]);
			}
		}
		std::cout << std::endl;
	}
	return (0);
}
