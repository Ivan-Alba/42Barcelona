/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_controller.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:29:18 by igarcia2          #+#    #+#             */
/*   Updated: 2024/04/05 19:22:18 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Function that close program execution
int	close_win(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	free_split((vars->map)->map);
	free((vars->map)->points);
	exit(0);
}

//Function that rotates the rendering at the angle z
void	rotate_z_img(t_vars *vars, int keycode)
{
	if (keycode == 43 && vars->z_angle > 0)
		vars->z_angle -= 1;
	else if (keycode == 43 && vars->z_angle == 0)
		vars->z_angle = 360;
	else if (keycode == 47 && vars->z_angle < 360)
		vars->z_angle += 1;
	else if (keycode == 47 && vars->z_angle == 360)
		vars->z_angle = 0;
	else if (keycode == 49)
	{
		if (vars->z_angle != 0)
			vars->z_angle = 0;
		else
			vars->z_angle = INIT_Z_ANGLE;
	}
	set_points_values(vars->map, vars);
	refresh_render(vars);
}

//Function that scales the rendering up or down
void	change_scale(t_vars *vars, int is_plus)
{
	if (is_plus && vars->scale < 60)
		vars->scale += 1;
	else if (!is_plus && vars->scale > 1)
		vars->scale -= 1;
	set_points_values(vars->map, vars);
	refresh_render(vars);
}

//Function that moves the rendering when the corresponding key is pressed
void	move_img(t_vars *vars, int keycode)
{
	if (keycode == 0)
		vars->pos_x -= MOVE_QTY;
	else if (keycode == 2)
		vars->pos_x += MOVE_QTY;
	else if (keycode == 1)
		vars->pos_y += MOVE_QTY;
	else if (keycode == 13)
		vars->pos_y -= MOVE_QTY;
	refresh_render(vars);
}

//Function that increases or decreases the height of the vertices
void	modify_z(t_vars *vars, int keycode)
{
	int	i;
	int	change;

	i = 0;
	change = 1;
	if (keycode == 6)
		change = -1;
	while (i < vars->map->height * vars->map->width)
	{
		if (!change && (vars->map)->points[i].z > 7)
			(vars->map)->points[i].z += change;
		else if (change && (vars->map)->points[i].z >= 5)
			(vars->map)->points[i].z += change;
		get_iso_values(&(vars->map->points[i]), vars->z_angle);
		i++;
	}
	refresh_render(vars);
}
