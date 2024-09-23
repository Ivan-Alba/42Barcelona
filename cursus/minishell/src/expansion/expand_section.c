/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_section.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:05:50 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/23 13:36:28 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 *	Function Name: get_var_value
 *
 *	Description:
 *
 *		This function searches the value of a variable in the environment
 *		variables stored in the t_data struct and returns it.
 *
 *	Parameters:
 *
 *		char *var_name - The name of the variable to search for.
 *		t_data *data   - The pointer to the t_data struct with all execution
 *							data.
 *
 *	Return Value:
 *
 *		char*	- Returns the value of the environment variable or a empty string
 *				("") if not.
 */
char	*get_var_value(char **var_name, t_data *data, int is_quotes)
{
	int		i;
	int		found;
	char	*var_equal;

	found = 0;
	i = 0;
	var_equal = ft_strcat(&((*var_name)[1]), "=");
	free(*var_name);
	malloc_protection(var_equal, data);
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], var_equal, ft_strlen(var_equal)))
			found = 1;
		if (found)
			break ;
		i++;
	}
	free(var_equal);
	if (found)
		return (mark_quotes(ft_strdup(ft_strchr(data->env[i], '=') + 1), data));
	else if (is_quotes)
		return (ft_strdup(""));
	else
		return (NULL);
}

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
	else if (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_')
	{
		len = 1;
		while (ft_isalnum(str[++(*i)]) || str[*i] == '_')
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

char	*expand_env_vars(char *str, int is_heredoc, t_data *data)
{
	int		i;
	char	*str_expanded;
	char	*aux;

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
	if (str_expanded)
	{
		aux = str_expanded;
		str_expanded = ft_strtrim(str_expanded, " ");
		free(aux);
		malloc_protection(str_expanded, data);
	}
	return (free(str), str_expanded);
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
		{
			if (section->cmd[i])
				word_splitting(&section->cmd, &i, data);
			i++;
		}
	}
	curr_file = section->files;
	while (curr_file)
	{
		files_expansion(curr_file, data);
		curr_file = curr_file->next;
	}
}
