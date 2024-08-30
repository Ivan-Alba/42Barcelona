/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:55:08 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/29 20:20:44 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*	Function Name: remove_quotes
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
void	remove_quotes(t_files *file, t_data *data)
{
	int		i;
	char	*result;

	i = -1;
	result = NULL;
	while (file->file_name[++i])
	{
		if (file->file_name[i] == '\'' || file->file_name[i] == '\"')
			file->hrdc_expand = 0;
		else
			result = concat_char_to_str(result, file->file_name[i], data);
	}
	free(file->file_name);
	file->file_name = result;
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

/*	Function Name: expand_heredoc_line
 *
 *	Description:
 *
 *		This function scans the line read by heredoc and calls the functions in
 *		charge of expanding environment variables.
 *		It frees the original line and returns the expanded one.
 *
 *	Parameters:
 *
 *		char *line		- The original line readed on heredoc to expand.
 *		t_data *data	- The pointer to the t_data struct with all
 *							the execution data
 *	Return Value:
 *
 *		char *line_expanded	- The new line expanded with the environment values.
 */
char	*expand_heredoc_line(char *line, t_data *data)
{
	int		i;
	char	*line_expanded;

	i = -1;
	while (line[++i])
	{
		trim_vars(line, &i, data);
		if (!data->expand_vars)
			print_error_exit(MALLOC_ERROR, data);
	}
	free(line);
	line = NULL;
	line_expanded = expand_vars(data);
	free_split(&data->expand_vars);
	return (line_expanded);
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
	line = get_next_line(0);
	while (line && ft_strncmp(file->file_name, line,
			ft_strlen(file->file_name)) != 0)
	{
		if (file->hrdc_expand)
			line = expand_heredoc_line(line, data);
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
				remove_quotes(current_file, data);
				suffix = ft_itoa(data->heredoc_file_n++);
				if (!suffix)
					print_error_exit(MALLOC_ERROR, data);
				current_file->hrdc_file_name = ft_strcat(".hrdc_", suffix);
				free(suffix);
				read_heredoc(current_file, data);
			}
			current_file = current_file->next;
		}
		current_sec = get_next_section(current_sec, data->section_id - 1);
	}
}
