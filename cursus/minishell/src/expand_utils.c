/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:05:50 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/29 17:25:55 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 *	Function Name: get_var_value
 *
 *	Description:
 *
 *		This function searches the value of a variable in the environment
 *		variables stored in the t_data struct and returns it.
 *
 *	Parameters:
 *
 *		char *var_name - The name of the variable to search for.
 *		t_data *data   - The pointer to the t_data struct with all execution data.
 *
 *	Return Value:
 *
 *		char*	- Returns the value of the environment variable or a empty string
 *				("") if not.
 */
char	*get_var_value(char **var_name, t_data *data, int is_quotes)
{
	int		i;
	int		found;
	char	*var_equal;

	found = 0;
	i = 0;
	var_equal = ft_strcat(&((*var_name)[1]), "=");
	free(*var_name);
	malloc_protection(var_equal, data);
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], var_equal, ft_strlen(var_equal)))
			found = 1;
		if (found)
			break ;
		i++;
	}
	free(var_equal);
	if (found)
		return (ft_strdup(ft_strchr(data->env[i], '=') + 1));
	else if (is_quotes)
		return (ft_strdup(""));
	else
		return (NULL);
}
