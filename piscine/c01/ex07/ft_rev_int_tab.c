/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 05:05:19 by igarcia2          #+#    #+#             */
/*   Updated: 2023/10/22 13:24:20 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_rev_int_tab(int *tab, int size)
{
	int	aux;
	int	idx_rev;
	int	idx;

	idx = 0;
	idx_rev = size - 1;
	while (idx < size / 2)
	{
		aux = tab[idx];
		tab[idx] = tab[idx_rev];
		tab[idx_rev] = aux;
		idx++;
		idx_rev--;
	}
}
