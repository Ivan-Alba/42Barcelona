/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:45:47 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/13 16:47:29 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void clean_prompt_data(t_data *data)
{
	free(data->prompt_init);
	data->prompt_init = NULL;
	free_split(&(data->split_info->splitted_prompt));
	ft_token_lstclear(&data->tokens);
}

void	free_split(char ***splitted)
{
	int	i;

	i = 0;
	if (splitted && *splitted)
	{
		while ((*splitted)[i])
		{
			free((*splitted)[i]);
			(*splitted)[i] = NULL;
			i++;
		}
		free(*splitted);
		*splitted = NULL;
	}
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->split_info)
		{
			if (data->split_info->splitted_prompt)
				free_split(&(data->split_info->splitted_prompt));
			free(data->split_info);
		}
		if (data->prompt_init)
			free(data->prompt_init);
		if (data->tokens)
			ft_token_lstclear(&data->tokens);
		free(data);
	}
}
