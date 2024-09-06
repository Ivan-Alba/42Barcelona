/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:31:40 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/05 18:04:32 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_signal(int signal)
{
	int	g_signal_received;

	g_signal_received = signal;
	if (g_signal_received == SIGINT)
	{
		write(2, "\n", 1);
		exit(130);
	}
}

void	handle_signal_prompt(int signal)
{
	int	g_signal_received;

	g_signal_received = signal;
	if (g_signal_received == SIGINT)
	{
		write(1, "\nminishell: ", 12);
	}
}
