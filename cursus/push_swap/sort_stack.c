/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:58:52 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/23 15:52:05 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Returns all elements of stack b to the main stack
void	get_all_stack_b(t_list **stack_a, t_list **stack_b, int count)
{
	int	max_mv;

	max_mv = 3;
	if (count == 4)
		max_mv = 2;
	move_stack(get_highest_index(*stack_b), stack_b, 'B');
	if ((ft_lstlast(*stack_a))->index == count - 1)
	{
		reverse_rotate_stack(stack_a, RRA);
		max_mv--;
	}
	while (ft_lstlast(*stack_a)->index == (*stack_a)->index - 1 && max_mv-- > 0)
		reverse_rotate_stack(stack_a, RRA);
	while (*stack_b)
	{
		if (ft_lstlast(*stack_a)->index == (*stack_b)->index + 1
			&& max_mv-- > 0)
			reverse_rotate_stack(stack_a, RRA);
		while (ft_lstlast(*stack_a)->index == (*stack_a)->index - 1
			&& max_mv-- > 0)
			reverse_rotate_stack(stack_a, RRA);
		push_stack(stack_b, stack_a, PA);
	}
	while (max_mv-- > 0)
		reverse_rotate_stack(stack_a, RRA);
}

//Sort last numbers of the main stack 
void	sort_last_three(t_list **stack_a)
{
	if ((*stack_a)->index > ((*stack_a)->next)->index
		&& (*stack_a)->index > (((*stack_a)->next)->next)->index)
	{
		rotate_stack(stack_a, RA);
		if ((*stack_a)->index > ((*stack_a)->next)->index)
			swap_stack(stack_a, SA);
	}
	else if ((*stack_a)->index > ((*stack_a)->next)->index)
		swap_stack(stack_a, SA);
	else if ((*stack_a)->index > (ft_lstlast(*stack_a))->index)
		reverse_rotate_stack(stack_a, RRA);
	else if (((*stack_a)->next)->index > (ft_lstlast(*stack_a))->index)
	{
		reverse_rotate_stack(stack_a, RRA);
		swap_stack(stack_a, SA);
	}
}

//When there are 3 or less elements left in the stack we call this function
void	finish_sort(t_list **stack_a, t_list **stack_b, int count)
{
	if (count == 2)
		swap_stack(stack_a, SA);
	else if (count == 3)
		sort_last_three(stack_a);
	else if (count == 4)
		if ((*stack_a)->index > ((*stack_a)->next)->index)
			swap_stack(stack_a, SA);
	if (count > 3)
	{
		sort_last_three(stack_a);
		get_all_stack_b(stack_a, stack_b, count);
	}
}

//Move both stacks to the necessary position to push a specific index
void	move_stacks(t_list **stack_a, t_list **stack_b, int idx)
{
	int	pos_b;

	pos_b = search_previous_position(idx, *stack_b);
	if (up_or_down(*stack_a, idx) && up_or_down(*stack_b, pos_b))
	{
		while ((*stack_a)->index != idx && (*stack_b)->index != pos_b)
			rev_rotate_both_stacks(stack_a, stack_b, RRR);
	}
	else if (!up_or_down(*stack_a, idx) && !up_or_down(*stack_b, pos_b))
	{
		while ((*stack_a)->index != idx && (*stack_b)->index != pos_b)
			rotate_both_stacks(stack_a, stack_b, RR);
	}
	if ((*stack_a)->index != idx)
		move_stack(idx, stack_a, 'A');
	if ((*stack_b)->index != pos_b)
		move_stack(pos_b, stack_b, 'B');
}

//Function in charge of sorting the stack by calling other functions
void	sort_stack(t_list **stack_a, int count)
{
	t_list	**stack_b;
	int		cheap_idx;

	if (count <= 3)
	{
		finish_sort(stack_a, NULL, count);
		return ;
	}
	stack_b = ft_calloc(sizeof(t_list *), 1);
	if (!stack_b)
		free_and_exit(*stack_a);
	push_stack(stack_a, stack_b, PB);
	push_stack(stack_a, stack_b, PB);
	while (ft_lstsize(*stack_a) > 3)
	{
		preview_moves(stack_a, stack_b);
		cheap_idx = get_cheap_idx(stack_a);
		move_stacks(stack_a, stack_b, cheap_idx);
		push_stack(stack_a, stack_b, PB);
	}
	finish_sort(stack_a, stack_b, count);
	free(stack_b);
	stack_b = NULL;
}
