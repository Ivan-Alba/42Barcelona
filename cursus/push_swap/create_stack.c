/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:22:53 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/14 15:53:26 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Sort array with bubble to store index in lists
void	order_array(int **array, int count)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if ((*array)[i] > (*array)[j])
			{
				tmp = (*array)[j];
				(*array)[j] = (*array)[i];
				(*array)[i] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < count)
		i++;
}

//We append the index value to the list elements
void	add_index(t_list **stack_a, int **array, int count)
{
	int		i;
	t_list	*current;

	i = 0;
	current = (*stack_a);
	while (i < count)
	{
		while ((*array)[i] != current -> value)
			current = current -> next;
		current -> index = i;
		current = (*stack_a);
		i++;
	}
}

//We initialize the stack_a with all the values of the args
t_list	**create_stack(int **array, int count)
{
	t_list	**stack_a;
	int		i;

	i = 0;
	stack_a = malloc(sizeof(t_list *));
	if (!stack_a)
		free_and_exit(*array);
	while (i < count)
	{
		ft_lstadd_back(stack_a, ft_lstnew((*array)[i]));
		i++;
	}
	order_array(array, count);
	add_index(stack_a, array, count);
	return (stack_a);
}
