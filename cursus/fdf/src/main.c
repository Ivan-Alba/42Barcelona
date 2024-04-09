/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:05:05 by igarcia2          #+#    #+#             */
/*   Updated: 2024/04/09 20:41:26 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
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
	else if ((keycode >= 0 && keycode <= 2) || keycode == 13)
		move_img(vars, keycode);
	else if (keycode == 43 || keycode == 47 || keycode == 49)
		rotate_z_img(vars, keycode);
	else if (keycode == 6 || keycode == 7)
		modify_z(vars, keycode);
	return (0);
}

//Function that refreshes on-screen rendering
void	refresh_render(t_vars *vars)
{
	t_data	img;

	img.img = mlx_new_image(vars->mlx, WIN_X, WIN_Y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	print_pixels(&img, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	draw_menu(vars);
	mlx_loop(vars->mlx);
}

//Main function
int	main(int argc, char *argv[])
{
	t_map	map;
	t_vars	vars;

	if (argc != 2)
		exit_error(ARGS_ERROR);
	map.map = read_map(argv[1]);
	initialize_map_info(&map, &vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_X, WIN_Y, "Hello world!");
	mlx_hook(vars.win, 2, 1L << 0, key_pressed, &vars);
	mlx_hook(vars.win, 17, 0, close_win, &vars);
	center_render(&vars);
	refresh_render(&vars);
}
