/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:26:20 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/23 13:11:21 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_error_many_args_exit(int *exit_code)
{
	ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
	ft_putendl_fd(" exit: too many arguments", STDERR_FILENO);
	*exit_code = 1;
	return (*exit_code);
}

int	print_error_num_arg(int *exit_code, char *cmd)
{
	ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
	ft_putstr_fd(" exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	*exit_code = 2;
	return (*exit_code);
}
