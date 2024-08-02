/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:29:42 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/02 16:56:34 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *str1, char *str2)
{
	int		len;
	int		i;
	int		j;
	char	*res;

	if (!str1 && !str2)
		return (NULL);
	else if (!str1)
		return (ft_strdup(str2));
	else if (!str2)
		return (ft_strdup(str1));
	len = ft_strlen(str1) + ft_strlen(str2);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	j = 0;
	i = 0;
	while (str1[i] != '\0')
		res[j++] = str1[i++];
	i = 0;
	while (str2[i] != '\0')
		res[j++] = str2[i++];
	res[j] = '\0';
	return (res);
}
