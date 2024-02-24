/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:06:29 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/22 19:06:31 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//Checks if there is a '\n' in the string and returns true (1) or false (0)
int	is_next_line(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

//Frees the memory of the received string, assigns NULL and returns NULL
char	*free_and_out(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

//Checks if there is content in *saved after *saved[i] and saves or releases it
int	check_stack(char **saved, int i, char **res)
{
	if ((*saved)[i] != '\0')
	{
		*saved = cut_after_next_line(&*saved);
		if (!*saved)
			return ((int)free_and_out(&*res));
	}
	else
	{
		free(*saved);
		*saved = NULL;
	}
	return (1);
}
