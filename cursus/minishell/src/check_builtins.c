/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:58:17 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/29 20:17:21 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_if_builtin(char *command)
{
	(void) command;
	//if (ft_strncmp(command, ECHO) == 0)
		//return (1);
	//else if (ft_strncmp(command, CD) == 0)
		//return (1);
	//else if (ft_strncmp(command, PWD) == 0)
		//return (1);
	//else if (ft_strncmp(command, EXPORT) == 0)
		//return (1);
	//else if (ft_strncmp(command, UNSET) == 0)
		//return (1);
	//else if (ft_strncmp(command, ENV) == 0)
		//return (1);
	//else if (ft_strncmp(command, EXIT) == 0)
		//return (1);
	return (0);
}

//data->env tienes las variables de entorno
//si tienes un fallo de malloc o algo, print_error_exit(FALLO, data);
int	execute_builtin(char **cmd, t_data *data)
{
	(void) cmd;
	(void) data;
	//if (ft_strncmp(cmd[0], ECHO, 5) == 0)
		//return (ft_echo(cmd, data));
	//else if (ft_strncmp(cmd[0], CD, 3) == 0)
		//return (ft_cd(cmd, data));
	//else if (ft_strncmp(cmd[0], PWD, 4) == 0)
		//return (ft_pwd(cmd, data));
	//else if (ft_strncmp(cmd[0], EXPORT, 7) == 0)
		//return (ft_export(cmd, data));
	//else if (ft_strncmp(cmd[0], UNSET, 6) == 0)
		//return (ft_unset(cmd, data));
	//else if (ft_strncmp(cmd[0], ENV, 4) == 0)
		//return (ft_env(cmd, data));
	//else if (ft_strncmp(cmd[0], EXIT, 5) == 0)
		//return (ft_exit(cmd, data));
	return (0);
}
