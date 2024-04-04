/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:21:35 by igarcia2          #+#    #+#             */
/*   Updated: 2024/04/04 18:49:00 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Function that transforms vertex positions in isometric view
void	get_iso_values(t_points *pnt, int angle)
{
	pnt->x_iso = pnt->x;
	pnt->y_iso = pnt->y;
	if (angle > 0)
	{
		pnt->x_iso = (pnt->x_iso - pnt->y_iso) * cos(angle * M_PI / 180);
		pnt->y_iso = (pnt->x_iso + pnt->y_iso) * sin(angle * M_PI / 180) - pnt->z;
	}
}

//Function that stores in each vertex the reference color
int	set_color(char *str, int z)
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
		color = hex_to_int(hexa);
		free(hexa);
	}
	else if (z > 8)
		color = 0xFF2D00;
	//else if (z > 5)
		//color = 0xFFA600;
	//else if (z > 2)
		//color = 0x32FF00;
	return (color);
}

//Function that configures the vertices read from the map
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
		j = -1;
		line = ft_split(map->map[i], ' ');
		if (!line)
			exit_error("ERROR");
		while (line[++j] != NULL)
		{
			map->points[h].x = j * vars->scale;
			map->points[h].y = i * vars->scale;
			map->points[h].z = ft_atoi(line[j]);
			map->points[h].color = set_color(line[j], map->points[h].z);
			get_iso_values(&(map->points[h]), vars->z_angle);
			h++;
		}
		i++;
		free_split(line);
	}
}

//Function that initializes the rendering configuration values
void	initialize_settings(t_vars *vars)
{
	t_map	*map;

	map = vars->map;
	//SCALE
	vars->scale = INIT_SCALE;
	while (vars->scale * map->width < WIN_X / 2)
		vars->scale += 1;
	while (vars->scale * map->width > WIN_X / 2)
		vars->scale -= 1;
	//POSITION
	vars->pos_x = 500;
	vars->pos_y = 500;
	//ANGLE
	vars->z_angle = INIT_Z_ANGLE;
}

//Function that initializes the map configuration values
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
	map->points = malloc((map->width * map->height) * sizeof(t_points));
	if (!map->points)
		exit_error("ERROR");
	free_split(line);
	vars->map = map;
	initialize_settings(vars);
	set_points_values(map, vars);
}
