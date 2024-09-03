/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:31:40 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/02 16:38:50 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_match_files(char *filename, char *pattern)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (file_match(filename, pattern, &i, &j) == 0)
		return (NULL);
	while (pattern[j] == '*')
		j++;
	if (!pattern[j])
		return (filename);
	return (NULL);
}

char	**search_files(char	*regex, t_data *data)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**res;

	dir = opendir(".");
	res = NULL;
	if (!dir)
		perror("Error opening directory");
	entry = readdir(dir);
	while (entry)
	{
		if (get_match_files(entry->d_name, regex))
		{
			res = add_to_array(&res, get_match_files(entry->d_name, regex));
			malloc_protection(res, data);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (res);
}

void	expand_wildcard_cmd(char ***cmd, int *i, t_data *data)
{
	char	**matches;

	matches = NULL;
	if (can_expand_wildcar((*cmd)[*i]))
	{
		remove_quotes(&((*cmd)[*i]), data);
		matches = search_files((*cmd)[*i], data);
		if (matches)
			add_to_cmd(cmd, i, &matches, data);
	}
	else
		remove_quotes(&((*cmd)[*i]), data);
	if (matches)
		free_split(&matches);
}

void	expand_wildcard_file(t_files *file, t_data *data)
{
	char	**matches;
	int		len;

	if (can_expand_wildcar(file->file_name))
	{
		remove_quotes(&file->file_name, data);
		matches = search_files(file->file_name, data);
		if (matches)
		{
			len = 0;
			while (matches[len])
				len++;
			free(file->file_name);
			file->file_name = NULL;
			if (len == 1)
				file->file_name = ft_strdup(matches[0]);
			free_split(&matches);
		}
	}
}

/**
 *	Function Name: manage_wildcard
 *
 *	Description:
 *
 *		This function goes through all the commands and file names of the section
 *		received by parameter and calls the function in charge of checking if
 *		there are wildcards(*) to expand and expand them if so.
 *
 *	Parameters:
 *
 *		t_section *section	- The pointer to the section from which to expand its
 *								variables.
 *		t_data *data		- The pointer to the t_data struct with all
 *								the execution data.
 *
 */
void	manage_wildcard(t_section *section, t_data *data)
{
	int		i;
	t_files	*curr_file;

	i = 0;
	while (section->cmd && section->cmd[i])
	{
		expand_wildcard_cmd(&section->cmd, &i, data);
		i++;
	}
	curr_file = section->files;
	while (curr_file)
	{
		if (curr_file->file_type != HEREDOC)
		{
			expand_wildcard_file(curr_file, data);
		}
		curr_file = curr_file->next;
	}
}
