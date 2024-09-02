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

int		check_filename_pattern(char *filename, char *pattern, int *i, int *j)
{
	int	star;
	int	saved_i;

	star = -1;
	saved_i = 0;
	while (filename[*i])
	{
		if (pattern[*j] == '*')
		{
			star = *j;
			saved_i = *i;
			(*j)++;
		}
		else if (pattern[*j] == filename[*i] && ++(*j) >= 0)
			(*i)++;
		else if (star != -1)
		{
			*j = star + 1;
			*i = ++saved_i;
		}
		else
			return (0);
	}
	return (1);
}

char	*get_match_files(char *filename, char *pattern)
{
	int	i;
	int	j;

	i = 0;
	j = 0;	
	if (check_filename_pattern(filename, pattern, &i, &j) == 0)
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

int	can_expand_wildcar(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' && i++ >= 0)
		{
			while (cmd[i] != '\'')
				if (cmd[i++] == '*')
					return (0);
			i--;
		}
		else if (cmd[i] == '"' && i++ >= 0)
		{
			while (cmd[i] != '"')
				if (cmd[i++] == '*')
					return (0);
			i--;
		}
	}
	return (1);
}

char	*remove_quotes(char **str, t_data *data)
{
	int		j;
	char	*new_str;

	new_str = NULL;
	j = -1;
	while ((*str)[++j])
	{
		if ((*str)[j] == '\'' && j++ >= 0)
		{
			while ((*str)[j] != '\'')
				new_str = ft_free_strcat(new_str, string_from_char((*str)[j++]));
		}
		else if ((*str)[j] == '"' && j++ >= 0)
		{
			while ((*str)[j] != '"')
				new_str = ft_free_strcat(new_str, string_from_char((*str)[j++]));
		}
		else
			new_str = ft_free_strcat(new_str, string_from_char((*str)[j]));
		malloc_protection(new_str, data);
	}
	free((*str));
	return (new_str);
}

void	add_cmd_to_array(char ***cmd, int *i, char ***matches, t_data *data)
{
	int	len;

	len = 0;
	while ((*matches)[len])
		len++;

}

void	expand_wildcard_cmd(char ***cmd, int *i, t_data *data)
{
	char	**matches;

	if (can_expand_wildcar((*cmd)[*i]))
	{
		remove_quotes(&((*cmd)[*i]), data);
		matches = search_files((*cmd)[*i], data);
		if (matches)
			add_cmd_to_array(cmd, i, &matches, data);
	}
	else
		remove_quotes(&((*cmd)[*i]), data);
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
			if (len > 1)
			{
				file->name_before_exp = file->file_name;
				free(file->file_name);
				file->file_name = NULL;
				return ;
			}
			free(file->file_name);
			file->file_name = matches[0];
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
