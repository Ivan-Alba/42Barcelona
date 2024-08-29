/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:29:08 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/14 14:26:03 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Adds a new token of type "<", "<<", ">" or ">>" to the t_token list
void	token_great_less(t_data	*data, int *i)
{
	char	**prompt;

	prompt = data->split_info->splitted_prompt;
	if (prompt[*i][0] == '<')
	{
		if (prompt[*i + 1] && prompt[*i + 1][0] == '<')
		{
			add_new_token(data, ft_strdup("<<"), HEREDOC);
			(*i)++;
		}
		else
			add_new_token(data, ft_strdup("<"), IN_F);
	}
	else if (prompt[*i][0] == '>')
	{
		if (prompt[*i + 1] && prompt[*i + 1][0] == '>')
		{
			add_new_token(data, ft_strdup(">>"), OUT_AP_F);
			(*i)++;
		}
		else
			add_new_token(data, ft_strdup(">"), OUT_F);
	}
}

//Adds a new token of type "|" or "||" to the t_token list
void	token_pipe_or(t_data *data, int *i)
{
	char	*current;
	char	*next;

	current = data->split_info->splitted_prompt[*i];
	next = data->split_info->splitted_prompt[(*i) + 1];
	if (current[0] == '|')
	{
		if (next && next[0] == '|')
		{
			add_new_token(data, ft_strdup("||"), OR);
			(*i)++;
		}
		else
			add_new_token(data, ft_strdup("|"), PIPE);
	}
}

//Adds a new token of type "&" or "&&" to the t_token list
void	token_amper_and(t_data *data, int *i)
{
	char	*current;
	char	*next;

	current = data->split_info->splitted_prompt[*i];
	next = data->split_info->splitted_prompt[(*i) + 1];
	if (current[0] == '&')
	{
		if (next && next[0] == '&')
		{
			add_new_token(data, ft_strdup("&&"), AND);
			(*i)++;
		}
		else
			add_new_token(data, ft_strdup("&"), AMPER);
	}
}

//TODO NOT REMOVE QUOTES
//Adds a new token of type "WORD", founded between quotes to the t_token list
void	token_quotes(t_data *data, int *i)
{
	char	*res;
	char	*aux;
	char	quote_type;

	res = NULL;
	quote_type = data->split_info->splitted_prompt[(*i)][0];
	while (data->split_info->splitted_prompt[++(*i)][0] != quote_type)
	{
		if (!res)
			res = ft_strdup(data->split_info->splitted_prompt[(*i)]);
		else
		{
			aux = res;
			res = ft_strcat(res, data->split_info->splitted_prompt[(*i)]);
			free(aux);
		}
		if (!res)
			print_error_exit(MALLOC_ERROR, data);
	}
	if (res)
		add_new_token(data, res, WORD);
}

//Adds a new token of type "(" or ")" to the t_token list
void	token_brackets(t_data *data, int *i)
{
	char	*current;

	current = data->split_info->splitted_prompt[*i];
	if (current[0] == '(')
		add_new_token(data, ft_strdup("("), OPEN_BRACKET);
	else
		add_new_token(data, ft_strdup(")"), CLOSE_BRACKET);
}
