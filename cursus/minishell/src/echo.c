/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctacconi <ctacconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:26:20 by ctacconi          #+#    #+#             */
/*   Updated: 2024/09/03 16:44:21 by ctacconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 *		Function Name: is_nflag
 *
 *		Description:
 *
 *			This function checks if with the built-in echo is passed 
 *			the ‘-n’ option. If so, the line break will be suppressed.
 *
 *		Parameters:
 *
 *			char		*str    - The argument passed from echo.
 *		Return Value:
 *
 *			int - Returns 1 if the command is "-n" and 0 if it is not.
 */
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

/*
 *		Function Name: ft_echo
 *
 *		Description:
 *
 *			Write arguments to the standard output.
 *   
 *   		Display the ARGs, separated by a single space character and followed by a
 *   		newline, on the STDOUT.
 *
 *		Parameters:
 *
 *			char	**cmd -	The command and its arguments or flags.
 *		Return Value:
 *
 *			int - Returns EXIT_SUCCESS if the executed function finished.
 */
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
