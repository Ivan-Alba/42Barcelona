/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:38:21 by igarcia2          #+#    #+#             */
/*   Updated: 2024/04/04 20:36:12 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define CONTROL_BOX			200
#define DRAWINFO_BOX		40
#define MAPINFO_BOX			280
#define COLORSCHEME_BOX		480
#define LINE_SIZE			30
#define MENU_TAB			30

static void	draw_controls(t_vars *vars)
{
	int	line;

	line = CONTROL_BOX;
	print_str(vars, MENU_TAB, line, "//// CONTROLS  ////");
	line += LINE_SIZE;
	print_str(vars, MENU_TAB, line, "ZOOM IN: [+]");
	line += LINE_SIZE;
	print_str(vars, MENU_TAB, line, "ZOOM OUT: [-]");
	line += LINE_SIZE;
	print_str(vars, MENU_TAB, line, "MOVE UP: [W]");
	line += LINE_SIZE;
	print_str(vars, MENU_TAB, line, "MOVE DOWN: [S]");
	line += LINE_SIZE;
	print_str(vars, MENU_TAB, line, "MOVE LEFT: [A]");	
	line += LINE_SIZE;
	print_str(vars, MENU_TAB, line, "MOVE RIGHT: [D]");
	line += LINE_SIZE;
	print_str(vars, MENU_TAB, line, "ROTATE +: [>]");
	line += LINE_SIZE;
	print_str(vars, MENU_TAB, line, "ROTATE -: [<]");
	line += LINE_SIZE;
	print_str(vars, MENU_TAB, line, "ORTOGRAPHIC VIEW: [SPACE]");
}

static void	draw_info(t_vars *vars)
{
	int	line;

	line = DRAWINFO_BOX;
	print_str(vars, MENU_TAB, line, "//// DRAW INFO ////");
	line += LINE_SIZE;
	print_str(vars, MENU_TAB, line, "X, Y: [   ] [   ]");
	print_nbr(vars, MENU_TAB + 70, line, vars->pos_x);
	print_nbr(vars, MENU_TAB + 130, line, vars->pos_y);
	line += LINE_SIZE;
	print_str(vars, MENU_TAB, line, "Z: [   ]");
	print_nbr(vars, MENU_TAB + 40, line, vars->z_angle);
	line += LINE_SIZE;
	print_str(vars, MENU_TAB, line, "Zoom:");
	print_nbr(vars, MENU_TAB + 80, line, vars->scale);
}

void	draw_menu(t_vars *vars)
{
	draw_info(vars);
	draw_controls(vars);
}
