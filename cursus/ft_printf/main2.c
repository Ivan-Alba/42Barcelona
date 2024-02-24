#include "ft_printf.h"
#include <limits.h>

int	main(void)
{
	printf("|LENGTH: %d\n", ft_printf("%01.d, %01.d, %01.d, %01.d, %01.d, %01.d, %01.d, %01.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX));
	printf("|LENGTH: %d\n", printf("%01.d, %01.d, %01.d, %01.d, %01.d, %01.d, %01.d, %01.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX));

	printf("|LENGTH: %d\n", printf("%+10.1d, %+10.1d, %+10.1d, %+10.1d, %+10.1d, %+10.1d, %+10.1d, %+10.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX));
	printf("|LENGTH: %d\n", ft_printf("%+10.1d, %+10.1d, %+10.1d, %+10.1d, %+10.1d, %+10.1d, %+10.1d, %+10.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX));

 	printf("%0100u, %0100u, %0100u, %0100u, %0100u, %0100u, %0100u, %0100u, %0100u, %0100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	ft_printf("%0100u, %0100u, %0100u, %0100u, %0100u, %0100u, %0100u, %0100u, %0100u, %0100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);

	printf("|LENGTH: %d\n", printf("%#08x", 100));
	printf("|LENGTH: %d\n", ft_printf("%#08x", 100));	
}
