/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinatacconis <carolinatacconis@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:26:20 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/20 12:08:46 by carolinatac      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	print_error_many_args(void)
{
	ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
	ft_putendl_fd(" cd : too many arguments", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	print_error_not_set(void)
{
	ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
	ft_putendl_fd(" cd: HOME not set", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	print_error_no_file(char *cmd)
{
	ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
	ft_putstr_fd(" cd: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	print_error_oldpwd(void)
{
	ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
	ft_putendl_fd(" cd: OLDPWD not set", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	print_error_permission(char *dir_name)
{
	ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
	ft_putstr_fd(" cd: ", STDERR_FILENO);
	ft_putstr_fd(dir_name, STDERR_FILENO);
	ft_putendl_fd(": permission denied", STDERR_FILENO);
	return (EXIT_FAILURE);
}
