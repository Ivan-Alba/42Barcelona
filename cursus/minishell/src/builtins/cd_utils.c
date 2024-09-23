/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinatacconis <carolinatacconis@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:01:54 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/23 17:29:13 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 *		Function Name: change_dir_my_env
 *
 *		Description:
 *
 *			This function updates the paths stored in the OLDPWD
 *			or PWD variables.
 *
 *		Parameters:
 *
 *			char *oldpwd - The string with the oldpwd path to set.
 *			char *pwd    - The string with the pwd path to set.
 *			t_data *data -  The pointer to the t_data struct with all the
 *							environment data.
 */
void	change_dir_my_env(char *old_pwd, char *pwd, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->env && data->env[i])
	{
		if (old_pwd && !ft_strncmp(data->env[i], "OLDPWD", 6))
		{
			tmp = ft_strjoin("OLDPWD=", old_pwd);
			malloc_protection(tmp, data);
			free(data->env[i]);
			data->env[i] = tmp;
		}
		else if (pwd && !ft_strncmp(data->env[i], "PWD", 3))
		{
			tmp = ft_strjoin("PWD=", pwd);
			malloc_protection(tmp, data);
			free(data->env[i]);
			data->env[i] = tmp;
		}
		i++;
	}
}

/*
 *		Function Name: set_oldpwd
 *
 *		Description:
 *
 *			This function updates the oldpwd before doing the directory change.
 *
 *		Parameters:
 *
 *			t_data *data -  The pointer to the t_data struct with all the
 *							environment data.
 */
void	set_oldpwd(t_data *data)
{
	char	*oldpwd;

	oldpwd = NULL;
	oldpwd = getcwd(NULL, 0);
	if (oldpwd)
	{
		if (my_getenv("OLDPWD", data) == NULL)
		{
			data->env = add_to_array(&data->env, "OLDPWD=");
			malloc_protection(data->env, data);
		}
		change_dir_my_env(oldpwd, NULL, data);
		free(oldpwd);
	}
	else
	{
		write(2, "cd: error retrieving current directory: getcwd: ", 48);
		perror("cannot access parent directories");
	}
}

/*
 *		Function Name: swap_dir
 *
 *		Description:
 *
 *			This function swaps the paths when "cd -" is called.
 *
 *		Parameters:
 *
 * 			char   **cmd - The command and its arguments or flags.
 *			t_data *data -  The pointer to the t_data struct with all the
 *							environment data.
 *		
 *		Return Value:
 *
 *			int - Returns 0 if it has been properly executed.
 */
int	swap_dir(char **cmd, t_data *data)
{
	char	*new_pwd;
	char	*new_old;

	new_pwd = NULL;
	new_old = NULL;
	new_old = getcwd(NULL, 0);
	if (my_getenv("OLDPWD", data) == NULL)
		return (free(new_old), print_error_oldpwd());
	if (chdir(my_getenv("OLDPWD", data)) == -1)
		return (free(new_old), print_error_no_file(my_getenv("OLDPWD", data)));
	change_dir_my_env(new_old, NULL, data);
	new_pwd = getcwd(NULL, 0);
	change_dir_my_env(NULL, new_pwd, data);
	free(new_old);
	free(new_pwd);
	ft_pwd(cmd, data);
	return (0);
}

/*
 *		Function Name: expand_path
 *
 *		Description:
 *
 *			The path to home is expanded when "~" is called.
 *
 *		Parameters:
 *
 * 			char   *exp  -  The path to expand.
 *			t_data *data -  The pointer to the t_data struct with all the
 *							environment data.
 *		
 *		Return Value:
 *
 *			char * - Returns the path expanded.
 */
char	*expand_path(char *exp, t_data *data)
{
	char	*path;
	char	*home;

	if (!exp || *exp != '~')
		return (NULL);
	home = my_getenv("HOME", data);
	if (!home)
	{
		print_error_not_set();
		return (NULL);
	}
	path = ft_strjoin(home, exp + 1);
	malloc_protection(path, data);
	return (path);
}

/*
 *		Function Name: expand_cd
 *
 *		Description:
 *
 *			Once we get the expanded path we update the variables
 *			pwd and oldpwd.
 *
 *		Parameters:
 *
 *			char	**cmd    - The command and its arguments or flags.
 *			t_data	*data	 - The pointer to the t_data struct with all
 *									execution data.
 * 
 *		Return Value:
 *
 *			int - Returns EXIT_SUCCESS if the executed function finished
 *				  or EXIT_FAILURE if something went wrong during the process.
 */
int	expand_cd(char *cmd, t_data *data)
{
	char	*expanded;
	char	*new_pwd;

	expanded = expand_path(cmd, data);
	if (!expanded)
		return (EXIT_FAILURE);
	set_oldpwd(data);
	if (chdir(expanded) == -1)
	{
		free(expanded);
		return (print_error_no_file(cmd));
	}
	free (expanded);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		change_dir_my_env(NULL, new_pwd, data);
		free(new_pwd);
	}
	return (EXIT_SUCCESS);
}
