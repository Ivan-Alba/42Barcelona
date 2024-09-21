/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:45:47 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/26 13:27:15 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*	Function Name: remove_heredoc_files
 *
 *	Description:
 *
 *		This function deletes temporary files of type heredoc created during
 *		execution.
 *
 *	Parameters:
 *
 *		t_section *section	- The pointer to the section containing the
 *								data of the heredocs created in it.
 *
 */
void	remove_heredoc_files(t_section *section, int last_section_id)
{
	t_files	*current_file;

	while (section)
	{
		current_file = section->files;
		while (current_file)
		{
			if (current_file->file_type == HEREDOC
				&& current_file->hrdc_file_name)
			{
				if (unlink(current_file->hrdc_file_name) == -1)
					perror("Error deleting file");
			}
			current_file = current_file->next;
		}
		section = get_next_section(section, last_section_id);
	}
}

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
	if (data->path)
		free_split(&data->path);
	if (data->pids)
		free(data->pids);
	data->pids = NULL;
	remove_heredoc_files(data->sections, data->section_id - 1);
	data->section_id = 0;
	ft_token_lstclear(&data->tokens);
	free_sections(&data->sections);
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
		free_if_exists(data->prompt_init);
		if (data->tokens)
			ft_token_lstclear(&data->tokens);
		if (data->sections)
			free_sections(&data->sections);
		if (data->pipes)
			free_close_pipes(data);
		if (data->path)
			free_split(&data->path);
		free_if_exists(data->pids);
		if (data->env)
			free_split(&data->env);
		close(data->std_in);
		close(data->std_out);
		free(data);
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
	if ((*section)->cmd_path)
		free((*section)->cmd_path);
	(*section)->cmd_path = NULL;
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
