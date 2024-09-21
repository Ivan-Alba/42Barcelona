/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:05:50 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/29 17:25:55 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	single_quote_exp(char *str, char **str_exp, int *i, t_data *data)
{
	*str_exp = ft_free_strcat(*str_exp, ft_strdup("\'"));
	malloc_protection(*str_exp, data);
	while (str[++(*i)] != '\'')
	{
		*str_exp = ft_free_strcat(*str_exp, string_from_char(str[*i]));
		malloc_protection(*str_exp, data);
	}
	*str_exp = ft_free_strcat(*str_exp, ft_strdup("\'"));
	malloc_protection(*str_exp, data);
}

void	double_quote_exp(char *str, char **str_exp, int *i, t_data *data)
{
	char	*var_name;
	char	*var_value;

	*str_exp = ft_free_strcat(*str_exp, ft_strdup("\""));
	malloc_protection(*str_exp, data);
	while (str[++(*i)] != '"')
	{
		if (str[*i] == '$')
		{
			var_name = expand_var(str, str_exp, i, data);
			if (var_name)
			{
				var_value = get_var_value(&var_name, data, 1);
				if (var_value)
					*str_exp = ft_free_strcat(*str_exp, var_value);
			}
		}
		else
		{
			*str_exp = ft_free_strcat(*str_exp, string_from_char(str[*i]));
			malloc_protection(*str_exp, data);
		}
	}
	*str_exp = ft_free_strcat(*str_exp, ft_strdup("\""));
	malloc_protection(*str_exp, data);
}

void	no_quote_exp(char *str, char **str_exp, int *i, t_data *data)
{
	char	*var_name;
	char	*var_value;

	if (str[*i] == '$')
	{
		var_name = expand_var(str, str_exp, i, data);
		if (var_name)
		{
			var_value = get_var_value(&var_name, data, 0);
			if (var_value)
				*str_exp = ft_free_strcat(*str_exp, var_value);
		}
	}
	else
	{
		*str_exp = ft_free_strcat(*str_exp, string_from_char(str[*i]));
		malloc_protection(*str_exp, data);
	}
}

int	is_space(char *cmd)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (cmd[i])
	{
		if (quote == '\0' && (cmd[i] == '"' || cmd[i] == '\''))
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
