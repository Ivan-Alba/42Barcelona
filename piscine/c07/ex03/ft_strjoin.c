/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:11:19 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/06 19:35:57 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	size;

	size = 0;
	while (str[size] != '\0')
	{
		size++;
	}
	return (size);
}

char	*join_strings(char *joined, char **strs, char *sep, int size)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (strs[i][j] != '\0')
			joined[k++] = strs[i][j++];
		if (i < size - 1)
		{
			j = 0;
			while (sep[j] != '\0')
				joined[k++] = sep[j++];
		}
		i++;
	}
	joined[k] = '\0';
	return (joined);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*joined;
	int		total_size;
	int		i;

	if (size == 0)
	{
		joined = (char *) malloc(1);
		*joined = '\0';
		return (joined);
	}
	total_size = 0;
	i = 0;
	while (i < size)
		total_size += ft_strlen(strs[i++]);
	total_size += ft_strlen(sep) * (size - 1);
	joined = (char *) malloc((total_size + 1) * sizeof(char));
	return (join_strings(joined, strs, sep, size));
}
