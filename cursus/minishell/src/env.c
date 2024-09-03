/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:29:52 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/03 16:45:39 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	"env" without options or arguments:
*
*	Shows a list of all environment variables
*
*	char *getenv(const char *name);
*	getenv: to obtain the value of each existing env variable and then print it	
*/
#include "../inc/minishell.h"

//to obtain the total number of environment variables
int	get_num_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

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
		printf("%s\n", data->env[i++]);
	return (EXIT_SUCCESS);
}
