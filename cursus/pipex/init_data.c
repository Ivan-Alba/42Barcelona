/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:19:37 by igarcia2          #+#    #+#             */
/*   Updated: 2024/05/13 15:48:19 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Create the necessary pipes for communication between processes
void	generate_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_num)
	{
		if (pipe(data->pipes + 2 * i) == -1)
			free_data(data, "Error creating pipes.\n");
		i++;
	}
}

//Split command name and flags
char	**get_cmd_flags(char *arg, t_pipex *data)
{
	char	**cmd_flags;

	cmd_flags = ft_split(arg, ' ');
	if (!cmd_flags)
		free_data(data, "Malloc error\n");
	return (cmd_flags);
}

//Search within the environment paths where the command is located
char	*get_cmd_path(t_pipex *data, char *cmd)
{
	int		i;
	char	*complete_path;
	char	*final_path;

	i = 0;
	while (data->path[i])
	{
		complete_path = ft_strjoin(data->path[i], "/");
		if (!complete_path)
			free_data(data, "Malloc error");
		final_path = ft_strjoin(complete_path, cmd);
		if (!final_path)
			free_data(data, "Malloc error");
		free(complete_path);
		complete_path = NULL;
		if (access(final_path, F_OK) != -1)
			return (final_path);
		free(final_path);
		final_path = NULL;
		i++;
	}
	return (NULL);
}

//Searches for the PATH environment variable and stores it
void	get_path(char **env, t_pipex *data)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			break ;
		i++;
	}
	data->path = ft_split(env[i] + 5, ':');
	if (!data->path)
		free_data(data, "Malloc error\n");
}

//Initializes the structures with the necessary data
void	init_data(t_pipex *data, int argc, char **argv, char **env)
{
	int	i;

	get_path(env, data);
	data->cmd_num = argc - 3;
	data->cmds = malloc((data->cmd_num) * sizeof(t_cmd));
	data->out_file = ft_strdup(argv[argc - 1]);
	data->in_file = ft_strdup(argv[1]);
	data->pipes = malloc(data->cmd_num * 2 * sizeof(int));
	if (!data->cmds || !data->pipes || !data->out_file || !data->in_file)
		free_data(data, "Malloc error\n");
	generate_pipes(data);
	i = 0;
	while (i < data->cmd_num)
	{
		data->cmds[i].first = 0;
		data->cmds[i].last = 0;
		data->cmds[i].cmd_flags = get_cmd_flags(argv[2 + i], data);
		data->cmds[i].path = get_cmd_path(data, data->cmds[i].cmd_flags[0]);
		i++;
	}
	data->cmds[0].first = 1;
	data->cmds[data->cmd_num - 1].last = 1;
}
