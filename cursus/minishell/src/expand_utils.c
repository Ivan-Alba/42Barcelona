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
 *	Function Name: concat_var_value
 *
 *	Description:
 *
 *		This function concatenates the content of a string and the value of an
 *		environment variable. It overwrites the original variable.
 *		IMPORTANT! Its previous memory allocation must be freed from where the
 *		call occurs with an auxiliary variable.
 *
 *	Parameters:
 *
 *		char **current_str	- A pointer to the previous string.
 *		char *var			- The name of the environment variable to expand.
 */
void	concat_var_value(char **current_str, char *var, t_data *data)
{
	char	*var_value;

	var_value = get_var_value(var, data);
	if (!var_value)
		print_error_exit(MALLOC_ERROR, data);
	*current_str = ft_strcat(*current_str, var_value);
	free(var_value);
}

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
char	*get_var_value(char *var_name, t_data *data)
{
	int		i;
	int		found;
	char	*var_equal;

	found = 0;
	i = 0;
	var_equal = ft_strcat(var_name, "=");
	if (!var_equal)
		print_error_exit(MALLOC_ERROR, data);
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], var_equal, ft_strlen(var_equal)))
		{
			found = 1;
			break ;
		}
		i++;
	}
	free(var_equal);
	if (found)
		return (ft_strdup(ft_strchr(data->env[i], '=') + 1));
	else
		return (ft_strdup(""));
}

/**
 *	Function Name: add_new_var
 *
 *	Description:
 *
 *		This function calculates the length of the environment variable and
 *		calls the ft_strcut function to make a copy of it and add it to the
 *		char** into the t_data struct of variables to be expanded.
 *		It only accepts alphanumeric characters as part of the environment
 *		variable.
 *
 *	Parameters:
 *
 *		int *i			- The pointer to the index of the string where the
 *							environment variable starts.
 *		char *str		- The string that contains the unexpanded variables.
 *		t_data *data	- The pointer to the t_data struct with all
 *							the execution data.
 */
void	add_new_var(int *i, char *str, t_data *data)
{
	int		len;
	char	*aux;

	len = 1;
	(*i)++;
	while (ft_isalnum(str[*i]))
	{
		len++;
		(*i)++;
	}
	aux = ft_strcut(&(str[(*i) - len]), len);
	data->expand_vars = add_to_array(&data->expand_vars, aux);
	free(aux);
	(*i)--;
}
