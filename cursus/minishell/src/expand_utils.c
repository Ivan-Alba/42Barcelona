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
 *		This function concatenates the content of a string and the value of an
 *		environment variable. It overwrites the original variable.
 *		IMPORTANT! Its previous memory allocation must be freed from where the
 *		call occurs with an auxiliary variable.
 *
 *	Parameters:
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
 *		This function searches the value of a variable in the environment
 *		variables stored in the t_data struct and returns it.
 *
 *	Parameters:
 *		char *var_name - The name of the variable to search for.
 *		t_data *data   - The pointer to the t_data struct with all execution data.
 *
 *	Return Value:
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
 *	Function Name: get_var_value
 *
 *	Description:
 *		This function receives a string that can contain from 0 to n environment
 *		variables to expand, in $NAME format. It counts them and return the
 *		number of these variables.
 *
 *	Parameters:
 *		char *str	- The string to search for how many variables there are.
 *
 *	Return Value:
 *		int count	- Returns the count of environment variables.
 */
/*int	count_env_var(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0'
			&& str[i + 1] != '\'')
			count++;
		if (str[i] == '$' && str[i + 1] == '$')
			i++;
	}
	return (count);
}*/

/**
 *	Function Name: expand_marks
 *
 *	Description:
 *		This function searches in the string received by parameter for environment
 *		variables in $NAME format and creates a new string in which it adds the
 *		character \ as a flag in front of each one of them.
 *		This will be used to perform the variable expansion in the 
 *		@ref expand_section function in expand_section.c file.
 *
 *	Parameters:
 *		char *str	- The string to search for environment variables to be marked.
 *
 *	Return Value:
 *		char* 	- Returns a new string with the marks before each variable found.
 *
 *	Example:
 *		char *str = "I'm the user $USER in $PWD directory".
 *		Returns: 	"I'm the user \$USER in \$PWD directory".
 */
/*char	*expand_marks(char *str)
{
	int		i;
	int		j;
	char	*flag_str;

	if (count_env_var(str) > 0)
	{
		flag_str = malloc(sizeof(char *)
				* (count_env_var(str) + ft_strlen(str) + 1));
		if (!flag_str)
			return (NULL);
		i = -1;
		j = -1;
		while (str[++i])
		{
			if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0'
				&& str[i + 1] != '\'')
				flag_str[++j] = '\\';
			if (str[i] == '$' && str[i + 1] == '$')
				flag_str[++j] = str[i++];
			flag_str[++j] = str[i];
		}
		flag_str[++j] = '\0';
		return (flag_str);
	}
	return (ft_strdup(str));
}*/
