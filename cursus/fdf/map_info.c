/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:21:35 by igarcia2          #+#    #+#             */
/*   Updated: 2024/04/02 18:21:24 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_iso_values(t_points *point)
{
	point->x_iso = point->x;
	point->y_iso = point->y;
	convert_isometric(&point->x_iso, &point->y_iso, point->z);
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

void	set_points_values(t_map *map, t_vars *vars)
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
			map->points[h].x = j * vars->scale;
			map->points[h].y = i * vars->scale;
			map->points[h].z = ft_atoi(line[j]) * vars->scale;
			map->points[h].color = get_color(line[j], map->points[h].z);
			get_iso_values(&(map->points[h]));
			h++;
			j++;
		}
		i++;
	}
}

/*void	initialize_img_settings (t_vars *vars)
{
	vars->scale = INIT_SCALE;
	while (vars->scale * map->width < WIN_X / 3)
		vars->scale += 1;
	while (vars->scale * map->width > WIN_X / 3)
		vars->scale -= 1;
}*/

void	initialize_map_info(t_map *map, t_vars *vars)
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
	vars->scale = 30;
	while (vars->scale * map->width < WIN_X / 3)
		vars->scale += 1;
	while (vars->scale * map->width > WIN_X / 3)
		vars->scale -= 1;
	set_points_values(map, vars);
}
