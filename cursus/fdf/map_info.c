/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:21:35 by igarcia2          #+#    #+#             */
/*   Updated: 2024/03/27 20:31:19 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_iso_values(t_points *point)
{
	point->x_iso = point->x;
	point->y_iso = point->y;
	convert_isometric(&point->x_iso, &point->y_iso, point->z);
	//point->x_iso *= 30;
	//point->y_iso *= 30;
	ft_printf("x: %d, y: %d, z: %d, x_iso: %d, y_iso: %d, color: %d\n",
			point->x, point->y, point->z, point->x_iso, point->y_iso, point->color);
}

int	get_color(char *str, int z)
{
	int		color;
	int		i;
	char	*hexa;

	color = 0xFFFFFF;
	if (ft_strchr(str, ','))
	{
		i = 0;
		while (str[i] != ',')
			i++;
		hexa = ft_substr(str, i + 1, 8);
	}
	else if (z > 8)
		color = 0xFF2D00;
	else if (z > 5)
		color = 0xFFA600;
	else if (z > 2)
		color = 0x32FF00;
	return (color);
}

void	set_points_values(t_map *map)
{
	int		i;
	int		j;
	int		h;
	char	**line;

	i = 0;
	h = 0;
	while (map->map[i] != NULL)
	{
		j = 0;
		line = ft_split(map->map[i], ' ');
		if (!line)
			exit_error("ERROR");
		while (line[j] != NULL)
		{
			map->points[h].x = j * 30;
			map->points[h].y = i * 30;
			map->points[h].z = ft_atoi(line[j]) * 30;
			map->points[h].color = get_color(line[j], map->points[h].z);
			get_iso_values(&(map->points[h]));
			h++;
			j++;
		}
		i++;
	}
}

void	initialize_map_info(t_map *map)
{
	int		i;
	char	**line;

	i = 0;
	while (map->map[i])
		i++;
	map->height = i;
	i = 0;
	line = ft_split(map->map[i], ' ');
	if (!line)
		exit_error("ERROR");
	while (line[i])
		i++;
	map->width = i;
	map->points = malloc((map->width * map->height)
		* sizeof(t_points));
	if (!map->points)
		exit_error("ERROR");
	free(line);
	set_points_values(map);
}
