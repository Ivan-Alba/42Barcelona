/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinatacconis <carolinatacconis@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:57:39 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/10 23:07:40 by carolinat        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*       "export" without options:
*
*       export [no options] VARIABLE_NAME
*
*/
#include "../inc/minishell.h"

//add "" to the VALUE of the KEY: KEY="VALUE"
static void	print_quoted_vars(char *var)
{
	int		i;

	i = 0;
	while (var[i] && var[i] != '=')
		write(1, &var[i++], 1);
	if (!var[i])
	{
		write(1, "\n", 1);
		return ;
	}
	if (!var[i + 1])
	{
		write(1, "=\"\"\n", 4);
		return ;
	}
	write(1, "=\"", 2);
	i++;
	while (var[i])
	{
		write(1, &var[i], 1);
		i++;
	}
	write(1, "\"\n", 2);
}

//prints in the export format the KEY=VALUE list
static void	print_vars_noargs(char **list_vars)
{
	int		i;

	i = 0;
	while (list_vars && list_vars[i])
	{
		if (!(list_vars[i][0] == '_' && list_vars[i][1] == '='))
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			print_quoted_vars(list_vars[i]);
		}
		i++;
	}
}

int	print_export_vars(t_data *data)
{
	char	**list_vars;
	int		num_vars;

	num_vars = 0;
	while (data->env && data->env[num_vars])
		num_vars++;
	list_vars = ft_calloc(sizeof(char *), num_vars + 1);
	malloc_protection(list_vars, data);
	dup_sort_list(list_vars, data, &num_vars);
	print_vars_noargs(list_vars);
	free_split(&list_vars);
	return (0);
}
