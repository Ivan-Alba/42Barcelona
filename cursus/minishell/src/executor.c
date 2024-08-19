/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:24 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/19 15:55:45 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Create the necessary pipes for communication between processes
void	generate_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipes_needed)
	{
		if (pipe(data->pipes + 2 * i) == -1)
			print_error_exit(PIPES_ERROR, data);
		i++;
	}
}

void	executor(t_data *data)
{
	//TODO GENERATE PIPES
	data->pipes = malloc(data->pipes_needed * 2 * sizeof(int));
	if (!data->pipes)
		print_error_exit(MALLOC_ERROR, data);
	generate_pipes(data);
	//TODO HEREDOCS
	
	//TODO OPEN FDS (NOT && or ||)
	
	//TODO EXECUTE FORK RECURSIVE INNER->NEXT 
}
