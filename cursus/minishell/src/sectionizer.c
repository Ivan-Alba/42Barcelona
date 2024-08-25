/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectionizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:38:59 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/22 20:13:11 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Creates the commands in the format necessary for their execution
char	**create_command(t_token **first, t_data *data)
{
	char	**command;

	command = NULL;
	while (*first && (*first)->type == WORD)
	{
		command = add_to_array(&command, (*first)->str);
		if (!command)
			return (print_error_exit(MALLOC_ERROR, data), NULL);
		if ((*first)->next && (*first)->next->type == WORD)
			*first = (*first)->next;
		else
			break ;
	}
	return (command);
}

//Creates a new node of type t_section * and initializes its values
t_section	*new_section(t_section *outer, t_section *previous, t_data *data)
{
	t_section	*new;

	new = malloc(sizeof(t_section));
	if (!new)
		return (print_error_exit(MALLOC_ERROR, data), NULL);
	new->outer = NULL;
	new->previous = NULL;
	if (outer)
		new->outer = outer;
	if (previous)
		new->previous = previous;
	new->id = data->section_id++;
	new->cmd = NULL;
	new->cmd_path = NULL;
	new->next = NULL;
	new->next_conn = -1;
	new->inner = NULL;
	new->in_conn = -1;
	new->out_conn = -1;
	new->fd_in = -1;
	new->fd_out = -1;
	new->files = NULL;
	return (new);
}

//Manages creation of t_section list with the information of the t_token list
void	sectionizer(t_data *data)
{
	t_token		*curr_tok;
	t_section	*curr_sec;

	curr_tok = data->tokens;
	if (curr_tok)
	{
		curr_sec = new_section(NULL, NULL, data);
		data->sections = curr_sec;
	}
	while (curr_tok)
	{
		if (curr_tok->type == OPEN_BRACKET || curr_tok->type == CLOSE_BRACKET)
			brack_sect(&curr_sec, &curr_tok, data);
		else if (curr_tok->type == IN_F || curr_tok->type == OUT_F
			|| curr_tok->type == OUT_AP_F || curr_tok->type == HEREDOC)
			files_sect(&curr_sec, &curr_tok, data);
		else if (curr_tok->type == WORD)
			word_sect(&curr_sec, &curr_tok, data);
		else if (curr_tok->type == PIPE || curr_tok->type == AND
			|| curr_tok->type == OR)
			conn_sect(&curr_sec, &curr_tok, data);
		if (curr_tok)
			curr_tok = curr_tok->next;
	}
}
