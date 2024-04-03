/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:38:21 by igarcia2          #+#    #+#             */
/*   Updated: 2024/04/03 18:50:46 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define CONTROL_BOX			650
#define DRAWINFO_BOX		40
#define MAPINFO_BOX			280
#define COLORSCHEME_BOX		480
#define LINE_SIZE			30
#define MENU_TAB			30

static void	draw_info(t_vars *vars)
{
	int		line;

	line = DRAWINFO_BOX;
	print_str(vars, MENU_TAB, line, "//// DRAW INFO ////");
	line += LINE_SIZE;
	/*print_str(vars, MENU_TAB, line, "Reenders:");
	print_nbr(vars, MENU_TAB + 100, line, meta->map.renders);
	line += LINE_SIZE;
	print_str(meta, MENU_TAB, line, "Performance(ms):");
	print_nbr(meta, MENU_TAB + 170, line, meta->map.performance * 1000);
	line += LINE_SIZE;
	*/
	print_str(vars, MENU_TAB, line, "X, Y, Z: [   ] [   ] [   ]");
	print_nbr(vars, MENU_TAB + 100, line, 0);
	print_nbr(vars, MENU_TAB + 160, line, 0);
	print_nbr(vars, MENU_TAB + 220, line, vars->z_angle);
	line += LINE_SIZE;
	print_str(vars, MENU_TAB, line, "Zoom:");
	print_nbr(vars, MENU_TAB + 80, line, vars->scale);
}

void	draw_menu(t_vars *vars)
{
	draw_info(vars);
}
