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

#include "../../inc/minishell.h"

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
	if (current)
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
	return (NULL);
}

/**
 * Function Name: get_next_fdin_section 
 *
 *	Description:
 *		This function receives a node from the t_section list and traverses
 *		the outter nodes looking for an input file fd or a PIPE
 *		connection.
 *
 *	Parameters:
 *		t_section* current - The pointer to the initial node.
 *
 *	Return Value:
 *		t_section*	- The pointer to the t_section node that contains an input
 *						file fd or a PIPE connection.
 *		NULL		- If it does not find any section that meets the
 *						conditions.
 */
t_section	*get_outer_fdin_section(t_section *current)
{
	if (current)
	{
		while (current->outer)
		{
			if (current->outer->fd_in != -1)
				return (current->outer);
			if (current->outer->previous
				&& current->outer->previous->next_conn == PIPE)
				return (current->outer);
			current = current->outer;
		}
	}
	return (NULL);
}

/**
 * Function Name: get_next_fdout_section 
 *
 *	Description:
 *		This function receives a node from the t_section list and traverses
 *		the previous and outter nodes looking for an output file fd or a PIPE
 *		connection.
 *
 *	Parameters:
 *		t_section* current - The pointer to the initial node.
 *
 *	Return Value:
 *		t_section*	- The pointer to the t_section node that contains an output
 *						file fd or a PIPE connection.
 *		NULL		- If it does not find any section that meets the
 *						conditions.
 */
t_section	*get_outer_fdout_section(t_section *current)
{
	if (current)
	{
		while (current->previous || current->outer)
		{
			while (current->previous)
				current = current->previous;
			if (!current->outer)
				return (NULL);
			if (current->outer->fd_out != -1
				|| current->outer->next_conn == PIPE)
				return (current->outer);
			current = current->outer;
		}
	}
	return (NULL);
}

/**
 * Function Name: get_next_pipe_section 
 *
 *	Description:
 *		This function receives a node from a list t_section and returns the
 *		following node if connected with a pipe '|'.
 *		Only nodes connectes by next pointer (not inner).
 *
 *	Parameters:
 *		t_section* current - The pointer to the initial node.
 *		int last_section_id - The id of the last node to know its end.
 *
 *	Return Value:
 *		t_section*	- The next node to the one received as a parameter.
 *		NULL		- If it does not meet the connection type or the list
 *						has ended.
 */
t_section	*get_next_pipe_section(t_section *current)
{
	if (current->next && current->next_conn != AND
		&& current->next_conn != OR)
		return (current->next);
	else
		return (NULL);
}

t_section	*get_outest_section(t_section *section)
{
	t_section	*current;

	current = section;
	if (current->outer)
	{
		while (current->outer)
			current = current->outer;
		return (current);
	}
	else
		return (NULL);
}
