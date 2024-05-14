/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:24:25 by igarcia2          #+#    #+#             */
/*   Updated: 2024/05/14 20:39:32 by igarcia2         ###   ########.fr       */
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
