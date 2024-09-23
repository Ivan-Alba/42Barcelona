/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:31:40 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/23 16:40:10 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	file_match(char *filename, char *pattern, int *i, int *j)
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

int	can_expand_wildcar(char *cmd)
{
	int		i;
	char	quote_type;

	i = -1;
	while (cmd && cmd[++i])
	{
		if (cmd[i] == '\\')
			i++;
		else if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			quote_type = cmd[i];
			while (cmd[++i] != quote_type)
			{
				if (cmd[i] == '\\')
					i++;
				else if (cmd[i] == '*')
					return (0);
			}
		}
	}
	return (1);
}

void	remove_until_next(char **str, char **new_str, int *j, t_data *data)
{
	char	quote_type;

	quote_type = (*str)[*j];
	while ((*str)[++(*j)] != quote_type)
	{
		if ((*str)[*j] == '\\')
			(*new_str) = ft_free_strcat((*new_str),
					str_from_char((*str)[++(*j)]));
		else
			(*new_str) = ft_free_strcat((*new_str), str_from_char((*str)[*j]));
		malloc_protection((*new_str), data);
	}
}

void	remove_quotes(char **str, t_data *data)
{
	int		j;
	char	*new_str;

	new_str = NULL;
	j = -1;
	while ((*str)[++j])
	{
		if ((*str)[j] == '\\')
		{
			new_str = ft_free_strcat(new_str, str_from_char((*str)[++j]));
			malloc_protection(new_str, data);
		}
		else if ((*str)[j] == '\'' || (*str)[j] == '"')
			remove_until_next(str, &new_str, &j, data);
		else
		{
			new_str = ft_free_strcat(new_str, str_from_char((*str)[j]));
			malloc_protection(new_str, data);
		}
	}
	if (!new_str)
		new_str = ft_strdup("");
	malloc_protection(new_str, data);
	free((*str));
	*str = new_str;
}

void	add_to_cmd(char ***cmd, int *i, char ***matches, t_data *data)
{
	char	**new_cmd;
	int		j;
	int		h;

	new_cmd = NULL;
	j = -1;
	while ((*cmd)[++j] && j < *i)
	{
		new_cmd = add_to_array(&new_cmd, (*cmd)[j]);
		malloc_protection(new_cmd, data);
	}
	h = -1;
	while ((*matches)[++h])
	{
		new_cmd = add_to_array(&new_cmd, (*matches)[h]);
		malloc_protection(new_cmd, data);
	}
	*i += h - 1;
	while (++j < str_array_len(*cmd) && (*cmd)[j - h])
	{
		new_cmd = add_to_array(&new_cmd, (*cmd)[j]);
		malloc_protection(new_cmd, data);
	}
	free_split(cmd);
	*cmd = new_cmd;
}
