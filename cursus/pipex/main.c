/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:24:42 by igarcia2          #+#    #+#             */
/*   Updated: 2024/05/13 18:52:06 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Checks the arguments and permissions of input and output files
void	check_args(int argc, char **argv, t_pipex *data)
{
	if (access(data->in_file, F_OK) == -1 || access(data->in_file, R_OK) == -1)
	{
		if (data->in_file)
		{
			free(data->in_file);
			data->in_file = NULL;
		}
		perror(argv[1]);
	}
	if (access(argv[argc - 1], F_OK) == 0 && access(argv[argc -1], W_OK) == -1)
	{
		if (data->out_file)
		{
			free(data->out_file);
			data->out_file = NULL;
		}
		perror(argv[argc - 1]);
	}
	else
	{
		if (open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666) == -1)
			perror("open");
	}
}

//Manages the incoming and outgoing fd's and executes the command
void	execute(t_pipex *data, int i)
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
		if (dup2(data->pipes[i * 2 - 2], STDIN_FILENO) == -1)
			perror("");
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
		if (dup2(data->pipes[i * 2 + 1], STDOUT_FILENO) == -1)
			perror("");
	free_close_pipes(data);
	if (execve(data->cmds[i].path, data->cmds[i].cmd_flags, data->env) == -1)
	{
		perror("execve");
		exit(1);
	}
}

//Main function
int	main(int argc, char **argv, char **env)
{
	int		i;
	int		pid;
	t_pipex	*data;

	if (argc < 5)
		error_exit("ARGS ERROR\n");
	data = malloc(sizeof(t_pipex));
	if (!data)
		free_data(data, "Malloc error\n");
	init_data(data, argc, argv, env);
	check_args(argc, argv, data);
	i = 0;
	while (i < data->cmd_num)
	{
		pid = fork();
		if (pid == 0)
			execute(data, i);
		else if (pid == -1)
			free_data(data, "Fork error\n");
		i++;
	}
	free_close_pipes(data);
	/*while (i--)
		wait(NULL);
	*/
	free_data(data, NULL);
	return (0);
}
