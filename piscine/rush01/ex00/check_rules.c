/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:37:43 by josegar2          #+#    #+#             */
/*   Updated: 2023/10/29 21:14:04 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	count_blocks(int size, char values[9], int blocks[2]);

int	check_col(int cr[2], int size, char elmapa[11][11])
{
	int	i;

	i = 1;
	while (i <= size)
	{
		if (elmapa[cr[0]][i] == elmapa[cr[0]][cr[1]] && i != cr[1])
			return (1);
		i++;
	}
	return (0);
}

int	check_row(int cr[2], int size, char elmapa[11][11])
{
	int	i;

	i = 1;
	while (i <= size)
	{
		if (elmapa[i][cr[1]] == elmapa[cr[0]][cr[1]] && i != cr[0])
			return (1);
		i++;
	}
	return (0);
}

int	check_cblock(int cr[2], int size, char elmapa[11][11])
{
	int		blocs[2];
	char	valores[9];
	int		i;

	i = 0;
	while (i < size)
	{
		valores[i] = elmapa[cr[0]][i + 1];
		i++;
	}
	count_blocks(size, valores, blocs);
	if (cr[1] == size)
	{
		if (blocs[0] != elmapa[cr[0]][0] || blocs[1] != elmapa[cr[0]][size + 1])
			return (1);
	}
	else
	{
		if (blocs[0] > elmapa[cr[0]][0])
			return (1);
	}
	return (0);
}

int	check_vblock(int cr[2], int size, char elmapa[11][11])
{
	int		blocs[2];
	char	valores[9];
	int		i;

	i = 0;
	while (i < size)
	{
		valores[i] = elmapa[i + 1][cr[1]];
		i++;
	}
	count_blocks(size, valores, blocs);
	if (cr[0] == size)
	{
		if (blocs[0] != elmapa[0][cr[1]] || blocs[1] != elmapa[size + 1][cr[1]])
			return (1);
	}
	else
	{
		if (blocs[0] > elmapa[0][cr[1]])
			return (1);
	}
	return (0);
}

int	check_rules(int cr[2], int size, char elmapa[11][11])
{
	if (check_col(cr, size, elmapa))
		return (1);
	if (check_row(cr, size, elmapa))
		return (1);
	if (check_cblock(cr, size, elmapa))
		return (1);
	if (check_vblock(cr, size, elmapa))
		return (1);
	return (0);
}
