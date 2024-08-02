/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:29:08 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/30 15:50:50 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	token_great_less(t_data	*data, int *i)
{
	char	*current;
	char	*next;

	current = data->split_info->splitted_prompt[*i];
	next = data->split_info->splitted_prompt[(*i) + 1];
	if (current[0] == '<')
	{
		if (next[0] == '<')
		{
			ft_lstadd_back(&(data->tokens), ft_lstnew(str, HEREDOC));
			(*i)++;
		}
		else
			ft_lstadd_back(&(data->tokens), ft_lstnew(str, INPUT_FILE));
	}
	else if (current[0] == '>')
	{
		if (next[0] == '>')
		{
			ft_lstadd_back(&(data->tokens), ft_lstnew(str, OUT_APPEND_FILE));
			(*i)++;
		}
		else
			ft_lstadd_back(&(data->tokens), ft_lstnew(str, OUTPUT_FILE));
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
			ft_lstadd_back(&(data->tokens), ft_lstnew(str, OR));
			(*i)++;
		}
		else
			ft_lstadd_back(&(data->tokens), ft_lstnew(str, PIPE));	
	}
	else if (current[0] == '&' && next[0] == '&')
	{
		ft_lstadd_back(&(data->tokens), ft_lstnew(str, AND));
		(*i)++;
	}
}
