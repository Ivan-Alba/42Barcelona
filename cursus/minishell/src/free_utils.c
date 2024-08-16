/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:45:47 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/16 21:08:20 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Cleans and frees the necessary data between one prompt and the next one
void	clean_prompt_data(t_data *data)
{
	free(data->prompt_init);
	data->prompt_init = NULL;
	free_split(&(data->split_info->splitted_prompt));
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
	}
}

//Frees the allocated memory of the nodes of a list of type t_section
void	free_sections(t_section **section)
{
	if (!section || !(*section))
		return ;
	free_sections((void *)&(*section)->inner);
	free_sections((void *)&(*section)->next);
	if ((*section)->cmd)
		free_split(&(*section)->cmd);
	(*section)->cmd = NULL;
	if ((*section)->infiles)
		free_split(&(*section)->infiles);
	(*section)->infiles = NULL;
	if ((*section)->outfiles)
		free_split(&(*section)->outfiles);
	(*section)->outfiles = NULL;
	if ((*section)->heredocs)
		free_split(&(*section)->heredocs);
	(*section)->heredocs = NULL;
	if ((*section)->outfiles_app)
		free_split(&(*section)->outfiles_app);
	(*section)->outfiles_app = NULL;
	free(*section);
	*section = NULL;
}
