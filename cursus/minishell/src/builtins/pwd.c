/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:31:18 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/03 16:44:38 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 *		Function Name: ft_pwd
 *
 *		Description:
 *
 *			This function prints the full filename 
 *			of the current working directory.
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
int	ft_pwd(char **cmd, t_data *data)
{
	char	*cwd;

	(void)cmd;
	(void)data;
	cwd = NULL;
	cwd = getcwd(NULL, 0);
	if (cwd)
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
		return (EXIT_FAILURE);
	free(cwd);
	return (EXIT_SUCCESS);
}
