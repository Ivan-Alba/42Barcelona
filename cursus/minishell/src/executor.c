/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:24 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/21 19:22:06 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Create the necessary pipes for communication between processes
void	generate_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipes_needed)
	{
		if (pipe(data->pipes + 2 * i) == -1)
			print_error_exit(PIPES_ERROR, data);
		i++;
	}
}

//Function that manages the reading of data when using a limiter
void	read_heredoc(t_data *data)
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

//manages the opening of fd's, creation of processes and execution of commands
void	executor(t_data *data)
{
	//TODO GENERATE PIPES
	data->pipes = malloc(data->pipes_needed * 2 * sizeof(int));
	if (!data->pipes)
		print_error_exit(MALLOC_ERROR, data);
	generate_pipes(data);
	//TODO HEREDOCS

	//TODO OPEN FDS (NOT && or ||)

	//TODO EXECUTE FORK RECURSIVE INNER->NEXT 
}
