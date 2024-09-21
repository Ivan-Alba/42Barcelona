/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:24 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/02 13:38:37 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*	Function Name: close_section_fds
 *
 *	Description:
 *
 *		This function closes the input and output fd's assigned to the section
 *		(if there are any).
 *
 *	Parameters:
 *
 *		t_section *section	- The pointer to the current section.
 *
 */
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

/*	Function Name: set_infile 
 *
 *	Description:
 *
 *		This function handles infile type files (< and <<). It checks if the
 *		file exists and if we have read permission and opens it.
 *		If there is any error, it closes the fd's of the section that could be
 *		open and returns the error code.
 *
 *	Parameters:
 *
 *		t_section *section	- The pointer to the current section.
 *		t_files *file		- The pointer to the file
 *
 *	Return Value:
 *
 *		int status_code	- 0 or 1 if success or error, respectively.
 *
 */
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
		print_perror(filename);
		close_section_fds(section);
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

/**
 *	Function Name: set_outfile 
 *
 *	Description:
 *
 *		This function handles outfile type files (> and >>). It checks if the
 *		file exists and if we have write permission and opens it in one mode or
 *		another depending on the type (TRUNCATE or APPEND).
 *		If there is any error, it closes the fd's of the section that could be
 *		open and returns the error code.
 *
 *	Parameters:
 *
 *		t_section *section	- The pointer to the current section.
 *		t_files *file		- The pointer to the file
 *
 *	Return Value:
 *
 *		int status_code	- 0 or 1 if success or error, respectively.
 *
 */
int	set_outfile(t_section *section, t_files *file)
{
	int	fd;

	if (!access(file->file_name, F_OK) && access(file->file_name, W_OK) == -1)
	{
		print_perror(file->file_name);
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

/**
 *	Function Name: open_fds 
 *
 *	Description:
 *
 *		This function goes through the file structure t_files of the section
 *		received by parameter and opens them (in order according to the prompt)
 *		and sets them as input or output fd of the section.
 *		The last files of each type (outfile and infile) will be the input and
 *		output fd's of the section.
 *
 *	Parameters:
 *
 *		t_section *section	- The pointer to the section from which to open its
 *								files.
 *
 *	Return Value:
 *
 *		int status_code	- 0 or 1 if success or error, respectively.
 *
 */

int	open_fds(t_section *section)
{
	t_files	*curr_file;
	int		status_code;

	status_code = 0;
	curr_file = section->files;
	while (curr_file)
	{
		if (curr_file->file_type != HEREDOC && !curr_file->file_name)
		{
			print_ambiguous_error(curr_file->name_before_exp);
			return (1);
		}
		if (curr_file->file_type == HEREDOC || curr_file->file_type == IN_F)
			status_code = set_infile(section, curr_file);
		else
			status_code = set_outfile(section, curr_file);
		if (status_code)
			return (status_code);
		curr_file = curr_file->next;
	}
	return (status_code);
}
