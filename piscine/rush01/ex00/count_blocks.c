/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_blocks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josegar2 <josegar2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 09:25:06 by josegar2          #+#    #+#             */
/*   Updated: 2023/10/29 17:34:43 by josegar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	count_blocks(int size, char values[9], int blocks[2])
{
	int	barrera;
	int	i;

	barrera = 0;
	i = 0;
	blocks[0] = 0;
	blocks[1] = 0;
	while (i < size)
	{
		if (values[i] > barrera)
		{
			blocks[0]++;
			barrera = values[i];
		}
		i++;
	}
	barrera = 0;
	while (--i >= 0)
	{
		if (values[i] > barrera)
		{
			blocks[1]++;
			barrera = values[i];
		}
	}
}
