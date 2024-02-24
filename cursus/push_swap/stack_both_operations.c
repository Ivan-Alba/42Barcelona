/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_both_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:38:54 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/23 16:04:16 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Rotate both stacks (rr)
void	rotate_both_stacks(t_list **stack_a, t_list **stack_b, char *order)
{
	rotate_stack(stack_a, NULL);
	rotate_stack(stack_b, NULL);
	protected_write(order, 3);
}

//Reverse rotate both stacks (rrr)
void	rev_rotate_both_stacks(t_list **stack_a, t_list **stack_b, char *order)
{
	reverse_rotate_stack(stack_a, NULL);
	reverse_rotate_stack(stack_b, NULL);
	protected_write(order, 4);
}

//Swaps the first two elements of both stacks (ss)
void	swap_both_stacks(t_list **stack_a, t_list **stack_b, char *order)
{
	swap_stack(stack_a, NULL);
	swap_stack(stack_b, NULL);
	protected_write(order, 3);
}
