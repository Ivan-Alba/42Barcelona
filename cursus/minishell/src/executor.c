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
	t_section	*curr_sect;

	curr_sect = data->sections;
	while (curr_sec)
	{
		expand_vars(curr_sec, t_data *data);
		if(curr_sec->inner && curr_sec->inner_conn_type != AND
			&& curr_sec->inner_conn_type != OR)
			curr_sec = get_next_section(curr_sec, data->section_id - 1);
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
		//TODO EXPAND VARS
}
