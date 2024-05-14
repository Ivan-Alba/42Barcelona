/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:00:27 by igarcia2          #+#    #+#             */
/*   Updated: 2024/05/14 21:00:44 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Function that sets the default input channel
void	set_stdin(t_pipex *data, int i)
{
	int	fd;

	if (data->cmds[i].first)
	{
		if (data->in_file)
		{
			fd = open(data->in_file, O_RDONLY);
			if (dup2(fd, STDIN_FILENO) == -1)
				perror("");
			close(fd);
		}
		else
			exit(1);
	}
	else
		if (dup2(data->pipes[(i + data->is_heredoc) * 2 - 2],
				STDIN_FILENO) == -1)
			perror("");
}

//Function that sets the default output channel
void	set_stdout(t_pipex *data, int i)
{
	int	fd;

	if (data->cmds[i].last)
	{
		if (data->out_file)
		{
			fd = open(data->out_file, O_WRONLY);
			if (dup2(fd, STDOUT_FILENO) == -1)
				perror("");
			close(fd);
		}
		else
			exit(1);
	}
	else
		if (dup2(data->pipes[(i + data->is_heredoc) * 2 + 1],
				STDOUT_FILENO) == -1)
			perror("");
}

//Manages the incoming and outgoing fd's and executes the command
void	execute(t_pipex *data, int i)
{
	set_stdin(data, i);
	set_stdout(data, i);
	free_close_pipes(data);
	if (execve(data->cmds[i].path, data->cmds[i].cmd_flags, data->env) == -1)
	{
		write(2, data->cmds[i].cmd_flags[0],
			ft_strlen(data->cmds[i].cmd_flags[0]));
		perror(": command not found");
		exit(1);
	}
}
