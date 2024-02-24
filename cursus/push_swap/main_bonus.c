/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:59:14 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/24 14:21:22 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Calls the necessary function to make changes on stack
void	do_operation(char *order, t_list **stack_a, t_list **stack_b)
{
	if (ft_strcmp(order, PA))
		push_stack(stack_b, stack_a, NULL);
	else if (ft_strcmp(order, PB))
		push_stack(stack_a, stack_b, NULL);
	else if (ft_strcmp(order, SA))
		swap_stack(stack_a, NULL);
	else if (ft_strcmp(order, SB))
		swap_stack(stack_b, NULL);
	else if (ft_strcmp(order, RA))
		rotate_stack(stack_a, NULL);
	else if (ft_strcmp(order, RB))
		rotate_stack(stack_b, NULL);
	else if (ft_strcmp(order, RRA))
		reverse_rotate_stack(stack_a, NULL);
	else if (ft_strcmp(order, RRB))
		reverse_rotate_stack(stack_b, NULL);
	else if (ft_strcmp(order, RR))
		rotate_both_stacks(stack_a, stack_b, NULL);
	else if (ft_strcmp(order, RRR))
		rev_rotate_both_stacks(stack_a, stack_b, NULL);
	else if (ft_strcmp(order, SS))
		swap_both_stacks(stack_a, stack_b, NULL);
	else
		free_both_stacks(stack_a, stack_b);
}

//Read the orders from fd 0 and apply changes to stack
void	read_orders(t_list **stack_a)
{
	char	*next;
	t_list	**stack_b;

	stack_b = ft_calloc(1, sizeof(t_list *));
	if (!stack_b)
	{
		free_stack(stack_a);
		free_and_exit(NULL);
	}
	next = get_next_line(0);
	if (next != NULL)
		do_operation(next, stack_a, stack_b);
	while (next)
	{
		free(next);
		next = get_next_line(0);
		if (next)
			do_operation(next, stack_a, stack_b);
	}
	free_stack(stack_b);
}

//Main function of checker (bonus)
int	main(int argc, char *argv[])
{
	int		count;
	int		*array;
	t_list	**stack_a;

	if (argc == 1)
		return (0);
	array = check_args(argc, argv, &count);
	stack_a = create_stack(&array, count);
	free(array);
	read_orders(stack_a);
	if (is_sorted(stack_a, count))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_stack(stack_a);
	return (0);
}
