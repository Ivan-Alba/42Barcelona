/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 06:33:24 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/22 06:53:34 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_sort_int_tab(int *tab, int size)
{
	int	idx;
	int	idx_2;
	int	aux;

	idx = 0;
	while (idx < size - 1)
	{
		idx_2 = idx + 1;
		while (idx_2 < size)
		{
			if (tab[idx] > tab[idx_2])
			{
				aux = tab[idx_2];
				tab[idx_2] = tab[idx];
				tab[idx] = aux;
			}
			idx_2++;
		}
		idx++;
	}
}
