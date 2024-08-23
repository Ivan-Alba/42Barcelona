/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:28:42 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/17 19:05:40 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Receives an error message by parameter and prints it on console
void	print_error(char *msg, char	*token)
{
	if (!token)
		ft_printf("%s\n", msg);
	else
		ft_printf("%s \'%s\'\n", msg, token);
}

//Receives an error message by parameter and prints it on console and exits
void	print_error_exit(char *msg, t_data *data)
{
	ft_printf("%s\n", msg);
	free_data(data);
	exit(1);
}

//Returns a char* from a char
char	*string_from_char(char	c)
{
	char	*result;

	result = malloc(sizeof(char) * (1 + 1));
	if (!result)
		return (NULL);
	result[0] = c;
	result[1] = '\0';
	return (result);
}

//Add to an existing char** a new value, freeing the memory and re-allocating it
char	**add_to_array(char	***current, char *new_value)
{
	char	**new;
	int		i;

	if (!(*current) || !(*current)[0])
		new = malloc(sizeof(char *) * 2);
	else
	{
		i = 0;
		while (*current && (*current)[i])
			i++;
		new = malloc(sizeof(char *) * (i + 2));
	}
	if (!new)
		return (NULL);
	i = 0;
	while (*current && (*current)[i])
	{
		new[i] = ft_strdup((*current)[i]);
		i++;
	}
	new[i++] = ft_strdup(new_value);
	new[i] = NULL;
	if (*current)
		free_split(current);
	return (new);
}
