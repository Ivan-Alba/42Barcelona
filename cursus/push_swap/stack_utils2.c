/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:51:53 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/22 18:53:53 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Returns the highest index on a stack
int	get_highest_index(t_list *stack)
{
	t_list	*tmp;
	int		highest;

	highest = 0;
	tmp = stack;
	while (stack)
	{
		if (stack->index > highest)
			highest = stack->index;
		stack = stack->next;
	}
	stack = tmp;
	return (highest);
}

//Moves stack to an specific position (index)
void	move_stack(int index, t_list **stack, char stack_id)
{
	if (up_or_down(*stack, index))
	{
		while ((*stack)->index != index)
		{
			if (stack_id == 'A')
				reverse_rotate_stack(stack, RRA);
			else
				reverse_rotate_stack(stack, RRB);
		}
	}
	else
	{
		while ((*stack)->index != index)
		{
			if (stack_id == 'A')
				rotate_stack(stack, RA);
			else
				rotate_stack(stack, RB);
		}
	}
}

//Returns 0 if better rotate (up) or 1 if better reverse rotate (down)
int	up_or_down(t_list *stack, int index)
{
	t_list	*tmp;
	int		count;

	count = 0;
	tmp = stack;
	while (stack->index != index)
	{
		count++;
		stack = stack->next;
	}
	stack = tmp;
	if (count < ft_lstsize(stack) / 2)
		return (0);
	return (1);
}

//Returns the highest index below the one received by parameter
int	search_previous_position(int index, t_list *stack)
{
	int		res;
	t_list	*tmp;

	tmp = stack;
	res = -1;
	if (index == 0)
		return (get_highest_index(stack));
	while (stack)
	{
		if (stack->index < index && res < stack->index)
			res = stack->index;
		stack = stack->next;
	}
	stack = tmp;
	if (res == -1)
		return (get_highest_index(stack));
	return (res);
}
