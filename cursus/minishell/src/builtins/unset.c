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

#include "../../inc/minishell.h"

/*
 *		Function Name: is_flag
 *
 *		Description:
 *
 *			This function checks if with the built-in unset is passed 
 *			an option.
 *
 *		Parameters:
 *
 *			char		*str    - The argument passed from unset.
 *
 *		Return Value:
 *
 *			int - Returns 1 if the argument is a flag and 0 if it is not.
 */
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

/*
 *		Function Name: ft_cmp_varname
 *
 *		Description:
 *
 *			Check that the variable passed as an argument actually matches
 *			one of the variables in data->env.
 *
 *		Parameters:
 *
 *			char	*s    - The argument passed from unset.
 *			char	**env - The array of pointers with the environment.
 *			int     *num_env -  The position in the array of env, where is
 *								 located the existing KEY variable.
 *
 *		Return Value:
 *
 *			int - Returns 0 if there is a match.
 */
int	ft_cmp_varname(char *s, char **env, int *num_env)
{
	int	i;
	int	j;

	i = 0;
	if (!s | !*s)
		return (1);
	while (env && env[i])
	{
		j = 0;
		while (s[j] && env[i][j] && env[i][j] != '=' && s[j] == env[i][j])
			j++;
		if (s[j] == '\0' && (env[i][j] == '=' || env[i][j] == '\0'))
		{
			*num_env = i;
			return (0);
		}
		i++;
	}
	return (1);
}

/*
 *		Function Name: remove_var
 *
 *		Description:
 *
 *			Frees the pointer of the KEY to be removed and moves all subsequent
 *			strings, one position -1.
 *
 *		Parameters:
 *
 *			char  **env    - The array of pointers to the environment variables.
 *			int   *num_env - The position in the array of env, where is
 *								 located the existing KEY variable.
 */
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

/*
 *		Function Name: ft_unset
 *
 *		Description:
 *
 *			Removes the environment variables with the given keys
 *			after checking if they are valid keys.
 *			Does nothing if the key is not in the environment.
 *
 *		Parameters:
 *
 *			char	**cmd -	The command and its arguments or flags.
 *			t_data	*data - The pointer to the t_data struct with the
 *							env data.
 *
 *		Return Value:
 *
 *			int - Returns EXIT_SUCCESS if all args were successfully unset.
 */
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
