/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:14:20 by igarcia2          #+#    #+#             */
/*   Updated: 2024/04/05 18:55:02 by igarcia2         ###   ########.fr       */
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

//Function that transforms a char * hexadecimal to int
int	hex_to_int(char *hex)
{
	int		res;
	int		i;
	char	c;
	int		decimal;

	i = 0;
	res = 0;
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		i = 2;
	while (hex[i] != '\0')
	{
		c = hex[i];
		if (c >= '0' && c <= '9')
			decimal = c - '0';
		else if (c >= 'a' && c <= 'f')
			decimal = 10 + c - 'a';
		else if (c >= 'A' && c <= 'F')
			decimal = 10 + c - 'A';
		res = res * 16 + decimal;
		i++;
	}
	return (res);
}

//Function that frees a pointer of string pointers
void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
