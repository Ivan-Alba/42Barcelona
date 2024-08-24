/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_syntax.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:20:17 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/17 15:41:36 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Checks the tokens allowed after a token of type AND or OR
int	check_and_or(t_token *current)
{
	if (current->type == AMPER || current->type == FORB)
	{
		print_error(UNEXPECTED_TOKEN, current->str);
		return (1);
	}
	if (current->next->type != WORD && current->next->type != OPEN_BRACKET
		&& current->next->type != IN_F && current->next->type != HEREDOC
		&& current->next->type != OUT_F && current->next->type != OUT_AP_F)
	{
		print_error(UNEXPECTED_TOKEN, current->next->str);
		return (1);
	}
	return (0);
}

//Checks the tokens allowed after a token of type OPEN_BRACKET
int	check_open_bracket(t_token *current)
{
	if (current->next->type != OPEN_BRACKET && current->next->type != WORD
		&& current->next->type != HEREDOC && current->next->type != IN_F
		&& current->next->type != OUT_F && current->next->type != OUT_AP_F)
	{
		print_error(UNEXPECTED_TOKEN, current->next->str);
		return (1);
	}
	return (0);
}

//Checks the tokens allowed after a token of type CLOSE_BRACKET
int	check_close_bracket(t_token *current)
{
	if (current->next->type == OPEN_BRACKET || current->next->type == WORD)
	{
		print_error(UNEXPECTED_TOKEN, current->next->str);
		return (1);
	}
	return (0);
}

//Checks the tokens allowed after a token of type PIPE
int	check_pipe(t_token *current)
{
	if (current->next->type != WORD && current->next->type != OPEN_BRACKET
		&& current->next->type != OUT_F && current->next->type != OUT_AP_F
		&& current->next->type != IN_F && current->next->type != HEREDOC)
	{
		print_error(UNEXPECTED_TOKEN, current->next->str);
		return (1);
	}
	return (0);
}

//Checks the tokens allowed at the beginning and end of a prompt
int	check_first_last_token(t_token *token, int is_first)
{
	if (token)
	{
		if (is_first)
		{
			if (token->type == CLOSE_BRACKET || token->type == PIPE
				|| token->type == AND || token->type == OR)
			{
				print_error(UNEXPECTED_TOKEN, token->str);
				return (1);
			}
		}
		else
		{
			if (token->type != WORD && token->type != CLOSE_BRACKET)
			{
				print_error(UNEXPECTED_TOKEN, token->str);
				return (1);
			}
		}
	}
	return (0);
}
