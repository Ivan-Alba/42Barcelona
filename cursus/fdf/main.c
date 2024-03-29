/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:05:05 by igarcia2          #+#    #+#             */
/*   Updated: 2024/03/27 17:06:20 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_data	img;
	t_map	map;
	t_vars	vars;
	
	if (argc != 2)
		exit_error(ARGS_ERROR);
	//Read map
	map.map = read_map(argv[1]);
	initialize_map_info(&map);
	//Initialize mlx window
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_X, WIN_Y, "Hello world!");
	//Initialize event listeners
	mlx_hook(vars.win, 2, 1L<<0, key_pressed, &vars);
    mlx_hook(vars.win, 17, 0, close_win, &vars);
	//Initialize img
	img.img = mlx_new_image(vars.mlx, WIN_X, WIN_Y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	//Print pixels
	print_pixels(&img, &map);
	//Put img on window
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	//Start render
	mlx_loop(vars.mlx);
}
