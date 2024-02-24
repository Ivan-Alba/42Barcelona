/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rellena_celdas.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 09:42:23 by josegar2          #+#    #+#             */
/*   Updated: 2023/10/29 20:47:44 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	write_value(int cr[2], char value, char elmapa[11][11]);

int	check_rules(int cr[2], int size, char elmapa[11][11]);

void	next_cr(int actual[2], int next[2], int size)
{
	next[0] = actual[0];
	next[1] = actual[1] + 1;
	if (next[1] > size)
	{
		next[1] = 1;
		next[0]++;
	}
}

int	rellena_celdas(int cr[2], char elmapa[11][11], int size)
{
	char	valor;
	char	previous;
	int		lcr[2];

	if (cr[0] > size || cr[1] > size)
		return (0);
	valor = 1;
	previous = elmapa[cr[0]][cr[1]];
	while (valor <= size)
	{
		if (!write_value(cr, valor, elmapa))
		{
			if (!check_rules(cr, size, elmapa))
			{
				next_cr(cr, lcr, size);
				if (!rellena_celdas(lcr, elmapa, size))
					return (0);
				elmapa[cr[0]][cr[1]] = previous;
			}
			else
				elmapa[cr[0]][cr[1]] = previous;
		}
		valor++;
	}
	return (1);
}
