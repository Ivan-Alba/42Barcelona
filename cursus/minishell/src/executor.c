/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:24 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/22 20:25:29 by igarcia2         ###   ########.fr       */
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

//Manages the opening of fd's, creation of processes and execution of commands
void	executor(t_data *data)
{
	//GENERATE PIPES
	data->pipes = malloc(data->pipes_needed * 2 * sizeof(int));
	if (!data->pipes)
		print_error_exit(MALLOC_ERROR, data);
	generate_pipes(data);
	//TODO CREAMOS ARCHIVOS TEMPORALES HEREDOCS
	manage_heredocs(data);
	//TODO SET FD_IN Y FD_OUT DE CADA SECCION (NOT && or ||)

	//TODO EXECUTE FORK RECURSIVE INNER->NEXT 
}
