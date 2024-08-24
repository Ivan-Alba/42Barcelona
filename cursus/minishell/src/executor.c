/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:24 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/23 19:58:46 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Create the necessary pipes for communication between processes
void	generate_pipes(t_data *data)
{
	int	i;

	if (data->section_id - 1 > 0)
	{
		data->pipes = malloc((data->section_id - 1) * 2 * sizeof(int));
		if (!data->pipes)
			print_error_exit(MALLOC_ERROR, data);
	}

	i = 0;
	while (i < data->section_id -1)
	{
		if (pipe(data->pipes + 2 * i) == -1)
			print_error_exit(PIPES_ERROR, data);
		i++;
	}
}

void	execute(t_data *data)
{
	t_section	*curr_sec;

	curr_sec = data->sections;
	//TODO EXECUTE ALL SECTIONS ONLY CONNECTED BY PIPE
	while (curr_sec)
	{
		//TODO PRINT TEST
		printf("\nSECTION %d EXPANSION\n", curr_sec->id);
		expand_vars(curr_sec, data);
		curr_sec = get_next_pipe_section(curr_sec, data->section_id - 1);
	}
}
//Manages the opening of fd's, creation of processes and execution of commands
void	executor(t_data *data)
{
	//GENERATE PIPES
	generate_pipes(data);
	//TODO CREAMOS ARCHIVOS TEMPORALES HEREDOCS
	manage_heredocs(data);	
	//TODO EXECUTE FORK RECURSIVE INNER->NEXT
	execute(data);
		//TODO SET FD_IN Y FD_OUT DE CADA SECCION (NOT && or ||)
}
