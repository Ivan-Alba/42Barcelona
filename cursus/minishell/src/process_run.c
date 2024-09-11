/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:24 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/05 18:14:05 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_shell_lvl(char *cmd, t_data *data)
{
	char	**export_cmd;
	char	*shell_lvl;
	int		curr;

	if (ft_strrchr(cmd, '/')
		&& ft_strncmp(ft_strrchr(cmd, '/'), "/minishell", 11) == 0)
	{
		shell_lvl = ft_strdup("$SHLVL");
		malloc_protection(shell_lvl, data);
		shell_lvl = get_var_value(&shell_lvl, data, 0);
		if (!shell_lvl)
			return ;
		curr = ft_atoi(shell_lvl);
		free(shell_lvl);
		export_cmd = NULL;
		export_cmd = add_to_array(&export_cmd, "export");
		malloc_protection(export_cmd, data);
		shell_lvl = ft_free_strcat(ft_strdup("SHLVL="), ft_itoa(curr + 1));
		malloc_protection(shell_lvl, data);
		export_cmd = add_to_array(&export_cmd, shell_lvl);
		free(shell_lvl);
		malloc_protection(export_cmd, data);
		ft_export(export_cmd, data);
		free(export_cmd);
	}
}

//Manages the incoming and outgoing fd's and executes the command
void	execute(t_section *section, t_data *data)
{
	free_close_pipes(data);
	get_path(data);
	if (section->cmd && (section->cmd)[0] && ((section->cmd)[0][0] == '/'
		|| (section->cmd)[0][0] == '.'))
		section->cmd_path = ft_strdup((section->cmd)[0]);
	else
		section->cmd_path = get_cmd_path((section->cmd)[0], data);
	if ((section->cmd)[0] && ((section->cmd)[0][0] == '/'
		|| (section->cmd)[0][0] == '.')
		&& access(section->cmd_path, X_OK) == -1)
	{
		perror((section->cmd)[0]);
		exit(127);
	}
	check_shell_lvl(section->cmd[0], data);
	if (execve(section->cmd_path, section->cmd, data->env) == -1)
	{
		if ((section->cmd)[0] && (section->cmd)[0][0])
			write(2, (section->cmd)[0], ft_strlen((section->cmd)[0]));
		else if ((section->cmd)[0])
			write(2, "''", 2);
		write(2, ": command not found\n", 20);
		exit(127);
	}
}

int	create_process(t_section **section, t_data *data, int is_subshell)
{
	int	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		data->is_child = 1;
		if (is_subshell)
		{
			data->wait_process = 0;
			*section = (*section)->inner;
			return (1);
		}
		else
		{
			signal(SIGINT, handle_signal);
			execute(*section, data);
		}
	}
	else if (pid == -1)
		print_error_exit(FORK_ERROR, data);
	else
		data->pids[(*section)->id] = pid;
	return (0);
}

void	wait_for_process_ending(t_section *last_section, t_data *data)
{
	int	last_section_executed;
	int	status;

	data->accept_inner = 0;
	free_close_pipes(data);
	last_section_executed = last_section->id;
	while (data->wait_process--)
	{
		if (wait(&status) == data->pids[last_section_executed])
		{
			if (WIFEXITED(status))
				data->last_exit_status = WEXITSTATUS(status);
			else
				data->last_exit_status = 130;
		}
	}
	data->wait_process = 0;
}
