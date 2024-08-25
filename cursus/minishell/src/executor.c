/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:24 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/23 19:58:46 by igarcia2         ###   ########.fr       */
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

void	set_stdin_stdout(t_section *section, t_data *data)
{
	//TODO DUP/DUP2
	data->std_in = dup(STDIN_FILENO);
	data->std_out = dup(STDOUT_FILENO);
	if (section->previous && section->previous->next_conn == PIPE)
		dup2(data->pipes[(section->id - 1) * 2], STDIN_FILENO);
	else if (section->fd_in != -1)
		dup2(section->fd_in, STDIN_FILENO);
	if (section->previous)
		close(data->pipes[(section->id - 1) * 2]);
	if (section->next && section->next_conn == PIPE)
		dup2(data->pipes[((section->id) * 2) + 1], STDOUT_FILENO);
	else if (section->fd_out != -1)
		dup2(section->fd_out, STDOUT_FILENO);
	if (section->next)
		close(data->pipes[((section->id) * 2) + 1]);
	close_section_fds(section);
}

//Manages the incoming and outgoing fd's and executes the command
void	execute(t_section *section, t_data *data)
{
	free_close_pipes(data);
	get_path(data);
	if (section->cmd && (section->cmd)[0] && (section->cmd)[0][0] == '/')
		section->cmd_path = ft_strdup((section->cmd)[0]);
	else
		section->cmd_path = get_cmd_path((section->cmd)[0], data);
	if ((section->cmd)[0] && (section->cmd)[0][0] == '/'
		&& access(section->cmd_path, X_OK) == -1)
	{
		perror((section->cmd)[0]);
		exit(127);
	}
	if (execve(section->cmd_path, section->cmd, data->env) == -1)
	{
		if ((section->cmd)[0])
			write(2, (section->cmd)[0], ft_strlen((section->cmd)[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
}

int	create_process(t_section **section, t_data *data, int is_inner)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (is_inner)
		{
			*section = (*section)->inner;
			return (1);
		}
		else
			execute(*section, data);
	}
	else if (pid == -1)
		print_error_exit(FORK_ERROR, data);
	else
	{
		data->pids[(*section)->id] = pid;
		dup2(data->std_in, STDIN_FILENO);
		dup2(data->std_out, STDOUT_FILENO);
	}
	return (0);
}

int	setup_process(t_section *curr_sec, t_data *data)
{
	int wait_process;
	
	wait_process = 0;
	//TODO EXECUTE ALL SECTIONS ONLY CONNECTED BY PIPE
	while (curr_sec)
	{
		if (curr_sec->cmd)
		{
		//TODO PRINT TEST
		printf("\n##### SECTION %d EXPANSION #####\n", curr_sec->id);
		expand_section(curr_sec, data);
		//TODO SET FD_IN Y FD_OUT DE CADA SECCION (NOT && or ||)
		if (open_fds(curr_sec) == 0)
		{
			set_stdin_stdout(curr_sec, data);
			//TODO FORK EXECVE
			create_process(&curr_sec, data, 0);
			wait_process++;
			printf("execve section %d\n", curr_sec->id);
		}
		else
			data->last_exit_status = 1;
		}
		if (curr_sec->inner && curr_sec->in_conn != AND && curr_sec->out_conn != OR)
		{
			//TODO PRINT TEST
			printf("\n##### SECTION %d EXPANSION #####\n", curr_sec->inner->id);
			expand_section(curr_sec->inner, data);
			//TODO SET FD_IN Y FD_OUT DE CADA SECCION (NOT && or ||)
			if (open_fds(curr_sec->inner) == 0)
			{
				set_stdin_stdout(curr_sec->inner, data);
				//TODO FORK (SETUP_PROCESS)
				if (create_process(&curr_sec, data, 1))
				{
					wait_process = 0;
					continue ;
				}
				wait_process++;
				printf("execute section %d\n", curr_sec->id);
			}
			else
				data->last_exit_status = 1;
		}
		if (get_next_pipe_section(curr_sec))
			curr_sec = get_next_pipe_section(curr_sec);
		else
			break;
	}
	int last_section_executed;
	last_section_executed = curr_sec->id;
	printf("last section executed %d\n", last_section_executed);
	int	status;
	printf("processes waiting: %d\n", wait_process);
	while (wait_process--)
	{
		if (wait(&status) == data->pids[last_section_executed])
		{
		printf("entro aqui\n");
			// Verificar si el proceso terminó normalmente
        	if (WIFEXITED(status)) 
			{
				printf("exit status: %d", WEXITSTATUS(status));
				data->last_exit_status = WEXITSTATUS(status);
			}
			else
				data->last_exit_status = 666;
		}
	}
	return (1);
}

//Manages the opening of fd's, creation of processes and execution of commands
void	executor(t_data *data)
{
	generate_pipes(data);
	manage_heredocs(data);
	data->pids = malloc(sizeof(int) * data->section_id);
	if (!data->pids)
		print_error_exit(MALLOC_ERROR, data);
	while (1)
	{
		if (setup_process(data->sections, data))
			break;
	}
}
