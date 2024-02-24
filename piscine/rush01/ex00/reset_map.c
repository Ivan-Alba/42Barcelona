/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:24:50 by josegar2          #+#    #+#             */
/*   Updated: 2023/10/29 20:31:44 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	reset_map(int size, char elmapa[11][11])
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			elmapa[i][j] = 0;
			j++;
		}
		i++;
	}
}

int	write_value(int cr[2], char value, char elmapa[11][11])
{
	if (elmapa[cr[0]][cr[1]] < 0 && value == -elmapa[cr[0]][cr[1]])
		return (1);
	if (elmapa[cr[0]][cr[1]] > 0 && value != elmapa[cr[0]][cr[1]])
		return (1);
	elmapa[cr[0]][cr[1]] = value;
	return (0);
}
