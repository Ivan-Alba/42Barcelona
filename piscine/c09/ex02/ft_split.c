/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:13:27 by igarcia2          #+#    #+#             */
/*   Updated: 2023/11/08 20:42:18 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	last_substring(char **splitted, int *j, int *i, char *str)
{
	int	k;

	k = 0;
	if (*i > 0)
	{
		splitted[*j] = (char *) malloc((*i + 1) * sizeof(char));
		while (*i > 0)
		{
			splitted[*j][k++] = *str++;
			*i -= 1;
		}
		splitted[*j][k] = '\0';
		*j += 1;
	}
}

int	insert_substring(char **splitted, char *str, int *i, int *j)
{
	int	k;
	int	pointer;

	pointer = 0;
	k = 0;
	if (*i > 0)
	{
		splitted[*j] = (char *) malloc((*i + 1) * sizeof(char));
		while (*i > 0)
		{
			splitted[*j][k++] = *str++;
			pointer++;
			*i -= 1;
		}
		splitted[*j][k] = '\0';
		*j += 1;
	}
	else
	{
		pointer = 1;
		str++;
	}
	return (pointer);
}

char	**last_steps(char **splitted, int array[2], char *str)
{
	last_substring(splitted, &array[1], &array[0], str);
	splitted[array[1]] = NULL;
	return (splitted);
}

char	**ft_split(char *str, char *charset)
{
	int		array[2];
	int		l;
	char	**splitted;

	array[0] = 0;
	array[1] = 0;
	splitted = (char **)malloc(10 * sizeof(char *));
	if (splitted == NULL)
		return (NULL);
	while (str[array[0]] != '\0')
	{
		l = 0;
		while (charset[l] != '\0')
		{
			if (str[array[0]] == charset[l++])
			{
				str += insert_substring(splitted, str, &array[0], &array[1]);
				array[0] = -1;
				break ;
			}
		}
		array[0]++;
	}
	return (last_steps(splitted, array, str));
}
