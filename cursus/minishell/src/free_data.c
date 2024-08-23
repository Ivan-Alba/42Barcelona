/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:45:47 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/21 19:22:29 by igarcia2         ###   ########.fr       */
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
	if (data->pipes)
		free_close_pipes(data);
	data->section_id = 0;
	data->heredoc_file_n = 0;
	ft_token_lstclear(&data->tokens);
	free_sections(&data->sections);
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
			free_close_pipes(data);
	}
}

//Frees the allocated memory of the nodes of a list of type t_section
void	free_sections(t_section **section)
{
	if (!section || !(*section))
		return ;
	free_sections(&(*section)->inner);
	free_sections(&(*section)->next);
	if ((*section)->cmd)
		free_split(&(*section)->cmd);
	(*section)->cmd = NULL;
	//TODO REMOVE HEREDOC FILES
	remove_heredoc_files(&(*section));
	ft_files_lstclear(&(*section)->files);
	free(*section);
	*section = NULL;
}

//Free and closes all pipes
void	free_close_pipes(t_data *data)
{
	int	i;

	i = 0;
	if (data->pipes)
	{
		while (i < data->section_id - 1)
		{
			close(data->pipes[i * 2]);
			close(data->pipes[i * 2 + 1]);
			i++;
		}
		free(data->pipes);
		data->pipes = NULL;
	}
}
