/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:55:08 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/05 18:12:30 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Function Name: remove_hrdc_quotes
 *
 *	Description:
 *
 *		This function receives a HEREDOC file by parameter and removes (if any)
 *		single and double quotes from its name.
 *		If any quotation marks are found it sets heredoc to non-expansion mode.
 *
 *	Parameters:
 *
 *		t_files *file	- The pointer to the heredoc file.
 *		t_data *data	- The pointer to the t_data struct with all
 *							the execution data
 *
 */
void	remove_hrdc_quotes(t_files *file, t_data *data)
{
	int		i;
	char	*new_name;

	i = -1;
	new_name = NULL;
	while (file->file_name[++i])
	{
		if (file->file_name[i] == '\'' || file->file_name[i] == '\"')
			file->hrdc_expand = 0;
		else
			new_name = concat_char_to_str(new_name, file->file_name[i], data);
	}
	free(file->file_name);
	file->file_name = new_name;
}

/*	Function Name: remove_heredoc_files
 *
 *	Description:
 *
 *		This function deletes temporary files of type heredoc created during
 *		execution.
 *
 *	Parameters:
 *
 *		t_section *section	- The pointer to the section containing the
 *								data of the heredocs created in it.
 *
 */
void	remove_heredoc_files(t_section *section)
{
	t_files	*current_file;

	current_file = section->files;
	while (current_file)
	{
		if (current_file->file_type == HEREDOC
			&& current_file->hrdc_file_name)
		{
			if (unlink(current_file->hrdc_file_name) == -1)
				perror("Error deleting file");
		}
		current_file = current_file->next;
	}
}

void	print_heredoc_eof(t_files *file, t_data *data)
{
	char	*eof_line;

	eof_line = ft_itoa(data->heredoc_eof_line);
	malloc_protection(eof_line, data);
	write(2, HEREDOC_EOF_1, ft_strlen(HEREDOC_EOF_1));
	write(2, eof_line, ft_strlen(eof_line));
	free(eof_line);
	write(2, HEREDOC_EOF_2, ft_strlen(HEREDOC_EOF_2));
	write(2, file->file_name, ft_strlen(file->file_name) - 1);
	write(2, HEREDOC_EOF_3, ft_strlen(HEREDOC_EOF_3));
	write(2, "\n", 1);
}

/*	Function Name: read_heredoc
 *
 *	Description:
 *
 *		This function creates the temporary file heredoc, reads the user input
 *		line by line and writes its contents to the file until the limiter
 *		is entered.
 *		If the file has expansion set, it calls the function in charge of
 *		expanding the environment variables before writing it.
 *
 *	Parameters:
 *
 *		t_files *file	- The pointer to the heredoc file with all
 *							heredoc data.
 *		t_data *data	- The pointer to the t_data struct with all
 *							the execution data
 */
void	read_heredoc(t_files *file, t_data *data)
{
	char		*line;

	if (!(file->hrdc_file_name))
		print_error_exit(MALLOC_ERROR, data);
	file->fd = open(file->hrdc_file_name, O_CREAT | O_RDWR, 0666);
	if (file->fd == -1)
		print_error_exit(OPEN_ERROR, data);
	write(2, "> ", 2);
	line = get_next_line(0);
	while (line && ft_strncmp(file->file_name, line,
			ft_strlen(file->file_name)) != 0)
	{
		if (file->hrdc_expand)
			line = expand_env_vars(line, 1, data);
		write(file->fd, line, ft_strlen(line));
		free(line);
		line = NULL;
		write(2, "> ", 2);
		line = get_next_line(0);
	}
	if (line)
		free(line);
	else
		print_heredoc_eof(file, data);
	close(file->fd);
}

/*	Function Name: manage_heredocs
 *
 *	Description:
 *
 *		This function, which is executed before starting the execution of
 *		the sections, manages the opening of heredoc files of all sections
 *		and the writing of their contents.
 *
 *	Parameters:
 *
 *		t_data *data	- The pointer to the t_data struct with all
 *							the execution data
 */
void	manage_heredocs(t_data *data)
{
	t_section	*current_sec;
	t_files		*current_file;
	char		*suffix;

	current_sec = data->sections;
	while (current_sec)
	{
		current_file = current_sec->files;
		while (current_file)
		{
			if (current_file->file_type == HEREDOC)
			{
				remove_hrdc_quotes(current_file, data);
				suffix = ft_itoa((long)current_file * (long)&suffix / 2);
				if (!suffix)
					print_error_exit(MALLOC_ERROR, data);
				current_file->hrdc_file_name = ft_strcat("/tmp/.hrdc_", suffix);
				free(suffix);
				read_heredoc(current_file, data);
			}
			current_file = current_file->next;
		}
		current_sec = get_next_section(current_sec, data->section_id - 1);
	}
}
