/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rellena_mapa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 08:01:19 by josegar2          #+#    #+#             */
/*   Updated: 2023/10/29 12:38:06 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	rellena_celdas(int cr[2], char elmapa[11][11], int size);

int	rellena_cols(int col, char elmapa[11][11], int size)
{
	int	i;

	if (col > size)
		return (0);
	i = 0;
	while (i <= size)
	{
		elmapa[col][i] = i;
		i++;
	}
	rellena_cols(col + 1, elmapa, size);
	return (0);
}

int	rellena_mapa(char elmapa[11][11], int size)
{
	int	cr[2];

	cr[0] = 1;
	cr[1] = 1;
	return (rellena_celdas(cr, elmapa, size));
}
	/*
	 if (rellena_cols(1, elmapa, size) == 1)
	{
		return (1);
	}
	return (0);
	*/
