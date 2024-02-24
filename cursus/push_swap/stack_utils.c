/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:59:51 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/24 14:20:07 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Returns the number of moves required to move a stack to a specific position.
int	calc_moves_stack(t_list **stack, int index)
{
	int		moves;
	t_list	*tmp;

	moves = 0;
	tmp = *stack;
	if (up_or_down(*stack, index))
	{
		while ((*stack)->index != index)
			*stack = (*stack)->next;
		while (*stack)
		{
			*stack = (*stack)->next;
			moves++;
		}
	}
	else
	{
		while ((*stack)->index != index)
		{
			moves++;
			*stack = (*stack)->next;
		}
	}
	*stack = tmp;
	return (moves);
}

//Calculates the moves it costs to move an item from one stack to another
void	preview_moves(t_list **stack_a, t_list **stack_b)
{
	int		mvs_a;
	int		mvs_b;
	int		idx_b;
	t_list	*tmp;

	tmp = *stack_a;
	while (*stack_a)
	{
		mvs_a = calc_moves_stack(&tmp, (*stack_a)->index);
		idx_b = search_previous_position((*stack_a)->index, *stack_b);
		mvs_b = calc_moves_stack(stack_b, idx_b);
		if ((up_or_down(tmp, (*stack_a)->index) && up_or_down(*stack_b, idx_b))
			|| (!up_or_down(tmp, (*stack_a)->index)
				&& !up_or_down(*stack_b, idx_b)))
		{
			if (mvs_a >= mvs_b)
				(*stack_a)->moves = mvs_a;
			else
				(*stack_a)->moves = mvs_b;
		}
		else
			(*stack_a)->moves = mvs_a + mvs_b;
		*stack_a = (*stack_a)->next;
	}
	*stack_a = tmp;
}

//Returns the index of the cheapest element to move from the stack
int	get_cheap_idx(t_list **stack_a)
{
	int		cheaper;
	int		min_moves;
	t_list	*tmp;

	tmp = *stack_a;
	min_moves = (*stack_a)->moves;
	cheaper = (*stack_a)->index;
	while (*stack_a)
	{
		if ((*stack_a)->moves < min_moves)
		{
			min_moves = (*stack_a)->moves;
			cheaper = (*stack_a)->index;
		}
		*stack_a = (*stack_a)->next;
	}
	*stack_a = tmp;
	return (cheaper);
}

//Fuction to free an stack
void	free_stack(t_list **stack)
{
	if (stack && *stack)
		ft_lstclear(stack);
	if (stack)
		free(stack);
	stack = NULL;
}
