/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:24:42 by igarcia2          #+#    #+#             */
/*   Updated: 2024/05/23 15:54:45 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Function that manages the reading of data when using a limiter
void	read_heredoc(t_pipex *data)
{
	char	*line;

	dup2(data->pipes[1], STDOUT_FILENO);
	line = get_next_line(0);
	while (line && ft_strncmp(data->limiter, line,
			ft_strlen(data->limiter) + 1) != 0)
	{
		write(1, line, ft_strlen(line));
		free(line);
		line = NULL;
		line = get_next_line(0);
	}
	if (line)
		free(line);
	close(STDOUT_FILENO);
}

//Checks if the input file exists and we have access to it
void	set_infile(char **argv, t_pipex *data)
{
	if (!data->is_heredoc)
	{
		if (access(data->in_file, F_OK) == -1
			|| access(data->in_file, R_OK) == -1)
		{
			if (data->in_file)
			{
				free(data->in_file);
				data->in_file = NULL;
			}
			perror(argv[1]);
		}
	}
}

////Checks if the output file exists and we have access to it
void	set_outfile(int argc, char **argv, t_pipex *data)
{
	if (access(argv[argc - 1], F_OK) == 0 && access(argv[argc - 1], W_OK) == -1)
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
		if (!data->is_heredoc)
		{
			if (open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666) == -1)
				perror("File error");
		}
		else
			if (open(argv[argc - 1], O_WRONLY | O_CREAT, 0666) == -1)
				perror("File error");
	}
}

//Calls the necessary functions depending on whether it is here_doc or not
void	pipex(t_pipex *data, int argc, char **argv, char **env)
{
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		data->is_heredoc = 1;
		data->limiter = ft_strjoin(argv[2], "\n");
		init_data(data, argc, argv, env);
		read_heredoc(data);
	}
	else
	{
		data->is_heredoc = 0;
		init_data(data, argc, argv, env);
	}
	set_infile(argv, data);
	set_outfile(argc, argv, data);
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
	pipex(data, argc, argv, env);
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
	free_data(data, NULL);
	while (i--)
		wait(NULL);
	return (0);
}
