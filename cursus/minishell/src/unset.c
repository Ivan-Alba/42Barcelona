/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:35:54 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/02 20:52:02 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	"unset" without options:
*	
*	unset [no options] VARIABLE_NAME
*	- Removes the environment variables with the given keys
*		after checking if they are valid keys.
*	- Does nothing if the key is not in the environment.
*	
*	Returns 0 if all args were successfully unset, or 1 if
*	one or more args could not be unset.
*/

#include "../inc/minishell.h"

int	is_flag(char *str)
{
	int	i;

	i = 1;
	if (*str != '-')
		return (0);
	if (*str == '-' && *(str + 1) == '\0')
		return (0);
	while (str[i] && ft_isalpha(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

//num_env: the array position of the KEY=VALUE to remove
int	ft_cmp_varname(char *s, char **env, int *num_env)
{
	int	i;
	int	j;

	i = 0;
	while (env && env[i])
	{
		j = 0;
		while (s[j] && env[i][j] && env[i][j] != '=' && s[j] == env[i][j])
			j++;
		if (s[j] == '\0' && env[i][j] == '=')
		{
			*num_env = i;
			return (0);
		}
		i++;
	}
	return (1);
}

void	remove_var(char **env, int *num_env)
{
	int	j;

	j = *num_env;
	while ((*num_env >= 0) && (env[j]))
	{
		if (j == *num_env)
			free(env[j]);
		env[j] = env[j + 1];
		j++;
	}
	env[j - 1] = NULL;
}

int	ft_unset(char **cmd, t_data *data)
{
	int	i;
	int	num_env;

	num_env = 0;
	i = 0;
	while (cmd[i])
		i++;
	if (i == 1)
		return (EXIT_SUCCESS);
	i = 1;
	while (cmd[i] && cmd)
	{
		if (is_flag(cmd[1]))
		{
			printf("%s unset: %c%c: invalid option\n", PROGRAM_NAME,
				*(cmd[i]), *(cmd[i] + 1));
			printf("unset: usage: unset [no options admitted] [name ...]\n");
			return (2);
		}
		else if (ft_cmp_varname(cmd[i], data->env, &num_env) == 0)
			remove_var(data->env, &num_env);
		i++;
	}
	return (EXIT_SUCCESS);
}
