/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:28:42 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/29 17:32:07 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Receive a char** and free all of its contents
void	free_split(char ***splitted)
{
	int	i;

	i = 0;
	if (splitted && *splitted)
	{
		while ((*splitted)[i])
		{
			free((*splitted)[i]);
			(*splitted)[i] = NULL;
			i++;
		}
		free(*splitted);
		*splitted = NULL;
	}
}

//Returns a char* from a char
char	*str_from_char(char c)
{
	char	*result;

	result = malloc(sizeof(char) * (1 + 1));
	if (!result)
		return (NULL);
	result[0] = c;
	result[1] = '\0';
	return (result);
}

char	*concat_char_to_str(char *str, char c, t_data *data)
{
	char	*tmp;
	char	*result;

	tmp = str_from_char(c);
	if (!tmp)
	{
		if (str)
			free(str);
		print_error_exit(MALLOC_ERROR, data);
	}
	result = ft_strcat(str, tmp);
	free(tmp);
	if (str)
	{
		free(str);
		str = NULL;
	}
	if (!result)
		print_error_exit(MALLOC_ERROR, data);
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

char	**str_array_dup(char **origin)
{
	char	**new_array;
	int		i;

	i = 0;
	while (origin && origin[i])
		i++;
	new_array = malloc(sizeof(char *) * (i + 1));
	if (!new_array)
		return (NULL);
	new_array[i] = NULL;
	while (--i >= 0)
	{
		new_array[i] = ft_strdup(origin[i]);
		if (!new_array[i])
			return (NULL);
	}
	return (new_array);
}
