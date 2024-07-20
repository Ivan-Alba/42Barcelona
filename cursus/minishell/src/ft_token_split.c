/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:28:04 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/20 19:27:44 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_words(char *str, char *separators)
{
	int	i;
	size_t	j;
	int	words;
	int	len;

	if (!str || !separators)
		return (0);
	i = 0;
	len = 0;
	words = 0;
	while (str[i])
	{
		j = 0;
		len++;
		while (separators[j])
		{
			if (str[i] == separators[j])
			{
				if (len > 1)
					words+=2;
				else
					words++;
				len = 0;
				break;
			}
			j++;
		}
		i++;
	}
	if (len > 0)
		words++;
	return (words);
}

void	insert_substring(char *str, int len, int word_idx, t_data *data)
{
	int	i;
	
	i = 0;
	if (!len)
		len = 1;
	data->splitted_prompt[word_idx] = malloc(sizeof(char) * (len + 1));
	if (!data->splitted_prompt[word_idx])
		print_error_exit("Error: memory allocation", data);
	while (i < len)
	{
		data->splitted_prompt[word_idx][i] = str[i];
		i++;
	}
	data->splitted_prompt[word_idx][i] = '\0';
}

void	create_substr(char *str, char *separators, t_data *data)
{
	int	i;
	int	j;
	int	word_idx;

	i = 0;
	word_idx = 0;
	while (str[i])
	{
		j = 0;
		while (separators[j])
		{
			if (str[i] == separators[j])
			{
				insert_substring(&str[0], i, word_idx, data);
				word_idx++;
				if (!i)
					str++;
				else
					str += i;
				i = -1;
				break;
			}
			j++;
		}
		i++;
	}
	if (i >= 1)
		insert_substring(&str[0], i, word_idx, data);
	data->splitted_prompt[word_idx + 1] = NULL;
}

void	ft_token_split(char *str, char *separators, t_data *data)
{
	int		words;

	words = count_words(str, separators);
	data->splitted_prompt = malloc(sizeof(char *) * (words + 1));
	if (!data->splitted_prompt)
		print_error_exit("Error: memory allocation", data);
	ft_printf("Palabras: %d\n", words);
	create_substr(str, separators, data);
}
