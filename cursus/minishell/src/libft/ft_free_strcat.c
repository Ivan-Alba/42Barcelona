/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strcat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:29:42 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/02 16:56:34 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_strcat(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*res;

	if (!str1 && !str2)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!res)
		return (NULL);
	j = 0;
	i = 0;
	while (str1 && str1[i] != '\0')
		res[j++] = str1[i++];
	i = 0;
	while (str2 && str2[i] != '\0')
		res[j++] = str2[i++];
	res[j] = '\0';
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	str1 = NULL;
	str2 = NULL;
	return (res);
}
