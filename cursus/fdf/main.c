/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:05:05 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/27 17:41:16 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	char	**map_format;
	t_vars	vars;
	
	if (argc != 2)
		exit_error(ARGS_ERROR);
	//Read map
	map_format = read_map(argv[1]);
	//Initialize mlx window
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	//Initialize event listeners
	vars.mlx = mlx;
	vars.win = mlx_win;
	mlx_hook(vars.win, 2, 1L<<0, key_pressed, &vars);
    mlx_hook(vars.win, 17, 0, close_win, &vars);
	//Initialize img
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	//Print pixels
	print_pixels(&img, map_format);

	//Put img on window
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	//Start render
	mlx_loop(mlx);
}
