/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:30:27 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/19 12:39:22 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*prompt;

	(void)argv;
	if (argc != 1)
		print_error_exit("Error: no args required", NULL);
	data = malloc(sizeof(t_data *));
	if (!data)
		print_error_exit("Error: allocating memory", NULL);
	data->env = env;
	while (1)
	{
		prompt = readline("minishell: ");
		prompt = prompt;
	}
}
