/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_join_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:58:50 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/18 18:33:11 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 *		Function Name: remove_plus
 *
 *		Description:
 *
 *			This function receives a string and removes the "+" from
 *			the "+=" operator.
 *
 *		Parameters:
 *
 *			char *str -	The string to edit.
 */
void	remove_plus(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] && str[i] != '+')
		i++;
	while (str[i] && str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
}

/*
 *		Function Name: join_values
 *
 *		Description:
 *
 *			This function concatenates an exported value to an existing 
 *			environment variable.
 *
 *		Parameters:
 *
 *			t_data	*data - The pointer to the t_data struct with all
 *							execution data.
 *			char	*join_var - The KEY=VALUE with the value to join.
 *			int		var_in_env - The position in the array of env, where
 *								 the existing variable to concatenate the
 *								 VALUE to is located.
 */
void	join_values(t_data *data, char *join_var, int var_in_env)
{
	char	*value_to_add;
	char	*value_joined;

	value_to_add = NULL;
	value_joined = NULL;
	if (ft_strchr(join_var, '=') + 1)
	{
		value_to_add = ft_substr(ft_strchr(join_var, '='), 1,
				ft_strlen(ft_strchr(join_var, '=') - 1));
		malloc_protection(value_to_add, data);
		if (!ft_strchr(data->env[var_in_env], '='))
		{
			value_to_add = ft_free_strcat(ft_strdup("="), value_to_add);
			malloc_protection(value_to_add, data);
		}
		value_joined = ft_strjoin(data->env[var_in_env], value_to_add);
		malloc_protection(value_joined, data);
		free(value_to_add);
		value_to_add = NULL;
		free(data->env[var_in_env]);
		data->env[var_in_env] = NULL;
		data->env[var_in_env] = value_joined;
	}
}

/*
 *		Function Name: prepare_join
 *
 *		Description:
 *
 *			In this function, if the KEY to be exported already exists,
 *			join_values is called, otherwise it is created and added.
 *
 *		Parameters:
 *
 *			t_data	*data - The pointer to the t_data struct with all
 *							execution data.
 *			char	*join_var - The KEY=VALUE with the value to join.
 *			int		var_in_env - The position in the array of env, where
 *								 the existing variable to concatenate the
 *								 VALUE to is located.
 */
void	prepare_join(t_data *data, char *join_var, int var_in_env)
{
	if (var_in_env >= 0)
		join_values(data, join_var, var_in_env);
	else
	{
		data->env = add_to_array(&data->env, join_var);
		malloc_protection(data->env, data);
	}
}
