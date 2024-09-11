/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinatacconis <carolinatacconis@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:58:50 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/10 17:40:49 by carolinat        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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
