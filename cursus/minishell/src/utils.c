/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:28:42 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/19 13:52:26 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_split(char **splitted)
{
	int i;

	i = 0;
	if (splitted)
	{
		while (splitted[i])
		{
			free(splitted[i]);
			i++;
		}
		free(splitted);
	}
}

void	free_data(t_data *data)
{
	if (data)
		free(data);
}

void	print_error_exit(char *msg, t_data *data)
{
	ft_printf("%s\n", msg);
	free_data(data);
	exit(1);
}
