/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:29:24 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/23 16:04:20 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_space(char *cmd)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (cmd[i])
	{
		if (cmd[i] == '\\')
			i++;
		else if (quote == '\0' && (cmd[i] == '"' || cmd[i] == '\''))
			quote = cmd[i];
		else if (quote != '\0' && cmd[i] == quote)
			quote = '\0';
		else if (quote == '\0' && cmd[i] == ' ')
			return (i);
		i++;
	}
	return (-1);
}

void	word_splitting(char ***cmd, int	*idx, t_data *data)
{
	char	**cmd_add;
	int		curr_idx;
	char	*to_add;

	curr_idx = 0;
	cmd_add = NULL;
	while (is_space(&(*cmd)[*idx][curr_idx]) >= 0)
	{
		to_add = ft_substr(&(*cmd)[*idx][curr_idx], 0,
				is_space(&(*cmd)[*idx][curr_idx]));
		malloc_protection(to_add, data);
		cmd_add = add_to_array(&cmd_add, to_add);
		free(to_add);
		malloc_protection(cmd_add, data);
		curr_idx += is_space(&(*cmd)[*idx][curr_idx]);
		while ((*cmd)[*idx][curr_idx] == ' ')
			curr_idx++;
	}
	cmd_add = add_to_array(&cmd_add, &((*cmd)[*idx][curr_idx]));
	malloc_protection(cmd_add, data);
	add_to_cmd(cmd, idx, &cmd_add, data);
	free_split(&cmd_add);
}

void	files_expansion(t_files *curr_file, t_data *data)
{
	if (curr_file->file_type != HEREDOC)
	{
		curr_file->file_name = expand_env_vars(
				curr_file->file_name, 0, data);
		if (curr_file->file_name && is_space(curr_file->file_name) >= 0)
		{
			free(curr_file->file_name);
			curr_file->file_name = NULL;
		}
	}
}

char	*mark_quotes(char *exp_value, t_data *data)
{
	int		i;
	char	*value;

	i = -1;
	value = NULL;
	while (exp_value[++i])
	{
		if (exp_value[i] == '"' || exp_value[i] == '\'' || exp_value[i] == '\\')
		{
			value = ft_free_strcat(value, str_from_char('\\'));
			malloc_protection(value, data);
		}
		value = ft_free_strcat(value, str_from_char(exp_value[i]));
		malloc_protection(value, data);
	}
	free(exp_value);
	return (value);
}
