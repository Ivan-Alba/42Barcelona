#include "libft.h"

int	str_array_len(char **array)
{
	int	i;

	if (!array || !array[0])
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}
