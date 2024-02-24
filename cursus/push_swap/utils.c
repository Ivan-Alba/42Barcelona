/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:44:02 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/23 16:05:49 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Frees the memory of parameter ptr and exit with error message
void	free_and_exit(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	write(2, ERROR_MSG, sizeof(ERROR_MSG));
	exit(0);
}

//Allocates memory and set content to \0
void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*res;

	res = malloc(nelem * elsize);
	if (res == NULL)
		return (res);
	else
		ft_bzero(res, nelem * elsize);
	return (res);
}

//Set n elements from void *s to 0
void	ft_bzero(void *s, size_t n)
{
	char	*tmp;

	tmp = s;
	while (n > 0)
	{
		*tmp = 0;
		tmp++;
		n--;
	}
}

//Prints a char * or exit if error
void	protected_write(char *order, int size)
{
	if (order)
	{
		if (write(1, order, size) == -1)
			free_and_exit(order);
	}
}
