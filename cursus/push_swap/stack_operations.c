/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:43:49 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/23 16:05:18 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Swaps the first two elements of a stack (sa/sb)
void	swap_stack(t_list **stack, char *order)
{
	t_list	*tmp;

	if (ft_lstsize(*stack) < 2)
		return ;
	tmp = ((*stack)->next)->next;
	((*stack)->next)->next = *stack;
	*stack = (*stack)->next;
	((*stack)->next)->next = tmp;
	protected_write(order, 3);
}

//Moves an element from the src stack to the dst stack (pa/pb)
void	push_stack(t_list **stack_src, t_list **stack_dst, char *order)
{
	t_list	*tmp;

	if (!stack_src || !(*stack_src))
		return ;
	tmp = (*stack_src)->next;
	(*stack_src)->next = NULL;
	ft_lstadd_front(stack_dst, *stack_src);
	*stack_src = tmp;
	protected_write(order, 3);
}

//Rotates down all elements of the stack (ra/rb)
void	rotate_stack(t_list **stack, char *order)
{
	t_list	*tmp;

	if (ft_lstsize(*stack) <= 1)
		return ;
	tmp = *stack;
	*stack = (*stack)->next;
	tmp->next = NULL;
	ft_lstadd_back(stack, tmp);
	protected_write(order, 3);
}

//Rotates down all elements of the stack (rra/rrb)
void	reverse_rotate_stack(t_list **stack, char *order)
{
	t_list	*tmp;
	int		size;

	size = ft_lstsize(*stack);
	if (size <= 1)
		return ;
	tmp = ft_lstlast(*stack);
	tmp->next = NULL;
	ft_lstadd_front(stack, tmp);
	*stack = tmp;
	while (size-- > 1)
		*stack = (*stack)->next;
	(*stack)->next = NULL;
	*stack = tmp;
	protected_write(order, 4);
}
