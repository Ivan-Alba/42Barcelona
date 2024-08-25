/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:19:24 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/23 19:58:46 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_cmd_path(char *cmd, t_data *data)
{
	int		i;
	char	*complete_path;
	char	*final_path;

	i = 0;
	if (data->path && cmd)
	{
		while (data->path[i])
		{
			complete_path = ft_strjoin(data->path[i], "/");
			if (!complete_path)
				print_error_exit(MALLOC_ERROR, data);
			final_path = ft_strjoin(complete_path, cmd);
			free(complete_path);
			complete_path = NULL;
			if (!final_path)
				print_error_exit(MALLOC_ERROR, data);
			if (access(final_path, F_OK) != -1)
				return (final_path);
			free(final_path);
			final_path = NULL;
			i++;
		}
	}
	return (NULL);
}

//Searches for the PATH environment variable and stores it
void	get_path(t_data *data)
{
	int	i;
	int	found;

	found = 0;
	i = 0;
	while ((data->env)[i])
	{
		if (ft_strnstr((data->env)[i], "PATH=", 5))
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (found)
	{
		data->path = ft_split((data->env)[i] + 5, ':');
		if (!data->path)
			print_error_exit(MALLOC_ERROR, data);
	}
	else
		data->path = NULL;
}
