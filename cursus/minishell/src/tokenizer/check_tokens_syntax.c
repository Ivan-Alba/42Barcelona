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

#include "../../inc/minishell.h"

/**
 *		Function Name:	check_and_or
 *
 *		Description:
 *
 *			This function checks the types of tokens allowed after an
 *			AND or OR token.
 *
 *		Parameters:
 *
 *			t_token  *current - The pointer to the current token.
 *
 *		Return Value:
 *
 *			int - Returns 0 if the next token is allowed and 1 if it is not.
 */
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

/**
 *		Function Name:	check_open_bracket
 *
 *		Description:
 *
 *			This function checks the types of tokens allowed after an
 *			OPEN_BRACKET token.
 *
 *		Parameters:
 *
 *			t_token  *current - The pointer to the current token.
 *
 *		Return Value:
 *
 *			int - Returns 0 if the next token is allowed and 1 if it is not.
 */
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

/**
 *		Function Name:	check_close_bracket
 *
 *		Description:
 *
 *			This function checks the types of tokens allowed after an
 *			CLOSE_BRACKET token.
 *
 *		Parameters:
 *
 *			t_token  *current - The pointer to the current token.
 *
 *		Return Value:
 *
 *			int - Returns 0 if the next token is allowed and 1 if it is not.
 */
int	check_close_bracket(t_token *current)
{
	if (current->next->type == OPEN_BRACKET || current->next->type == WORD)
	{
		print_error(UNEXPECTED_TOKEN, current->next->str);
		return (1);
	}
	return (0);
}

/**
 *		Function Name:	check_pipe
 *
 *		Description:
 *
 *			This function checks the types of tokens allowed after an
 *			PIPE token.
 *
 *		Parameters:
 *
 *			t_token  *current - The pointer to the current token.
 *
 *		Return Value:
 *
 *			int - Returns 0 if the next token is allowed and 1 if it is not.
 */
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
/**
 *		Function Name:	check_first_last_token
 *
 *		Description:
 *
 *			This function checks the tokens allowed at the beginning and
 *			end of a prompt.
 *
 *		Parameters:
 *
 *			t_token	*token		- The pointer to the token to check.
 *			int		is_first	- Indicates the position to check.
 *
 *		Return Value:
 *
 *			int - Returns 0 if the next token is allowed and 1 if it is not.
 */
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
