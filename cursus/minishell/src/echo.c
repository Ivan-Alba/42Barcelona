/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:26:20 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/03 16:44:21 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	"echo" with the option -n:
*
*	When the user writes "echo" in the shell, the function replicates the
*	behaviour of the echo command without the need to run an external process,
*	i.e., the code handle this command directly without calling /bin/echo.
*
*	When the -n option is used, the trailing newline is suppressed.
*/

#include "../inc/minishell.h"

//Is checked if the -n flag is passed as an argument
int	is_nflag(char *str)
{
	int	i;

	i = 1;
	if (*str != '-')
		return (0);
	if (str[i] != 'n')
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (!cmd[i])
		return (printf("\n"), 0);
	while (cmd[i] && is_nflag(cmd[i]))
	{
		n_flag = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i++]);
		if (cmd[i])
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	return (EXIT_SUCCESS);
}
