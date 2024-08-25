/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate_sections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:55:08 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/22 20:22:26 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * Function Name: get_next_section 
 *
 *	Description:
 *		This function receives a node from a list t_section and returns the
 *		following node.
 *		Priority to inner nodes and then next nodes.
 *
 *	Parameters:
 *		t_section* current - The pointer to the initial node.
 *		int last_section_id - The id of the last node to know its end.
 *
 *	Return Value:
 *		t_section*	- The next node to the one received as a parameter.
 *		NULL		- If the list has ended.
 */
t_section	*get_next_section(t_section *current, int last_section_id)
{
	if (current->inner)
		return (current->inner);
	else if (current->next)
		return (current->next);
	else if (current->id == last_section_id)
		return (NULL);
	while (1)
	{
		if (current->next)
			return (current->next);
		while (current->previous)
			current = current->previous;
		if (current->outer)
			current = current->outer;
	}
}

/**
 * Function Name: get_next_pipe_section 
 *
 *	Description:
 *		This function receives a node from a list t_section and returns the
 *		following node if connected with a pipe '|'.
 *		Priority to inner nodes and then next nodes.
 *
 *	Parameters:
 *		t_section* current - The pointer to the initial node.
 *		int last_section_id - The id of the last node to know its end.
 *
 *	Return Value:
 *		t_section*	- The next node to the one received as a parameter.
 *		NULL		- If it does not meet the connection type or the list has ended.
 */
t_section	*get_next_pipe_section(t_section *current)
{
	/*if (current->inner && current->in_conn != AND && current->in_conn != OR)
		return (current->inner);
	else if (current->inner)
		return (NULL);*/
	if (current->next && current->next_conn != AND
		&& current->next_conn != OR)
		return (current->next);
	else
		return (NULL);
	/*while (1)
	{
		if (current->next && current->next_conn != AND
			&& current->next_conn != OR)
			return (current->next);
		else if (current->next)
			return (NULL);
		while (current->previous)
			current = current->previous;
		if (current->outer)
			current = current->outer;
	}*/
}
