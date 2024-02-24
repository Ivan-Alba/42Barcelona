/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:38:59 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/07 17:39:05 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//Comprueba si hay un '\n' en la string y devuelve true (1) o false (0)
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

//Libera la memoria de la string recibida, le asigna NULL y devuelve NULL
char	*free_and_out(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

//Comprueba si hay contenido en *saved tras la posicion i y lo guarda o libera
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
