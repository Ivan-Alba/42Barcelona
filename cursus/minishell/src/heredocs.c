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


//TODO REVISAR FREES SI MALLOC FALLA
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
			if (unlink(current_file->hrdc_file_name) == -1)
				perror("Error deleting file");
		}
		current_file = current_file->next;
	}
}

char	*expand_heredoc_line(char *str, t_data *data)
{
	int		i;
	char	*str_expanded;

	i = -1;
	while (str[++i])
	{
		trim_vars(str, &i, data);
		if (!data->expand_vars)
			print_error_exit(MALLOC_ERROR, data);
	}
	free(str);
	str = NULL;
	//print_split(data->expand_vars);
	str_expanded = expand_vars(data);
	//printf("%s\n", str_expanded);
	free_split(&data->expand_vars);
	return (str_expanded);
}

//Function that manages the reading of data when using a limiter
void	read_heredoc(t_data *data, t_files *file)
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

//Go through the sections and manage the opening of the heredocs
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
				read_heredoc(data, current_file);
			}
			current_file = current_file->next;
		}
		current_sec = get_next_section(current_sec, data->section_id - 1);
	}
}
