/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:58:50 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/18 19:19:22 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 *		Function Name: ft_strcmp
 *
 *		Description:
 *
 *			This function compares the two strings s1 and s2.
 *
 *		Parameters:
 *
 *			const char *s1 - The string to compare.
 *			const char *s2 - The string to compare.
 * 
 *		Return Value:
 *
 *			int - Returns 0 if s1 and s1 are equal, a negative value if s1 is
 *				  less than s2 and a positive value if s1 is greater than s2.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
 *		Function Name: ft_sort_list
 *
 *		Description:
 *
 *			This function receives a char** with a the list of environment
 *			varibles and sort the list in alphabetical order.
 *
 *		Parameters:
 *
 *			char	**list_vars - The array of strings to sort.
 */
void	ft_sort_list(char **list_vars)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	while (list_vars[i])
	{
		j = i + 1;
		while (list_vars[j])
		{
			if (ft_strcmp(list_vars[i], list_vars[j]) > 0)
			{
				aux = list_vars[j];
				list_vars[j] = list_vars[i];
				list_vars[i] = aux;
			}
			j++;
		}
		i++;
	}
}

/*
 *		Function Name: dup_sort_list
 *
 *		Description:
 *
 *			This function duplicates the list to be sorted.
 *
 *		Parameters:
 *
 *			char	**list_vars - The array of strings to sort.
 *			t_data	*data - The pointer to the t_data struct with env.
 *			int *num_vars - A pointer to the total value of number
 *							of environment variables.
 */
void	dup_sort_list(char **list_vars, t_data *data, int *num_vars)
{
	int	i;

	i = 0;
	while (i < *num_vars)
	{
		list_vars[i] = ft_strdup(data->env[i]);
		if (!list_vars[i])
		{
			free_split(&list_vars);
			print_error_exit(MALLOC_ERROR, data);
		}
		i++;
	}
	list_vars[i] = NULL;
	ft_sort_list(list_vars);
}

/*
 *		Function Name: export_var
 *
 *		Description:
 *
 *			This function:
 *			- If the variable already exists and there is no operator,
 *			it returns.
 *			- If the variable already exists and there is an operator of type 3,
 *			 substitute the VALUE.
 *			- If not, create the new environment variable and add it to the list.
 *
 *		Parameters:
 *
 *			t_data	*data - The pointer to the t_data struct with env.
 *			char	*new_var - The possibly new variable to add.
 *			int		var_in_env -The position in the env array of the variable
 *								if it already exists.
 *			int		operator_type - If it is 1 means that there is none and
 *									number 3 is "=".
 */
void	export_var(t_data *data, char *new_var, int var_in_env, int oper_type)
{
	char	*updated_var;

	updated_var = NULL;
	if (var_in_env >= 0 && oper_type == 1)
		return ;
	else if (var_in_env >= 0 && oper_type == 3)
	{
		updated_var = ft_strdup(new_var);
		malloc_protection(updated_var, data);
		free (data->env[var_in_env]);
		data->env[var_in_env] = NULL;
		data->env[var_in_env] = updated_var;
	}
	else
	{
		data->env = add_to_array(&data->env, new_var);
		malloc_protection(data->env, data);
	}
}

/*
 *		Function Name: valid_varname
 *
 *		Description:
 *
 *			This function receives a string to verify if it has
 *			a valid variable name to export.
 *
 *		Parameters:
 *
 *			char *str -	The string to check.
 *
 *		Return Value:
 *
 *			int - Returns 0 if the name of the variable is not valid,
 *				  1 if there is no operator, 2 if the operator is "+=" and
 *			      3 if the operator is "=".
 */
int	valid_varname(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] == '_' || ft_isalpha(str[0]))
	{
		i = 1;
		while (ft_isalpha(str[i]) || ft_isalnum(str[i]) || str[i] == '_')
			i++;
	}
	else
		return (0);
	if (str[i] == '\0')
		return (1);
	if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
		return (2);
	if (str[i] == '=')
		return (3);
	return (0);
}
