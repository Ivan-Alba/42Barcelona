/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:20:17 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/07 17:12:41 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_tokens_format(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	if (current->type != WORD && current->type != HEREDOC && current->type != IN_F)
	{
		print_error(UNEXPECTED_TOKEN, current->str);
		return (1);
	}
	while (current)
	{
		if (current->next)
		{
			if ((current->type == AND || current->type == OR) && (current->next->type
				!= WORD && current->next->type != OPEN_BRACKET))
			{
				print_error(UNEXPECTED_TOKEN, current->next->str);
				return (1);
			}
			if (current->type == OPEN_BRACKET && current->next->type != OPEN_BRACKET
				&& current->next->type != WORD && current->next->type != HEREDOC
				&& current->next->type != IN_F)
			{
				print_error(UNEXPECTED_TOKEN, current->next->str);
				return (1);
			}
			if (current->type == CLOSE_BRACKET && current->next->type != CLOSE_BRACKET
				&& current->next->type != PIPE && current->next->type != AND
				&& current->next->type != OR)
			{
				print_error(UNEXPECTED_TOKEN, current->next->str);
				return (1);
			}

			if (current->type != WORD && current->next->type != WORD
				&& current->type != OPEN_BRACKET && current->next->type
				!= OPEN_BRACKET && current->type != CLOSE_BRACKET
				&& current->next->type != CLOSE_BRACKET)
			{
				print_error(UNEXPECTED_TOKEN, current->next->str);
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

