/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_controller.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:29:18 by igarcia2          #+#    #+#             */
/*   Updated: 2024/04/03 18:58:14 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Function that close program execution
int	close_win(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

//Function that rotates the rendering at the angle z
void	rotate_z_img(t_vars *vars, int keycode)
{
	if (keycode == 83 && vars->z_angle > 0)
		vars->z_angle -= 1;
	else if (keycode == 83 && vars->z_angle == 0)
		vars->z_angle = 360;
	else if (keycode == 85 && vars->z_angle < 360)
		vars->z_angle += 1;
	else if (keycode == 85 && vars->z_angle == 360)
		vars->z_angle = 0;
	set_points_values(vars->map, vars);
	refresh_render(vars);
}

//Function that scales the rendering up or down
void	change_scale(t_vars *vars, int is_plus)
{
	if (is_plus && vars->scale < 60)
		vars->scale += 1;
	else if (!is_plus && vars->scale > 2)
		vars->scale -= 1;
	set_points_values(vars->map, vars);
	refresh_render(vars);
}

//Function that moves the rendering when the corresponding key is pressed
void	move_img(t_vars *vars, int keycode)
{
	if (keycode == 123)
		vars->pos_x -= MOVE_QTY;
	else if (keycode == 124)
		vars->pos_x += MOVE_QTY;
	else if (keycode == 125)
		vars->pos_y += MOVE_QTY;
	else if (keycode == 126)
		vars->pos_y -= MOVE_QTY;
	refresh_render(vars);
}

//Function that listens for the key pressed and calls the corresponding function
int	key_pressed(int keycode, t_vars *vars)
{
	ft_printf("KEY PRESSED:%d\n", keycode);
	if (keycode == 53)
		close_win(vars);
	else if (keycode == 69)
		change_scale(vars, 1);
	else if (keycode == 78)
		change_scale(vars, 0);
	else if (keycode >= 123 && keycode <= 126)
		move_img(vars, keycode);
	else if (keycode == 83 || keycode == 85)
		rotate_z_img(vars, keycode);
	return (0);
}
