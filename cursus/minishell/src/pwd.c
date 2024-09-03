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

/*
*	"pwd" without options:
*
*	char *getcwd(char *buf, size_t size);
*	getcwd: function to get the path of the current working directory
*	returns a pointer to the path or NULL and sets an errno
*
*	getcwd(NULL, 0): will allocate the necessary memory, to have the exact 
*	length of the path without using PATH_MAX
*/

#include "../inc/minishell.h"

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
