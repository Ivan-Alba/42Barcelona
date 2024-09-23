/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:31:40 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/23 13:09:13 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Receives an error message by parameter and prints it on console
void	print_error(char *msg, char	*token)
{
	if (!token)
	{
		write(2, PROGRAM_NAME, ft_strlen(PROGRAM_NAME));
		write(2, " ", 1);
		write(2, msg, ft_strlen(msg));
	}
	else
	{
		write(2, PROGRAM_NAME, ft_strlen(PROGRAM_NAME));
		write(2, " ", 1);
		write(2, msg, ft_strlen(msg));
		write(2, "'", 1);
		write(2, token, ft_strlen(token));
		write(2, "'", 1);
	}
	write(2, "\n", 2);
}

void	print_perror(char *msg)
{
	write(2, PROGRAM_NAME, ft_strlen(PROGRAM_NAME));
	write(2, " ", 1);
	if (msg && msg[0] == '\0')
		write(2, ": ", 2);
	perror(msg);
}

void	print_ambiguous_error(char *str)
{
	write(2, PROGRAM_NAME, ft_strlen(PROGRAM_NAME));
	write(2, " ", 1);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, AMBIGUOUS_ERROR, ft_strlen(AMBIGUOUS_ERROR));
	write(2, "\n", 1);
}

//Receives an error message by parameter and prints it on console and exits
void	print_error_exit(char *msg, t_data *data)
{
	if (msg)
	{
		write(2, PROGRAM_NAME, ft_strlen(PROGRAM_NAME));
		write(2, " ", 1);
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	free_data(data);
	exit(1);
}
