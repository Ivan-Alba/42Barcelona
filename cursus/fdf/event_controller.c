/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_controller.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:29:18 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/27 17:33:27 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Function that listens for the key pressed and calls the corresponding function
int key_pressed(int keycode, t_vars *vars)
{
	ft_printf("KEY PRESSED:%d\n", keycode);
	if (keycode == 53)
	{
		close_win(vars);
	}
	return (0);
}
