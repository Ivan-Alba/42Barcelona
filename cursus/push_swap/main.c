/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 20:04:01 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/22 19:53:52 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Main function
int	main(int argc, char *argv[])
{
	int				count;
	int				*array;
	t_list			**stack_a;

	if (argc == 1)
		return (0);
	array = check_args(argc, argv, &count);
	stack_a = create_stack(&array, count);
	free(array);
	sort_stack(stack_a, count);
	free_stack(stack_a);
	return (0);
}
