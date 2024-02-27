/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:34:50 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/27 17:51:51 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include "libft/get_next_line/get_next_line.h"
# include <mlx.h>

# define ARGS_ERROR "Args error\n"
# define FILE_ERROR "File error\n"
# define MAP_ERROR "Map format error\n"
# define WIN_X = 1920
# define WIN_Y = 1080

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

void	exit_error(char *error_msg);
char	**read_map(char *file);
int		key_pressed(int keycode, t_vars *vars);
int		close_win(t_vars *vars);
void	print_pixels(t_data *img, char **tmp);

#endif
