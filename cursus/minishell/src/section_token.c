/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:52:55 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/17 17:15:21 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Manages the creation of a new section when a bracket is found
void	brackets_section(t_section **curr_sec, t_token **curr_tok)
{
	if ((*curr_tok)->type == OPEN_BRACKET)
	{
		(*curr_sec)->inner = new_section(*curr_sec, NULL);
		//(*curr_sec)->inner->outer = *curr_sec;
		*curr_sec = (*curr_sec)->inner;
	}
	else if ((*curr_tok)->type == CLOSE_BRACKET)
	{
		while (!(*curr_sec)->outer)
			*curr_sec = (*curr_sec)->previous;
		(*curr_sec) = (*curr_sec)->outer;
	}
}

//Manages the storage of incoming and outgoing files within the section
void	files_section(t_section **curr_sec, t_token **curr_tok)
{
	if ((*curr_tok)->type == IN_F || (*curr_tok)->type == OUT_F
		|| (*curr_tok)->type == OUT_AP_F || (*curr_tok)->type == HEREDOC)
	{
		(*curr_sec)->files[(*curr_tok)->type] = add_to_array(
				&((*curr_sec)->files[(*curr_tok)->type]),
				(*curr_tok)->next->str);
		*curr_tok = (*curr_tok)->next;
	}
}

//Creates the command based on token of type WORD and stores it in the section
void	word_section(t_section **curr_sec, t_token **curr_tok)
{
	(*curr_sec)->cmd = create_command(curr_tok);
}

//Manages the creation of sections and connections when a separator is found
void	connection_section(t_section **curr_sec, t_token **curr_tok)
{
	if ((*curr_tok)->type == PIPE || (*curr_tok)->type == AND
		|| (*curr_tok)->type == OR)
	{
		if ((*curr_tok)->next->type == OPEN_BRACKET)
		{
			(*curr_sec)->inner = new_section(*curr_sec, NULL);
			(*curr_sec)->inner->outer_conn_type = (*curr_tok)->type;
			*curr_tok = (*curr_tok)->next;
			(*curr_sec) = (*curr_sec)->inner;
		}
		else
		{
			(*curr_sec)->next_conn_type = (*curr_tok)->type;
			(*curr_sec)->next = new_section(NULL, *curr_sec);
			*curr_sec = (*curr_sec)->next;
		}
	}
}
