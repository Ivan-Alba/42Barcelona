/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:10:36 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/06 16:38:07 by igarcia2         ###   ########.fr       */
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

int	check_non_accepted_chars(t_data *data)
{
	int	i;

	i = 0;
	while (data->prompt[i] != '\0')
	{
		if (data->prompt[i] == ';' || data->prompt[i] == '\\')
			return (1);
		i++;
	}
	return (0);
}

int	check_brackets(t_data *data)
{
	int	bracket_open;
	int	bracket_close;
	int	i;

	i = 0;
	bracket_open = 0;
	bracket_close = 0;
	while (data->prompt[i] != '\0')
	{
		if (data->prompt[i] == '(')
			bracket_open++;
		else if (data->prompt[i] == ')')
		{
			if (bracket_close < bracket_open)
				bracket_close++;
			else
				return (1);
		}
		i++;
	}
	if (bracket_close != bracket_open)
		return (1);
	return (0);
}

int	check_syntax(t_data *data)
{
	if (check_quotes(data))
	{
		print_error(QUOTE_FORMAT_ERROR, NULL);
		return (1);
	}
	if (check_non_accepted_chars(data))
	{
		print_error(INVALID_CHARS_ERROR, NULL);
		return (1);
	}
	if (check_brackets(data))
	{
		print_error(BRACKET_FORMAT_ERROR, NULL);
		return (1);
	}
	return (0);
}
