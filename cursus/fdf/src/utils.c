/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:14:20 by igarcia2          #+#    #+#             */
/*   Updated: 2024/04/03 18:37:34 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Print error and exit program
void	exit_error(char *error_msg)
{
	ft_printf("%s", error_msg);
	exit(0);
}

//Function that prints number in the rendering window
void	print_nbr(t_vars *vars, int x, int y, int nbr)
{
	char	*str;

	str = ft_itoa(nbr);
	mlx_string_put(vars->mlx, vars->win, x, y, NUMBER_COLOR, str);
	free (str);
}

//Function that prints text in the rendering window
void	print_str(t_vars *vars, int x, int y, char *str)
{
	mlx_string_put(vars->mlx, vars->win, x, y, TEXT_COLOR, str);
}
