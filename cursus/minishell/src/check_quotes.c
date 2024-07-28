/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:10:36 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/28 18:37:44 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_quotes(t_data	*data)
{
	int	i;
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (data->prompt[i] != '\0')
	{
		if (data->prompt[i] == '"' && single_quote % 2 == 0)
			double_quote += 1;
		if (data->prompt[i] == '\'' && double_quote % 2 == 0)
			single_quote += 1;
		i++;
	}
	if (single_quote % 2 || double_quote % 2)
		return (1);
	return (0);
}

int	check_syntax(t_data *data)
{
	if (check_quotes(data))
	{
		print_error("Error: Incorrect quoting mark format");
		return (1);
	}
	return (0);
}
