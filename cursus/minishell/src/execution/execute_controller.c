/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_controller.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:24 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/26 17:24:37 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 *		Function Name:	generate_pipes
 *
 *		Description:
 *
 *			This function creates the necessary pipes for communication between
 *			processes and stores them in the t_data struct.
 *
 *		Parameters:
 *
 *			t_data	*data - The pointer to the t_data struct with all
 *							execution data.
 */
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

/**
 *		Function Name:	setup_curr_section
 *
 *		Description:
 *
 *			This function prepares the current section for execution. It calls
 *			the functions in charge of managing the expansion of environment
 *			variables, expansion of wildcards, opening of fd's, input and
 *			output fd's and the execution.
 *
 *		Parameters:
 *
 *			t_section	**curr_sec	- A double pointer to the current section
 *										to execute.
 *			t_data		*data		- The pointer to the t_data struct with all
 *										execution data.
 *
 *		Return Value:
 *
 *			int - Returns 0 if fd's opening was correct or 1 if not.
 */
int	setup_curr_section(t_section **curr_sec, t_data *data)
{
	expand_section(*curr_sec, data);
	manage_wildcard(*curr_sec, data);
	if (open_fds(*curr_sec) == 0)
	{
		if ((*curr_sec)->cmd && (*curr_sec)->cmd[0])
		{
			set_stdin_stdout(*curr_sec, data);
			if (is_builtin((*curr_sec)->cmd[0]))
				builtin_setup((*curr_sec), (*curr_sec)->cmd, data);
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

/**
 *		Function Name:	is_next_and_or
 *
 *		Description:
 *
 *			This function checks if section->next exists, if the connection
 *			to the next section is AND or OR and if the condition to execute
 *			this next section is met.
 *
 *		Parameters:
 *
 *			t_section	*curr_sec	- A pointer to the current section.
 *			t_data		*data		- The pointer to the t_data struct with all
 *										execution data.
 *
 *		Return Value:
 *
 *			int - Returns 0 if the conditions are not met and 1 if yes.
 */
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

/**
 *		Function Name:	execute_sections
 *
 *		Description:
 *
 *			This function goes through the sections and sends them to execute.
 *			It stops when it finds a section with AND or OR connection to the
 *			next one and waits for the result of the last section before
 *			checking if the conditions are met to continue or not.
 *
 *		Parameters:
 *
 *			t_section	*curr_sec	- A pointer to the current section.
 *			t_data		*data		- The pointer to the t_data struct with all
 *										execution data.
 *
 */
void	execute_sections(t_section *curr_sec, t_data *data)
{
	signal(SIGINT, SIG_IGN);
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

/**
 *		Function Name:	execute_controller
 *
 *		Description:
 *
 *			This function calls the function in charge of managing the creation
 *			of the heredocs (before the execution of the sections) and allocate
 *			the necessary memory to store the pids of the processes that will
 *			be executed.
 *
 *		Parameters:
 *
 *			t_data	*data - The pointer to the t_data struct with all
 *							execution data.
 *
 */
void	execute_controller(t_data *data)
{
	if (manage_heredocs(data))
		return ;
	data->pids = malloc(sizeof(int) * data->section_id);
	if (!data->pids)
		print_error_exit(MALLOC_ERROR, data);
	execute_sections(data->sections, data);
}
