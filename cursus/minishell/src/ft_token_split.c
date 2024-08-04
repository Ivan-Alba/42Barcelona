/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:28:04 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/28 18:18:19 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	count_words(t_data *data, char *separators)
{
	int	i;
	int	j;

	if (!(data->prompt) || !separators)
		return ;
	i = -1;
	while (data->prompt[++i])
	{
		j = -1;
		(data->split_info->len)++;
		while (separators[++j])
		{
			if (data->prompt[i] == separators[j])
			{
				if (data->split_info->len > 1)
					data->split_info->words += 2;
				else
					data->split_info->words++;
				data->split_info->len = 0;
				break ;
			}
		}
	}
	if (data->split_info->len > 0)
		data->split_info->words++;
}

void	insert_substr(char *str, int len, int word_idx, t_data *data)
{
	int	i;

	if (len == 0)
		len = 1;
	data->split_info->splitted_prompt[word_idx]
		= malloc(sizeof(char) * (len + 1));
	if (!data->split_info->splitted_prompt[word_idx])
		print_error_exit(MALLOC_ERROR, data);
	i = 0;
	while (i < len)
	{
		data->split_info->splitted_prompt[word_idx][i] = str[i];
		i++;
	}
	data->split_info->splitted_prompt[word_idx][i] = '\0';
}

void	create_substr(char *separators, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->prompt[++i])
	{
		j = -1;
		while (separators[++j])
		{
			if (data->prompt[i] == separators[j])
			{
				insert_substr(data->prompt, i,
					++(data->split_info->word_idx), data);
				if (!i)
					(data->prompt)++;
				else
					(data->prompt) += i;
				i = -1;
				break ;
			}
		}
	}
	if (i >= 1)
		insert_substr(data->prompt, i, ++(data->split_info->word_idx), data);
	data->split_info->splitted_prompt[++(data->split_info->word_idx)] = NULL;
}

void	init_split_info_data(t_data *data)
{
	data->split_info = malloc(sizeof(t_split));
	if (!data->split_info)
		print_error_exit(MALLOC_ERROR, data);
	data->split_info->words = 0;
	data->split_info->len = 0;
	data->split_info->word_idx = -1;
	data->split_info->splitted_prompt = NULL;
}

void	ft_token_split(char *separators, t_data *data)
{
	init_split_info_data(data);
	count_words(data, separators);
	data->split_info->splitted_prompt = malloc(sizeof(char *)
			* (data->split_info->words + 1));
	if (!data->split_info->splitted_prompt)
		print_error_exit(MALLOC_ERROR, data);
	//ft_printf("Palabras: %d\n", data->split_info->words);
	create_substr(separators, data);
	data->split_info->words = 0;
	data->split_info->len = 0;
	data->split_info->word_idx = -1;
}
