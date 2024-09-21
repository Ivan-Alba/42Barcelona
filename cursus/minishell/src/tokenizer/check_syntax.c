/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:10:36 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/17 15:37:39 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 *		Function Name:	check_quotes
 *
 *		Description:
 *
 *			This function checks if the prompt entered by the user has the
 *			quotes correctly closed.
 *
 *		Parameters:
 *
 *			t_data	*data	-	The pointer to the t_data struct with all
 *								execution data.
 *		Return Value:
 *
 *			int - Returns 0 if the format is correct and 1 if it is not.
 */
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

/**
 *		Function Name:	check_brackets
 *
 *		Description:
 *
 *			This function checks if the prompt entered by the user has the
 *			brackets correctly closed.
 *
 *		Parameters:
 *
 *			t_data	*data	-	The pointer to the t_data struct with all
 *								execution data.
 *		Return Value:
 *
 *			int - Returns 0 if the format is correct and 1 if it is not.
 */
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

/**
 *		Function Name:	check_syntax
 *
 *		Description:
 *
 *			This function is in charge of calling the different functions that
 *			checks the syntax of the prompt entered by the user.
 *
 *		Parameters:
 *
 *			t_data	*data	-	The pointer to the t_data struct with all
 *								execution data.
 *		Return Value:
 *
 *			int - Returns 0 if the format is correct and 1 if it is not.
 */
int	check_syntax(t_data *data)
{
	char	*error;

	error = NULL;
	if (check_quotes(data))
		error = QUOTE_FORMAT_ERROR;
	if (check_brackets(data))
		error = BRACKET_FORMAT_ERROR;
	if (error)
	{
		data->last_exit_status = 2;
		print_error(error, NULL);
		return (1);
	}
	return (0);
}
