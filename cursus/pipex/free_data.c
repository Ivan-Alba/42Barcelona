/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:04:16 by igarcia2          #+#    #+#             */
/*   Updated: 2024/05/15 20:04:19 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Writes an error message and ends the program
void	error_exit(char *error)
{
	write(2, error, ft_strlen(error));
	exit(1);
}

//Free the memory of a char*
void	free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

//Free the memory of a char**
void	free_split(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
	}
	free(str);
	str = NULL;
}

//Free and closes all pipes
void	free_close_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	if (data->pipes)
	{
		while (i < data->cmd_num + data->is_heredoc)
		{
			close(data->pipes[i * 2]);
			close(data->pipes[i * 2 + 1]);
			i++;
		}
		free(data->pipes);
		data->pipes = NULL;
	}
}

//Function that manages all the data release of the structures
void	free_data(t_pipex *data, char *error)
{
	int	i;

	if (data)
	{
		i = -1;
		free_str(data->in_file);
		free_str(data->out_file);
		free_str(data->limiter);
		free_split(data->path);
		if (data->cmds)
		{
			while (++i < data->cmd_num)
			{
				free_split(data->cmds[i].cmd_flags);
				free_str(data->cmds[i].path);
			}
			free(data->cmds);
			data->cmds = NULL;
		}
		free_close_pipes(data);
		free(data);
		data = NULL;
	}
	if (error)
		error_exit(error);
}
