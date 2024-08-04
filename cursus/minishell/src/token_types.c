/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:29:08 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/02 17:56:40 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	token_great_less(t_data	*data, int *i)
{
	if (data->split_info->splitted_prompt[*i][0] == '<')
	{
		if (data->split_info->splitted_prompt[*i + 1][0] == '<')
		{
			ft_token_add_back(&(data->tokens), ft_token_new(ft_strdup("<<"),
					HEREDOC));
			(*i)++;
		}
		else
			ft_token_add_back(&(data->tokens), ft_token_new(ft_strdup("<"),
					IN_F));
	}
	else if (data->split_info->splitted_prompt[*i][0] == '>')
	{
		if (data->split_info->splitted_prompt[*i + 1][0] == '>')
		{
			ft_token_add_back(&(data->tokens), ft_token_new(ft_strdup(">>"),
					OUT_AP_F));
			(*i)++;
		}
		else
			ft_token_add_back(&(data->tokens), ft_token_new(ft_strdup(">"),
					OUT_F));
	}
}

void	token_pipe_or_and(t_data *data, int *i)
{
	char	*current;
	char	*next;

	current = data->split_info->splitted_prompt[*i];
	next = data->split_info->splitted_prompt[(*i) + 1];
	if (current[0] == '|')
	{
		if (next[0] == '|')
		{
			ft_token_add_back(&(data->tokens),
				ft_token_new(ft_strdup("||"), OR));
			(*i)++;
		}
		else
			ft_token_add_back(&(data->tokens),
				ft_token_new(ft_strdup("|"), PIPE));
	}
	else if (current[0] == '&' && next[0] == '&')
	{
		ft_token_add_back(&(data->tokens), ft_token_new(ft_strdup("&&"), AND));
		(*i)++;
	}
}

void	token_quotes(t_data *data, int *i)
{
	int		x;
	char	*res;
	char	*aux;
	char	quote_type;

	x = 0;
	res = NULL;
	quote_type = data->split_info->splitted_prompt[(*i)++][0];
	while (data->split_info->splitted_prompt[*i + x][0] != quote_type)
	{
		if (!res)
			res = ft_strdup(data->split_info->splitted_prompt[*i + x]);
		else
		{
			aux = res;
			res = ft_strcat(res, data->split_info->splitted_prompt[(*i) + x]);
			free(aux);
		}
		if (!res)
			print_error_exit(MALLOC_ERROR, data);
		x++;
	}
	(*i) += x;
	if (x > 0)
		ft_token_add_back(&(data->tokens), ft_token_new(res, WORD));
}

void	token_brackets(t_data *data, int *i)
{
	char	*current;

	current = data->split_info->splitted_prompt[*i];
	if (current[0] == '(')
		ft_token_add_back(&(data->tokens),
			ft_token_new(ft_strdup("("), OPEN_BRACKET));
	else
		ft_token_add_back(&(data->tokens),
			ft_token_new(ft_strdup(")"), CLOSE_BRACKET));
}

void	token_word(t_data *data, int *i)
{
	char	*current;

	current = data->split_info->splitted_prompt[*i];
	ft_token_add_back(&(data->tokens), ft_token_new(ft_strdup(current), WORD));
}
