/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:58:17 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/23 13:13:30 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 *		Function Name: is_builtin
 *
 *		Description:
 *
 *			This function receives a string with a command and checks if it
 *			belongs to one of the builtins.
 *
 *		Parameters:
 *
 *			char *command -	The string with the command to compare.
 *
 *		Return Value:
 *
 *			int - Returns 1 if the command is a builtin and 0 if it is not.
 */
int	is_builtin(char *command)
{
	if (ft_strncmp(command, ECHO, 5) == 0)
		return (1);
	else if (ft_strncmp(command, CD, 3) == 0)
		return (1);
	else if (ft_strncmp(command, PWD, 4) == 0)
		return (1);
	else if (ft_strncmp(command, EXPORT, 7) == 0)
		return (1);
	if (ft_strncmp(command, UNSET, 6) == 0)
		return (1);
	else if (ft_strncmp(command, ENV, 4) == 0)
		return (1);
	else if (ft_strncmp(command, EXIT, 5) == 0)
		return (1);
	return (0);
}

/**
 *		Function Name: execute_builtin
 *
 *		Description:
 *
 *			This function receives a char** with a command of type builtin and
 *			its arguments (if any). It will call the function in charge of
 *			executing the builtin.
 *
 *		Parameters:
 *
 *			char	**cmd -	The command and its arguments or flags.
 *			t_data	*data - The pointer to the t_data struct with all
 *							execution data.
 */
void	execute_builtin(char **cmd, t_data *data)
{
	if (ft_strncmp(cmd[0], ECHO, 5) == 0)
		data->last_exit_status = ft_echo(cmd);
	else if (ft_strncmp(cmd[0], CD, 3) == 0)
		data->last_exit_status = ft_cd(cmd, data);
	else if (ft_strncmp(cmd[0], PWD, 4) == 0)
		data->last_exit_status = ft_pwd(cmd, data);
	else if (ft_strncmp(cmd[0], EXPORT, 7) == 0)
		data->last_exit_status = ft_export(cmd, data);
	if (ft_strncmp(cmd[0], UNSET, 6) == 0)
		data->last_exit_status = ft_unset(cmd, data);
	else if (ft_strncmp(cmd[0], ENV, 4) == 0)
		data->last_exit_status = ft_env(cmd, data);
	else if (ft_strncmp(cmd[0], EXIT, 5) == 0)
	{
		data->last_exit_status = ft_exit(cmd, data);
		if (data->last_exit_status == 2)
		{
			free_data(data);
			exit(2);
		}
	}
}

/**
 *		Function Name: execute_builtin_process
 *
 *		Description:
 *
 *			This function creates a child process before calling the
 *			execute_builtin function.
 *
 *		Parameters:
 *
 *			t_section	*section - The pointer to the section to which the
 *									builtin to be executed belongs.
 *			char		**cmd    - The command and its arguments or flags.
 *			t_dat		*data	 - The pointer to the t_data struct with all
 *									execution data.
 */
void	execute_builtin_process(t_section *section, char **cmd, t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		data->is_child = 1;
		execute_builtin(cmd, data);
		exit(data->last_exit_status);
	}
	else if (pid == -1)
		print_error_exit(FORK_ERROR, data);
	else
		data->pids[section->id] = pid;
}

/**
 *		Function Name: builtin_setup
 *
 *		Description:
 *
 *			This function contains the logic to determine if a builtin must
 *			be executed in a child process or not.
 *
 *		Parameters:
 *
 *			t_section	*section - The pointer to the section to which the
 *									builtin to be executed belongs.
 *			char		**cmd    - The command and its arguments or flags.
 *			t_dat		*data	 - The pointer to the t_data struct with all
 *									execution data.
 */
void	builtin_setup(t_section *section, char **cmd, t_data *data)
{
	if ((!section->next || section->next_conn != PIPE)
		&& (!section->previous || section->previous->next_conn != PIPE))
		execute_builtin(cmd, data);
	else
		execute_builtin_process(section, cmd, data);
}
