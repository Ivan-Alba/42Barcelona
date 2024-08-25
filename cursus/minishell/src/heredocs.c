/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:55:08 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/22 20:22:26 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Removes temporary files created by heredocs
void	remove_heredoc_files(t_section **section)
{
	t_files	*current_file;

	current_file = (*section)->files;
	while (current_file)
	{
		if (current_file->file_type == HEREDOC
			&& current_file->hrdc_file_name)
		{
			//TODO test prints
			if (unlink(current_file->hrdc_file_name) != -1)
				printf("Heredoc file \"%s\" deleted\n",
					current_file->hrdc_file_name);
			else
				printf("Error deleting %s file\n",
					current_file->hrdc_file_name);
		}
		current_file = current_file->next;
	}
}

//Function that manages the reading of data when using a limiter
void	read_heredoc(t_data *data, t_files *file)
{
	char		*line;
	char		*suffix;

	suffix = ft_itoa(data->heredoc_file_n++);
	if (!suffix)
		print_error_exit(MALLOC_ERROR, data);
	file->hrdc_file_name = ft_strcat(".hrdc_", suffix);
	free(suffix);
	if (!(file->hrdc_file_name))
		print_error_exit(MALLOC_ERROR, data);
	file->fd = open(file->hrdc_file_name, O_CREAT | O_RDWR, 0666);
	if (file->fd == -1)
		print_error_exit(OPEN_ERROR, data);
	line = get_next_line(0);
	while (line && ft_strncmp(file->file_name, line,
			ft_strlen(file->file_name)) != 0)
	{
		write(file->fd, line, ft_strlen(line));
		free(line);
		line = NULL;
		line = get_next_line(0);
	}
	write(1, "Heredoc closed\n", 15); //TODO test print
	if (line)
		free(line);
	close(file->fd);
}

//Go through the sections and manage the opening of the heredocs
void	manage_heredocs(t_data *data)
{
	t_section	*current_sec;
	t_files		*current_file;

	current_sec = data->sections;
	while (current_sec)
	{
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
