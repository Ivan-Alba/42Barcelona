/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:28:42 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/13 16:47:38 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_error(char *msg, char	*token)
{
	if (!token)
		ft_printf("%s\n", msg);
	else
		ft_printf("%s \'%s\'\n", msg, token);
}

void	print_error_exit(char *msg, t_data *data)
{
	ft_printf("%s\n", msg);
	free_data(data);
	exit(1);
}

void	print_split(char **splitted)
{
	int	i;

	i = 0;
	if (splitted)
	{
		while (splitted[i])
		{
			ft_printf("%s\n", splitted[i]);
			i++;
		}
	}
}
