/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:24 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/09 14:06:28 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Create the necessary pipes for communication between processes
void	generate_pipes(t_data *data)
{
	int	i;

	if (data->section_id - 1 > 0)
	{
		data->pipes = malloc((data->section_id - 1) * 2 * sizeof(int));
		if (!data->pipes)
			print_error_exit(MALLOC_ERROR, data);
	}
	i = 0;
	while (i < data->section_id -1)
	{
		if (pipe(data->pipes + 2 * i) == -1)
			print_error_exit(PIPES_ERROR, data);
		i++;
	}
}

int	setup_curr_section(t_section **curr_sec, t_data *data)
{
	expand_section(*curr_sec, data);
	manage_wildcard(*curr_sec, data);
	if (open_fds(*curr_sec) == 0)
	{
		if ((*curr_sec)->cmd && (*curr_sec)->cmd[0])
		{
			set_stdin_stdout(*curr_sec, data);
			if (check_if_builtin((*curr_sec)->cmd[0]))
				builtin_setup(curr_sec, (*curr_sec)->cmd, data);
			else
				create_process(curr_sec, data, 0);
			dup2(data->std_in, STDIN_FILENO);
			dup2(data->std_out, STDOUT_FILENO);
			data->wait_process++;
		}
	}
	else
	{
		data->last_exit_status = 1;
		return (1);
	}
	return (0);
}

int	is_next_and_or(t_section *curr_sec, t_data *data)
{
	if (curr_sec->next)
	{
		if (curr_sec->next_conn == AND && data->last_exit_status == 0)
		{
			data->accept_inner = 1;
			return (1);
		}
		else if (curr_sec->next_conn == OR && data->last_exit_status > 0)
		{
			data->accept_inner = 1;
			return (1);
		}
	}
	return (0);
}

void	execute_sections(t_section *curr_sec, t_data *data)
{
	generate_pipes(data);
	while (curr_sec)
	{
		if (setup_curr_section(&curr_sec, data) == 0)
		{
			if (curr_sec->inner && ((curr_sec->in_conn != AND
						&& curr_sec->out_conn != OR) || data->accept_inner))
			{
				if (create_process(&curr_sec, data, 1))
					continue ;
				data->wait_process++;
			}
		}
		if (get_next_pipe_section(curr_sec))
			curr_sec = get_next_pipe_section(curr_sec);
		else
			break ;
	}
	wait_for_process_ending(curr_sec, data);
	if (is_next_and_or(curr_sec, data))
		execute_sections(curr_sec->next, data);
	if (data->is_child)
		exit(data->last_exit_status);
	signal(SIGINT, handle_signal_prompt);
}

//Manages the opening of fd's, creation of processes and execution of commands
void	execute_controller(t_data *data)
{
	if (manage_heredocs(data))
		return ;
	data->pids = malloc(sizeof(int) * data->section_id);
	if (!data->pids)
		print_error_exit(MALLOC_ERROR, data);
	execute_sections(data->sections, data);
}
