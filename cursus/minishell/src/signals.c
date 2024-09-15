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
	if (signal == SIGINT)
	{
		printf("\n");
		exit(130);
	}
}

void	handle_signal_prompt(int signal)
{
	g_signal_received = signal;
	if (g_signal_received == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
