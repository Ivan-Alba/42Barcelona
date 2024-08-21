/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectionizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:38:59 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/21 17:09:04 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Creates the commands in the format necessary for their execution
char	**create_command(t_token **first, t_data *data)
{
	char	**command;
	t_token	*current;

	current = *first;
	command = NULL;
	while (current && current->type == WORD)
	{
		command = add_to_array(&command, current->str);
		if (command == NULL)
			return (print_error_exit(MALLOC_ERROR, data), NULL);
		if (current->next && current->next->type == WORD)
			*first = (*first)->next;
		current = current->next;
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
	new->next = NULL;
	new->next_conn_type = -1;
	new->inner = NULL;
	new->inner_conn_type = -1;
	new->outer_conn_type = -1;
	new->files = NULL;
	return (new);
}

//Counts the number of pipes necessary to execute the prompt
void	count_pipes_heredocs(t_section *curr_sec, t_data *data)
{
	t_files	*current;

	if (!curr_sec)
		return ;
	count_pipes_heredocs(curr_sec->inner, data);
	count_pipes_heredocs(curr_sec->next, data);
	current = curr_sec->files;
	while (current)
	{
		if (current->file_type == HEREDOC)
			data->pipes_needed += 1;
		current = current->next;
	}
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
			files_sect(&curr_sec, &curr_tok);
		else if (curr_tok->type == WORD)
			curr_sec->cmd = create_command(&curr_tok, data);
		else if (curr_tok->type == PIPE || curr_tok->type == AND
			|| curr_tok->type == OR)
			conn_sect(&curr_sec, &curr_tok, data);
		if (curr_tok)
			curr_tok = curr_tok->next;
	}
	count_pipes_heredocs(data->sections, data);
}
