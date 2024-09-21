/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:29:52 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/05 18:01:55 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 *		Function Name: get_num_env
 *
 *		Description:
 *
 *			The function iterates a char ** to calculate the length.
 *
 *		Parameters:
 *
 *			char **env - The array of pointers with the environment.
 *
 *		Return Value:
 *
 *			int - Returns the total number of environment variables.
 */
int	get_num_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

/*
 *		Function Name: ft_env
 *
 *		Description:
 *
 *			Shows a list of all environment variables.
 *
 *		Parameters:
 *
 *			char	**cmd -	The command and its arguments or flags.
 *			t_data	*data - The pointer to the t_data struct with all
 *							execution data.
 *
 *		Return Value:
 *
 *			int - Returns EXIT_SUCCESS if the executed function finished.
 */
int	ft_env(char **cmd, t_data *data)
{
	int	i;
	int	num_env;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 1)
		return (printf("env: '%s': No such file or directory\n", cmd[1]), 127);
	num_env = get_num_env(data->env);
	i = 0;
	while (i < num_env)
	{
		if (ft_strchr(data->env[i], '='))
			printf("%s\n", data->env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
