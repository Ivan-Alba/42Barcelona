/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:55:08 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/22 19:16:03 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//(TEST) Prints the content of a pipe
void	print_pipe(int fd)
{
	int		bytes_read;
	char	buffer[1024];

	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read >= 0)
	{
		buffer[bytes_read] = '\0';
		write(STDOUT_FILENO, buffer, bytes_read);
	}
}

//Deletes the contents of a pipe, closes it and reopens it again
void	reset_pipe(t_data *data, t_files *file)
{
	int		bytes_read;
	char	buffer[1024];

	close(data->pipes[file->pipe * 2 + 1]);
	bytes_read = read(data->pipes[file->pipe * 2], buffer, sizeof(buffer));
	while (bytes_read > 0)
		bytes_read = read(data->pipes[file->pipe * 2], buffer, sizeof(buffer));
	close(data->pipes[file->pipe * 2]);
	pipe(data->pipes + (2 * file->pipe));
}

//Function that manages the reading of data when using a limiter
void	read_heredoc(t_data *data, t_files *file)
{
	char	*line;
	int		std_out_fd;

	reset_pipe(data, file);
	std_out_fd = dup(STDOUT_FILENO);
	dup2(data->pipes[(file->pipe * 2) + 1], STDOUT_FILENO);
	line = get_next_line(0);
	while (line && ft_strncmp(file->str, line,
			ft_strlen(file->str)) != 0)
	{
		write(1, line, ft_strlen(line));
		free(line);
		line = NULL;
		line = get_next_line(0);
	}
	//TODO Test print
	write(2, "cierro heredoc\n", 15);
	if (line)
		free(line);
	close(STDOUT_FILENO);
	dup2(std_out_fd, STDOUT_FILENO);
}

//Receives a node from a list t_section and returns the following node
t_section	*get_next_section(t_section	*current, int last_section_id)
{
	if (current->inner)
		return (current->inner);
	else if (current->next)
		return (current->next);
	else if (current->id == last_section_id)
		return (NULL);
	while (1)
	{
		if (current->next)
			return (current->next);
		while (current->previous)
			current = current->previous;
		if (current->outer)
			current = current->outer;
	}
}

//Go through the sections and manage the opening of the heredocs
void	manage_heredocs(t_data *data)
{
	t_section	*current_sec;
	t_files		*current_file;

	current_sec = data->sections;
	while (current_sec)
	{
		printf("Section: %d\n", current_sec->id);
		current_file = current_sec->files;
		while (current_file)
		{
			if (current_file->file_type == HEREDOC)
				read_heredoc(data, current_file);
			current_file = current_file->next;
		}
		current_file = NULL;
		current_sec = get_next_section(current_sec, data->section_id - 1);
	}
}
