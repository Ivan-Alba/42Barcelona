/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:28:04 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/19 14:52:46 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_words(char *str, char *separators)
{
	int	i;
	size_t	j;
	int	words;
	int	flag;

	if (!str || !separators)
		return (0);
	i = 0;
	flag = 1;
	while (str[i])
	{
		j = 0;
		while (separators[j])
		{
			if (str[i] == separators[j])
			{
				if (flag > 0)
					words+=2;
				else
					words++;
				flag = 0;
				break;
			}
			j++;
			if (j == ft_strlen(separators))
				flag++;
		}
		i++;
	}
	return (words);
}

void	create_substr(char *str, char *separators, char **result, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (separators[j])
		{
			if (str[i] == separators[j])

		}
	}
}

char	**ft_token_split(char *str, char *separators, t_data *data)
{
	char	**result;
	int		words;

	words = count_words(str, separators);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		print_error_exit("Error: memory allocation", data);
	ft_printf("Palabras: %d\n", words);
	create_substr(str, separators, result, data);
	return (result);
}
