/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:45:47 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/19 15:53:07 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Cleans and frees the necessary data between one prompt and the next one
void	clean_prompt_data(t_data *data)
{
	if (data->prompt_init)
	{
		free(data->prompt_init);
		data->prompt_init = NULL;
	}
	if (data->split_info)
	{
		free_split(&(data->split_info->splitted_prompt));
		free(data->split_info);
		data->split_info = NULL;
	}
	data->section_id = 0;
	data->pipes_needed = 0;
	ft_token_lstclear(&data->tokens);
	free_sections(&data->sections);
	if (data->pipes)
		free(data->pipes);
}

//Receive a char** and free all of its contents
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

//Releases all the data necessary to finalize the program execution
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
		if (data->sections)
			free_sections(&data->sections);
		free(data);
		if (data->pipes)
			free(data->pipes);
	}
}

//Frees the allocated memory of the nodes of a list of type t_section
void	free_sections(t_section **section)
{
	int	i;

	if (!section || !(*section))
		return ;
	free_sections(&(*section)->inner);
	free_sections(&(*section)->next);
	if ((*section)->cmd)
		free_split(&(*section)->cmd);
	(*section)->cmd = NULL;
	if ((*section)->files)
	{
		i = -1;
		while (++i < 4)
		{
			if ((*section)->files[i])
				free_split(&((*section)->files[i]));
		}
		free((*section)->files);
	}
	free(*section);
	*section = NULL;
}
