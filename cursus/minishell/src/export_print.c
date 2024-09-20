/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:57:39 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/18 18:49:21 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 *		Function Name: print_quoted_vars
 *
 *		Description:
 *
 *			This function adds the double quotes to the VALUE of the KEY:
 *			KEY=‘VALUE’.
 *
 *		Parameters:
 *
 *			char *var -	The string to edit and print.
 */
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

/*
 *		Function Name: print_vars_noargs
 *
 *		Description:
 *
 *			This function prints in the export format the KEY=VALUE
 *			list of env.
 *
 *		Parameters:
 *
 *			char *list_vars - The array of strings to print.
 */
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

/*
 *		Function Name: print_export_vars
 *
 *		Description:
 *
 *			By allocating dynamic memory, a copy of the alphabetically
 *			ordered list of environment variables is created and printed.
 *
 *		Parameters:
 *
 *			t_data	*data - The pointer to the t_data struct with env.
 */
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
