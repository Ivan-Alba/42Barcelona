/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pixels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:38:19 by igarcia2          #+#    #+#             */
/*   Updated: 2024/03/27 20:29:39 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void convert_isometric(int *x, int *y, int z)
{
    *x = (*x - *y) * cos(1);
    *y = (*x + *y) * sin(1) - z;
}

void	putpixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	round_float(float num)
{
	if (num - (int) num >= 0.5)
		return ((int) num + 1);
	return ((int) num);
}

void	print_lines(t_data *data, t_points point1, t_points point2)
{
	int		max;
	int		x;
	int		y;
	int		i;

	if (abs(point2.x_iso - point1.x_iso) > abs(point2.y_iso - point1.y_iso))
		max = abs(point2.x_iso - point1.x_iso);
	else
		max = abs(point2.y_iso - point1.y_iso);
	if (max > 0)
	{
		x = point1.x_iso + ((point2.x_iso - point1.x_iso) / max);
		y = point1.y_iso + ((point2.y_iso - point1.y_iso) / max);
		i = 0;
		while (i < max)
		{
			putpixel(data, round_float(x) + 500, round_float(y) + 500, 0xFFFFFF);
			x = x + ((point2.x_iso - point1.x_iso) / max);
			y = y + ((point2.y_iso - point1.y_iso) / max);
			i++;
		}
	}
}

//Function that prints the pixels on the screen based on the map
void	print_pixels(t_data *data, t_map *map)
{
	int			i;

	i = 0;
	while (i < map->width * map->height)
	{
		putpixel(data, map->points[i].x_iso + 500, 
			map->points[i].y_iso + 500, map->points[i].color);
		//Miramos si hay punto al lado para unir
		if ((i + 2) < (map->width * map->height) && (i + 1) % 19 != 0)
		{
			print_lines(data, map->points[i], map->points[i + 1]);
		}
		//Miramos si hay punto debajo para unir
		if (i + map->width < map->width * map->height)
		{
			print_lines(data, map->points[i], map->points[i + map->width]);
		}
		i++;
	}
}
