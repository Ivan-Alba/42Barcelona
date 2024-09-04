/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:31:40 by igarcia2          #+#    #+#             */
/*   Updated: 2024/09/02 16:38:50 by igarcia2         ###   ########.fr       */
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
		exit(0);
	}
}

// Función para registrar el manejador de señales y pasar la estructura data
void	setup_signal_handler(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	//sigaddset(&sa.sa_mask, SIGTERM);
	//sigaddset(&sa.sa_mask, SIGINT);
	//sigaddset(&sa.sa_mask, SIGQUIT);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("sigaction");
}
