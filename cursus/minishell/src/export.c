/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinatacconis <carolinatacconis@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:57:39 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/10 23:07:40 by carolinat        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	"export" without options:
*
*	export [no options] VARIABLE_NAME
*	
*/
#include "../inc/minishell.h"

int	check_if_exist(char *var, t_data *data)
{
	int		i;
	int		var_len;
	int		env_key_len;
	char	*equal_pos_var;
	char	*equal_pos_env;

	i = 0;
	equal_pos_var = ft_strchr(var, '=');
	if (equal_pos_var)
		var_len = equal_pos_var - var;
	else
		var_len = ft_strlen(var);
	while (data->env && data->env[i])
	{
		equal_pos_env = ft_strchr(data->env[i], '=');
		if (equal_pos_env)
			env_key_len = ft_strchr(data->env[i], '=') - data->env[i];
		else
			env_key_len = ft_strlen(data->env[i]);
		if (var_len == env_key_len && ft_strncmp(data->env[i], var, env_key_len)
			== 0)
			return (i);
		i++;
	}
	return (-1);
}

void	check_cmd(char **cmd, int *i, int *exit_status)
{
	if (*cmd[1] == '\0')
	{
		printf("%s: export: `': not a valid identifier\n", PROGRAM_NAME);
		*exit_status = EXIT_FAILURE;
		(*i)++;
	}
	else if (is_flag(cmd[1]))
	{
		printf("%s export: %c%c: invalid option\n", PROGRAM_NAME,
			cmd[1][0], cmd[1][1]);
		printf("export: usage: export [no options admitted]");
		printf(" [name[=value] ...]\n");
		*exit_status = 2;
		(*i)++;
	}
}

void	export_actions(char **cmd, int i, int *exit_status, t_data *data)
{
	int	operator_type;
	int	var_in_env;

	operator_type = valid_varname(cmd[i]);
	if (operator_type)
	{
		if (operator_type == 2)
			remove_plus(cmd[i]);
		var_in_env = check_if_exist(cmd[i], data);
		if (operator_type == 1 || operator_type == 3)
			export_var(data, cmd[i], var_in_env, operator_type);
		else if (operator_type == 2)
			prepare_join(data, cmd[i], var_in_env);
	}
	else
	{
		if (cmd[i][0])
		{
			printf("%s export: ", PROGRAM_NAME);
			printf("`%s': not a valid identifier\n", cmd[i]);
			*exit_status = EXIT_FAILURE;
		}
	}
}

int	ft_export(char **cmd, t_data *data)
{
	int	i;
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (!cmd[1])
		return (print_export_vars(data), exit_status);
	i = 0;
	check_cmd(cmd, &i, &exit_status);
	if (exit_status == 2)
		return (exit_status);
	while (cmd && cmd[++i])
		export_actions(cmd, i, &exit_status, data);
	return (exit_status);
}
