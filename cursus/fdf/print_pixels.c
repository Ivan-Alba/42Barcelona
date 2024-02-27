/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pixels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:38:19 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/27 18:26:17 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	print_x(char **map, t_data *img, int i, int j)
{
	int	current_pixel;

	my_mlx_pixel_put(img, j * 30, i * 30, 0xFFFFFF);
	current_pixel = j * 30;
	if (map[i][j + 1] != '\0')
	{
		while (++current_pixel < (j + 1) * 30)
		{
			my_mlx_pixel_put(img, current_pixel, i * 30, 0xFFFFFF);
		}
	}
}

void	print_y(char **map, t_data *img, int i, int j)
{
	int	current_pixel;
	long	colour;

	colour = 0xFFFFFFF;
	my_mlx_pixel_put(img, j * 30, i * 30, 0xFFFFFF);
	current_pixel = i * 30;
	if (map[i + 1] != NULL && map[i + 1][j] != '\0')
	{
		while (++current_pixel < (i + 1) * 30)
		{
			my_mlx_pixel_put(img, j * 30, current_pixel, colour);
		}
	}
	
}

void	print_pixels(t_data *img, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			print_x(map, img, i, j);
			print_y(map, img, i, j);
			j++;
		}
		i++;
	}
}
