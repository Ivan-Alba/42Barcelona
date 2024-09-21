/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinatacconis <carolinatacconis@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:01:54 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/20 12:26:00 by carolinatac      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 *		Function Name: my_getenv
 *
 *		Description:
 *
 *			This function searches the environment list to find the
 *  		environment variable name, as "getenv".
 *
 *		Parameters:
 *
 * 			char   *env  -  The variable name to find.
 *			t_data *data -  The pointer to the t_data struct with all the
 *							environment data.
 *		
 *		Return Value:
 *
 *			char * - Returns a pointer to the variable name in the list or
 *					 NULL if there is no match.
 */
char	*my_getenv(char *env, t_data *data)
{
	int		pos;
	char	*abs_path;

	pos = 0;
	if (!env)
		return (NULL);
	pos = check_if_exist(env, data);
	if (pos > 0)
	{
		abs_path = ft_strchr(data->env[pos], '=');
		if (abs_path)
			return (abs_path + 1);
		return (NULL);
	}
	else
		return (NULL);
}

/*
 *		Function Name: is_relative_path
 *
 *		Description:
 *
 *			This function checks if a relative path has been passed as
 *			an argument, if it can be accessed and if the directory 
 *			can finally be changed.
 *
 *		Parameters:
 *
 *			char   *cmd -	The string with the path.
 *			t_data *data -  The pointer to the t_data struct with all the
 *							environment data.
 *
 *		Return Value:
 *
 *			int - Returns 1 if something went wrong or 0 if it is a
 *			      valid pathname.
 */
int	is_relative_path(char *cmd, t_data *data)
{
	char	*current_dir;
	char	*new_path;
	char	*tmp_path;

	current_dir = getcwd(NULL, 0);
	tmp_path = ft_strjoin(current_dir, "/");
	malloc_protection(tmp_path, data);
	new_path = ft_strjoin(tmp_path, cmd);
	malloc_protection(new_path, data);
	free(tmp_path);
	if (access(new_path, F_OK) == -1)
	{
		free(current_dir);
		free(new_path);
		return (print_error_no_file(cmd));
	}
	if (chdir(new_path) == -1)
	{
		free(current_dir);
		free(new_path);
		return (print_error_permission(cmd));
	}
	return (free(current_dir), free(new_path), 0);
}

/*
 *		Function Name: change_directory
 *
 *		Description:
 *
 *			This function changes the current directory.
 *
 *		Parameters:
 *
 *			char   *path -	The string with the path.
 *			t_data *data -  The pointer to the t_data struct with all the
 *							environment data.
 *
 *		Return Value:
 *
 *			int - Returns 1 if something went wrong or 0 if it has a
 *				  valid pathname.
 */
int	change_directory(char *path, t_data *data)
{
	char	*new_pwd;

	new_pwd = NULL;
	set_oldpwd(data);
	if (chdir(path) == -1)
	{
		if (is_relative_path(path, data) != 0)
			return (EXIT_FAILURE);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		change_dir_my_env(NULL, new_pwd, data);
		free(new_pwd);
	}
	return (EXIT_SUCCESS);
}

/*
 *		Function Name: ft_cd
 *
 *		Description:
 *
 *			This function is the main structure where other functions are
 *			called depending on the arguments passed to the command.
 *
 *		Parameters:
 *
 *			char	**cmd    - The command and its arguments or flags.
 *			t_data	*data	 - The pointer to the t_data struct with all
 *							   environment data.
 *
 *		Return Value:
 *
 *			int - Returns EXIT_SUCCESS if the executed function finished
 *				  or EXIT_FAILURE if something went wrong during the process.
 */
int	ft_cd(char **cmd, t_data *data)
{
	if (cmd[1] && cmd[2])
		return (print_error_many_args());
	else if (!cmd[1] || !ft_strncmp(cmd[1], "--", 3)
		|| (*cmd[1] == '~' && cmd[1][1] == '\0'))
	{
		set_oldpwd(data);
		if (chdir(my_getenv("HOME", data)) == -1)
			return (print_error_not_set());
		change_dir_my_env(NULL, my_getenv("HOME", data), data);
		return (EXIT_SUCCESS);
	}
	else if (**(cmd + 1) == '\0')
		return (EXIT_SUCCESS);
	else if (cmd[1][0] == '-' && cmd[1][1] == '\0')
	{
		if (swap_dir(cmd, data))
			return (EXIT_FAILURE);
	}
	else if (*cmd[1] == '~')
		return (expand_cd(cmd[1], data));
	else
		return (change_directory(cmd[1], data));
	return (EXIT_SUCCESS);
}
