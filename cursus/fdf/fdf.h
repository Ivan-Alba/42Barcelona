/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:34:50 by igarcia2          #+#    #+#             */
/*   Updated: 2024/03/27 17:15:16 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"
# include <mlx.h>
# include <math.h>

# define ARGS_ERROR "Args error\n"
# define FILE_ERROR "File error\n"
# define MAP_ERROR "Map format error\n"
# define WIN_X 1920
# define WIN_Y 1080
# define CELL_SIZE 50

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct	s_points {
	int		x;
	int		y;
	int		z;
	int		x_iso;
	int		y_iso;
	int		color;
}				t_points;

typedef struct	s_map {
	char		**map;
	int			width;
	int			height;
	t_points	*points;
}				t_map;

void	exit_error(char *error_msg);
char	**read_map(char *file);
int		key_pressed(int keycode, t_vars *vars);
int		close_win(t_vars *vars);
void	print_pixels(t_data *img, t_map *map);
void	initialize_map_info(t_map *map);
void	convert_isometric(int *x, int *y, int z);

#endif
