/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinatacconis <carolinatacconis@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:57:39 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/10 23:07:40 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 *		Function Name: check_if_exist
 *
 *		Description:
 *
 *			This function receives the variable to be exported and checks
 *			if it already exists in the data->env list. 
 *
 *		Parameters:
 *
 *			char 	 *var -	The string to check.
 *			t_data	*data - The pointer to the t_data struct with all
 *							execution data.
 *		Return Value:
 *
 *			int - Returns -1 if no matches are found. otherwise it returns
 *				  the position in the array in which it is found.		
 */
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

/*
 *		Function Name: check_cmd
 *
 *		Description:
 *
 *			Checks if the command received as argument is an empty string or
 *			if it is a flag, to print the corresponding error messages.
 *
 *		Parameters:
 *
 *			char	**cmd -	The command and its arguments or flags.
 *			int   	*i    - The pointer to to the index that iterates the
 *							received arguments.	
 */
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

/*
 *		Function Name: export_actions
 *
 *		Description:
 *
 *			It checks whether the built-in has any operators in its arguments,
 *			and if so, prepares to concatenate or substitute the value. 
 *			If not, an error message is printed.
 *
 *		Parameters:
 *
 *			char	**cmd -	The command and its arguments.
 *			int   	 i    - The index that iterates the array of arguments.	
 *			int *exit_status - The pointer to exit_status value.
 *			t_data	*data - The pointer to the t_data struct with all
 *							execution data.
 */
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

/*
 *		Function Name: ft_export
 *
 *		Description:
 *
 *			It checks whether the built-in has any operators in its arguments,
 *			and if so, prepares to concatenate or substitute the value. 
 *			If not, an error message is printed.
 *
 *		Parameters:
 *
 *			char	**cmd -	The command and its arguments.
 *			t_data	*data - The pointer to the t_data struct with all
 *							execution data.
 *		Return Value:
 *
 *			int - Returns the value of the exit_status, which will depend on
 *				  each case. In case of success, the value is 0.
 */
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
