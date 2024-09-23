/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:26:20 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/03 16:44:21 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 *		Function Name: check_llong
 *
 *		Description:
 *
 *			This function receives a string and after all.
 *
 *		Parameters:
 *
 *			const char *str -	The string to compare.
 *
 *		Return Value:
 *
 *			int - Returns 1 if the string is a valid number and 0 if it is not.
 */
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

/*
 *		Function Name: check_max_min_llong
 *
 *		Description:
 *
 *			This function receives a string and checks that it is, converted to
 *			a number, within the long long int limits (LLONG MIN - LLONG MAX).
 *
 *		Parameters:
 *
 *			const char *str -	The string to check.
 *
 *		Return Value:
 *
 *			int - Returns 1 if the string is within the range and 0 if not.
 */
int	check_max_min_llong(const char *str)
{
	int		len;
	int		i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	len = ft_strlen(&(str[i]));
	if (len > 19)
		return (0);
	if (len < 19)
		return (1);
	if (str[0] == '-')
	{
		if (ft_strncmp("9223372036854775808", &(str[i]), len) < 0)
			return (0);
	}
	else
	{
		if (ft_strncmp("9223372036854775807", &(str[i]), len) < 0)
			return (0);
	}
	return (1);
}

/*
 *		Function Name: ft_atoll
 *
 *		Description:
 *
 *			This function receives a string that has already passed 
 *			all the necessary checks, and converts it from char 
 *			to long long int.
 *
 *		Parameters:
 *
 *			const char *str -	The string to be converted.
 *
 *		Return Value:
 *
 *			long long - Returns the long long int.
 */
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

/*
 *		Function Name: ft_exit
 *
 *		Description:
 *
 *			This function causes normal process termination and the
 *      	least significant byte of status is
 *     		returned to the parent.
 *
 *		Parameters:
 *
 *			char	**cmd -	The command and its arguments or flags.
 *			t_data	*data - The pointer to the t_data struct with all
 *							execution data.
 *
 *		Return Value:
 *
 *			int - Returns EXIT_SUCCESS if the executed function finished
 *				  or EXIT_FAILURE if something went wrong during the process.
 */
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
