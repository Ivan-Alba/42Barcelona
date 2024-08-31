/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:31:40 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/31 15:58:16 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**search_files(char	*regex,  t_data *data)
{
	char	**expanded;
}

char	*expand_wildcard_cmd(char **cmd, int *idx, t_data *data)
{
	if (search_files(cmd[*idx], data))
		//TODO check if 1 or more 
	else
		return (cmd[*idx]);
}

/**
 *	Function Name: manage_wildcard
 *
 *	Description:
 *
 *		This function goes through all the commands and file names of the section
 *		received by parameter and calls the function in charge of checking if
 *		there are wildcards(*) to expand and expand them if so.
 *
 *	Parameters:
 *
 *		t_section *section	- The pointer to the section from which to expand its
 *								variables.
 *		t_data *data		- The pointer to the t_data struct with all
 *								the execution data.
 *
 */
int	manage_wildcard(t_section *section, t_data *data)
{
	int		i;
	t_files	*curr_file;

	i = 0;
	while (section->cmd && section->cmd[i])
	{
		if (ft_strchr(section->cmd[i], '*'))
			section->cmd[i] = expand_wildcard_cmd(section->cmd, &i, data);
		i++;
	}
	curr_file = section->files;
	while (curr_file)
	{
		if (curr_file->file_type != HEREDOC)
		{
			if (ft_strchr(curr_file->file_name, '*'))
				curr_file->file_name = get_str_expanded(curr_file->file_name, data);
		}
		curr_file = curr_file->next;
	}
}
