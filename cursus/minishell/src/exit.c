/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:26:20 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/03 16:44:21 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*		int isatty(int fd);
* returns 1: fd is an open fd referring to a terminal.
* returns 0: set errno.
*/

/*
*	el builtin exit en bash solo utiliza los 8 bits - significativos del numero
*	que se pasa como codigo de salida
*	LLONG MIN: -9223372036854775808
*	LLONG MAX: 9223372036854775807
*/

#include "../inc/minishell.h"

int	check_llong(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_max_min_llong(char *str)
{
	int		len;
	char	*str_to_check;

	str_to_check = str;
	if (str_to_check[0] == '-' || str_to_check[0] == '+')
		str_to_check++;
	len = ft_strlen(str_to_check);
	if (len > 19)
		return (0);
	if (len < 19)
		return (1);
	if (str[0] == '-')
	{
		if (ft_strncmp("9223372036854775808", str_to_check, len) < 0)
			return (0);
	}
	else
	{
		if (ft_strncmp("9223372036854775807", str_to_check, len) < 0)
			return (0);
	}
	return (1);
}

long long	ft_atoll(const char *str)
{
	int			j;
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	j = 0;
	while ((str[j] >= 9 && str[j] <= 13) || (str[j] == 32))
		j++;
	if (str[j] == '-' || str[j] == '+')
	{
		if (str[j] == '-')
			sign *= -1;
		j++;
	}
	while (str[j] && (str[j] >= '0' && str[j] <= '9'))
	{
		res *= 10;
		res += str[j] - '0';
		j++;
	}
	return (res * sign);
}

int	ft_exit(char **cmd, t_data *data)
{
	int	argc;
	int	exit_code;

	argc = 0;
	exit_code = 0;
	while (cmd && cmd[argc])
		argc++;
	if (isatty(STDIN_FILENO) && !data->is_child)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (cmd[1])
	{
		if (check_llong(cmd[1]) && check_max_min_llong(cmd[1]))
		{
			exit_code = ft_atoll(cmd[1]);
			if (exit_code > 255 || exit_code < 0)
				exit_code = exit_code % 256;
		}
		else
			return (print_error_num_arg(&exit_code, cmd[1]));
	}
	if (argc > 2)
		return (print_error_many_args_exit(&exit_code));
	free_data(data);
	exit(exit_code);
	return (EXIT_SUCCESS);
}
