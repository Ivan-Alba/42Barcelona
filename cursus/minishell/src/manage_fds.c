/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:24 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/26 12:51:21 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_section_fds(t_section *section)
{
	if (section->fd_in != -1)
	{
		if (close(section->fd_in) == -1)
			perror(CLOSE_ERROR);
	}
	if (section->fd_out != -1)
	{
		if (close(section->fd_out) == -1)
			perror(CLOSE_ERROR);
	}
}

int	set_infile(t_section *section, t_files *file)
{
	int		fd;
	char	*filename;

	if (file->file_type == IN_F)
		filename = file->file_name;
	else if (file->file_type == HEREDOC)
		filename = file->hrdc_file_name;
	if (access(filename, F_OK) == -1
		|| access(filename, R_OK) == -1)
	{
		perror(filename);
		close_section_fds(section); //TODO CLOSE ERROR?
		return (1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(OPEN_ERROR);
		close_section_fds(section);
		return (1);
	}
	if (section->fd_in != -1)
		close(section->fd_in);
	section->fd_in = fd;
	return (0);
}

int	set_outfile(t_section *section, t_files *file)
{
	int	fd;

	if (!access(file->file_name, F_OK) && access(file->file_name, W_OK) == -1)
	{
		perror(file->file_name);
		close_section_fds(section);
		return (1);
	}
	else
	{
		if (file->file_type == OUT_F)
			fd = open(file->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else
			fd = open(file->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
		{
			perror(OPEN_ERROR);
			close_section_fds(section);
			return (1);
		}
		if (section->fd_out != -1)
			close(section->fd_out);
		section->fd_out = fd;
	}
	return (0);
}

int	open_fds(t_section *section)
{
	t_files	*curr_file;
	int		error;

	curr_file = section->files;
	while (curr_file)
	{
		if (curr_file->file_type == HEREDOC || curr_file->file_type == IN_F)
			error = set_infile(section, curr_file);
		if (curr_file->file_type == OUT_F || curr_file->file_type == OUT_AP_F)
			error = set_outfile(section, curr_file);
		if (error)
			return (error);
		curr_file = curr_file->next;
	}
	return (0);
}
