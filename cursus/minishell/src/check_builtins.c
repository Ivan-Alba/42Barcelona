/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:58:17 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/03 16:48:42 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_if_builtin(char *command)
{
	if (ft_strncmp(command, ECHO, 5) == 0)
		return (1);
	//else if (ft_strncmp(command, CD) == 0)
		//return (1);
	else if (ft_strncmp(command, PWD, 4) == 0)
		return (1);
	//else i.f (ft_strncmp(command, EXPORT, 7) == 0)
		//return (1);
	if (ft_strncmp(command, UNSET, 6) == 0)
		return (1);
	else if (ft_strncmp(command, ENV, 4) == 0)
		return (1);
	//else if (ft_strncmp(command, EXIT, 5) == 0)
		//return (1);
	return (0);
}

//data->env tienes las variables de entorno
//si tienes un fallo de malloc o algo, print_error_exit(FALLO, data);
void	execute_builtin(char **cmd, t_data *data)
{
	if (ft_strncmp(cmd[0], ECHO, 5) == 0)
		data->last_exit_status = ft_echo(cmd);
	//else if (ft_strncmp(cmd[0], CD, 3) == 0)
	//	data->last_exit_status = ft_cd(cmd, data);
	else if (ft_strncmp(cmd[0], PWD, 4) == 0)
		data->last_exit_status = ft_pwd(cmd, data);
	//else if (ft_strncmp(cmd[0], EXPORT, 7) == 0)
	//	data->last_exit_status = ft_export(cmd, data);
	if (ft_strncmp(cmd[0], UNSET, 6) == 0)
		data->last_exit_status = ft_unset(cmd, data);
	else if (ft_strncmp(cmd[0], ENV, 4) == 0)
		data->last_exit_status = ft_env(cmd, data);
	//else if (ft_strncmp(cmd[0], EXIT, 5) == 0)
	//	data->last_exit_status = ft_exit(cmd, data);
}
