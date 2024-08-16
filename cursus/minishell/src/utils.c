/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:28:42 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/16 21:16:05 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Receives an error message by parameter and prints it on console
void	print_error(char *msg, char	*token)
{
	if (!token)
		ft_printf("%s\n", msg);
	else
		ft_printf("%s \'%s\'\n", msg, token);
}

//Receives an error message by parameter and prints it on console and exits
void	print_error_exit(char *msg, t_data *data)
{
	ft_printf("%s\n", msg);
	free_data(data);
	exit(1);
}

//(TEST) Receives a char** as a parameter and prints its content by console
void	print_split(char **splitted)
{
	int	i;

	i = 0;
	if (splitted)
	{
		while (splitted[i])
		{
			ft_printf("[%d]: %s\n", i, splitted[i]);
			i++;
		}
	}
}

//(TEST) Prints the content of each node of a list of type t_section
void	print_sections(t_section *section)
{
	if (!section)
		return ;
	printf("---SECTION---\n");
	while (section)
	{
		printf("CMD: \n");
		print_split(section->cmd);
		printf("infiles:\n");
		print_split(section->infiles);
		printf("outfiles:\n");
		print_split(section->outfiles);
		printf("outfiles_app:\n");
		print_split(section->outfiles_app);
		printf("heredocs:\n");
		print_split(section->heredocs);
		//print_sections(section->inner);
		printf("next_conn_type %d\n", section->next_conn_type);
		//print_sections(section->next);
		section = section->next;
	}
}
