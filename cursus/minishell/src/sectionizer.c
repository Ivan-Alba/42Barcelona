/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectionizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:38:59 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/16 21:20:21 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Add to an existing char** a new value, freeing the memory and re-allocating it
char	**add_to_array(char	***current, char *new_value)
{
	char	**new;
	int		i;

	if (!(*current) || !(*current)[0])
		new = malloc(sizeof(char *) * 2);
	else
	{
		i = 0;
		while (*current && (*current)[i])
			i++;
		new = malloc(sizeof(char *) * (i + 2));
	}
	//TODO check malloc error
	if (!new)
		return (NULL);
	i = 0;
	while (*current && (*current)[i])
	{
		new[i] = ft_strdup((*current)[i]);
		i++;
	}
	new[i++] = ft_strdup(new_value);
	new[i] = NULL;
	if (*current)
		free_split(current);
	return (new);
}

//Creates the commands in the format necessary for their execution
char	**create_command(t_token **first)
{
	char	**command;
	t_token	*current;

	current = *first;
	command = NULL;
	while (current && current->type == WORD)
	{
		command = add_to_array(&command, current->str);
		//TODO check malloc error
		if (command == NULL)
			return (NULL);
		if (current->next && current->next->type == WORD)
			*first = (*first)->next;
		current = current->next;
	}
	return (command);
}

//Creates a new node of type t_section * and initializes its values
t_section	*new_section(t_section *outer, t_section *previous)
{
	t_section	*new;

	new = malloc(sizeof(t_section));
	//TODO check malloc error
	if (!new)
		return (NULL);
	if (outer)
		new->outer = outer;
	if (previous)
		new->previous = previous;
	new->cmd = NULL;
	new->next = NULL;
	new->next_conn_type = 0;
	new->inner = NULL;
	new->outer_conn_type = 0;
	new->outfiles = NULL;
	new->outfiles_app = NULL;
	new->infiles = NULL;
	new->heredocs = NULL;
	return (new);
}

/*void	*get_type_function(enum	e_token_type type)
{
	
}*/

//Manages the creation of t_section list with the information of the t_token list
void	sectionizer(t_data *data)
{
	t_token		*curr_tok;
	t_section	*curr_sec;

	curr_tok = data->tokens;
	curr_sec = NULL;
	if (curr_tok)
	{
		curr_sec = new_section(NULL, NULL);
		data->sections = curr_sec;
	}
	while (curr_tok)
	{
		if (curr_tok->type == OPEN_BRACKET)
		{
			curr_sec->inner = new_section(curr_sec, NULL);
			curr_sec->inner->outer = curr_sec;
			curr_sec = curr_sec->inner;
		}
		else if (curr_tok->type == CLOSE_BRACKET)
			curr_sec = curr_sec->outer;
		else if (curr_tok->type == IN_F)
		{
			curr_sec->infiles = add_to_array(&curr_sec->infiles, curr_tok->next->str);
			curr_tok = (curr_tok->next);
		}
		else if (curr_tok->type == OUT_F)
		{
			curr_sec->outfiles = add_to_array(&curr_sec->outfiles, curr_tok->next->str);
			curr_tok = (curr_tok->next);
		}
		else if (curr_tok->type == OUT_AP_F)
		{
			curr_sec->outfiles_app = add_to_array(&curr_sec->outfiles_app, curr_tok->next->str);
			curr_tok = (curr_tok->next);
		}
		else if (curr_tok->type == HEREDOC)
		{
			curr_sec->heredocs = add_to_array(&curr_sec->heredocs, curr_tok->next->str);
			curr_tok = (curr_tok->next);
		}
		else if (curr_tok->type == WORD)
			curr_sec->cmd = create_command(&curr_tok);
		//TODO Outer conn_type
		else if (curr_tok->type == PIPE || curr_tok->type == AND || curr_tok->type == OR)
		{
			if (curr_tok->next->type == OPEN_BRACKET)
			{
				curr_sec->inner = new_section(curr_sec, NULL);
				curr_sec->inner->outer_conn_type = curr_tok->type;
				curr_tok = curr_tok->next;
			}
			else
			{
				curr_sec->next_conn_type = curr_tok->type;
				curr_sec->next = new_section(NULL, curr_sec);
				curr_sec = curr_sec->next;
			}
		}
		if (curr_tok)
			curr_tok = curr_tok->next;
	}
}
