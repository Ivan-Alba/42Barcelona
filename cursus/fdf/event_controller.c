/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_controller.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:29:18 by igarcia2          #+#    #+#             */
/*   Updated: 2024/04/02 19:27:20 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_scale(t_vars *vars, int is_plus)
{
	if (is_plus)
	{
		vars->scale += 1;
		set_points_values(vars->map, vars);
		refresh_render(vars);
	}
	else if (vars->scale > 2)
	{
		vars->scale -= 1;
		set_points_values(vars->map, vars);
		refresh_render(vars);

	}
}

void	move_img(t_vars *vars, int keycode)
{
	if (keycode == 123)
	{
		vars->pos_x -= 1;
		refresh_render(vars);
	}
	else if (keycode == 124)
	{
		vars->pos_x += 1;
		refresh_render(vars);
	}
	else if (keycode == 125)
	{
		vars->pos_y += 1;
		refresh_render(vars);
	}
	else if (keycode == 126)
	{
		vars->pos_y -= 1;
		refresh_render(vars);
	}
}

//Function that listens for the key pressed and calls the corresponding function
int key_pressed(int keycode, t_vars *vars)
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
	return (0);
}
