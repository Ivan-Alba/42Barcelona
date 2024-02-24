/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:53:35 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/24 14:52:40 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Compare two char *. Returns 1 (true) if same content or 0 (false) if not
int	ft_strcmp(char *next, char *order)
{
	int	i;

	i = 0;
	while (next[i] != '\0')
	{
		if (next[i] != order[i])
			return (0);
		i++;
	}
	return (1);
}

//Returns 1 (true) when the stack are sorted or 0 (false) if not
int	is_sorted(t_list **stack_a, int count)
{
	t_list	*tmp;

	tmp = *stack_a;
	if (ft_lstsize(*stack_a) != count)
		return (0);
	while (*stack_a)
	{
		if (!(*stack_a)->next)
			break ;
		else
		{
			if ((*stack_a)->index > ((*stack_a)->next)->index)
			{
				*stack_a = tmp;
				return (0);
			}
		}
		*stack_a = (*stack_a)->next;
	}
	*stack_a = tmp;
	return (1);
}

//Fuction to free both stacks
void	free_both_stacks(t_list **stack_a, t_list **stack_b)
{
	free_stack(stack_a);
	free_stack(stack_b);
	write(2, ERROR_MSG, sizeof(ERROR_MSG));
	exit(0);
}
