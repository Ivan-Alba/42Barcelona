/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_section.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:05:50 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/29 18:47:39 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand_var(char *str, char **str_exp, int *i, t_data *data)
{
	int		len;
	char	*var_name;
	char	*exit_status;

	if (str[*i + 1] == '$' && (*i)++ >= 0)
		*str_exp = ft_free_strcat(*str_exp, ft_strdup("40078"));
	else if (str[*i + 1] == '?' && (*i)++ >= 0)
	{
		exit_status = ft_itoa(data->last_exit_status);
		malloc_protection(exit_status, data);
		*str_exp = ft_free_strcat(*str_exp, exit_status);
	}
	else if (ft_isalnum(str[*i + 1]))
	{
		len = 1;
		while (ft_isalnum(str[++(*i)]))
			len++;
		var_name = ft_strcut(&(str[(*i) - len]), len);
		malloc_protection(var_name, data);
		(*i)--;
		return (var_name);
	}
	else
		*str_exp = ft_free_strcat(*str_exp, ft_strdup("$"));
	return (NULL);
}

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

char	*expand_env_vars(char *str, int is_heredoc, t_data *data)
{
	int		i;
	char	*str_expanded;

	i = -1;
	str_expanded = NULL;
	while (str[++i])
	{
		if (is_heredoc)
			no_quote_exp(str, &str_expanded, &i, data);
		else if (str[i] == '\'')
			single_quote_exp(str, &str_expanded, &i, data);
		else if (str[i] == '"')
			double_quote_exp(str, &str_expanded, &i, data);
		else
			no_quote_exp(str, &str_expanded, &i, data);
	}
	free(str);
	return (str_expanded);
}

void	reorder_cmd(char ***cmd, int remove_idx, t_data *data)
{
	int		i;
	char	*aux;

	i = remove_idx + 1;
	while ((*cmd)[i])
	{
		aux = ft_strdup((*cmd)[i]);
		malloc_protection(aux, data);
		(*cmd)[i - 1] = aux;
		free((*cmd)[i]);
		(*cmd)[i] = NULL;
		i++;
	}
}

/**
 *	Function Name: expand_section
 *
 *	Description:
 *
 *		This function goes through all the commands and file names of the section
 *		received by parameter and calls the function in charge of checking if
 *		there are environment variables to expand and expand them if so.
 *
 *	Parameters:
 *
 *		t_section *section	- The pointer to the section from which to expand its
 *								variables.
 *		t_data *data		- The pointer to the t_data struct with all
 *								the execution data.
 *
 */
void	expand_section(t_section *section, t_data *data)
{
	int		i;
	t_files	*curr_file;

	i = 0;
	while (section->cmd && section->cmd[i])
	{
		section->cmd[i] = expand_env_vars(section->cmd[i], 0, data);
		if (!section->cmd[i] && section->cmd[i + 1])
			reorder_cmd(&section->cmd, i, data);
		else
			i++;
	}
	curr_file = section->files;
	while (curr_file)
	{
		if (curr_file->file_type != HEREDOC)
			curr_file->file_name = expand_env_vars(
					curr_file->file_name, 0, data);
		curr_file = curr_file->next;
	}
}
