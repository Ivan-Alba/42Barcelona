/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:52:55 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/21 18:32:02 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Manages the creation of a new section when a bracket is found
void	brack_sect(t_section **curr_sec, t_token **curr_tok, t_data *data)
{
	if ((*curr_tok)->type == OPEN_BRACKET)
	{
		(*curr_sec)->inner = new_section(*curr_sec, NULL, data);
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
void	files_sect(t_section **curr_sec, t_token **curr_tok)
{
	if ((*curr_tok)->type == IN_F || (*curr_tok)->type == OUT_F
		|| (*curr_tok)->type == OUT_AP_F || (*curr_tok)->type == HEREDOC)
	{
		ft_files_add(&(*curr_sec)->files, ft_files_new(
				ft_strdup((*curr_tok)->next->str), (*curr_tok)->type));
		*curr_tok = (*curr_tok)->next;
	}
}

//Creates the command based on token of type WORD and stores it in the section
void	word_sect(t_section **curr_sec, t_token **curr_tok, t_data *data)
{
	if ((*curr_sec)->cmd == NULL)
		(*curr_sec)->cmd = create_command(curr_tok, data);
	else
		(*curr_sec)->cmd = add_to_array(&(*curr_sec)->cmd, (*curr_tok)->str);
}

//Manages the creation of sections and connections when a separator is found
void	conn_sect(t_section **curr_sec, t_token **curr_tok, t_data *data)
{
	if ((*curr_tok)->type == PIPE || (*curr_tok)->type == AND
		|| (*curr_tok)->type == OR)
	{
		if ((*curr_tok)->next->type == OPEN_BRACKET)
		{
			(*curr_sec)->next_conn_type = (*curr_tok)->type;
			(*curr_sec)->next = new_section(NULL, *curr_sec, data);
			*curr_sec = (*curr_sec)->next;
			(*curr_sec)->inner = new_section(*curr_sec, NULL, data);
			(*curr_sec)->inner_conn_type = (*curr_tok)->type;
			(*curr_sec)->inner->outer_conn_type = (*curr_tok)->type;
			*curr_tok = (*curr_tok)->next;
			(*curr_sec) = (*curr_sec)->inner;
		}
		else
		{
			(*curr_sec)->next_conn_type = (*curr_tok)->type;
			(*curr_sec)->next = new_section(NULL, *curr_sec, data);
			*curr_sec = (*curr_sec)->next;
		}
	}
}
