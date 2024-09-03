/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:05:50 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/29 17:25:55 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	single_quote_exp(char *str, char **str_exp, int *i, t_data *data)
{
	*str_exp = ft_free_strcat(*str_exp, ft_strdup("\'"));
	malloc_protection(*str_exp, data);
	while (str[++(*i)] != '\'')
	{
		*str_exp = ft_free_strcat(*str_exp, string_from_char(str[*i]));
		malloc_protection(*str_exp, data);
	}
	*str_exp = ft_free_strcat(*str_exp, ft_strdup("\'"));
	malloc_protection(*str_exp, data);
}

void	double_quote_exp(char *str, char **str_exp, int *i, t_data *data)
{
	char	*var_name;
	char	*var_value;

	*str_exp = ft_free_strcat(*str_exp, ft_strdup("\""));
	malloc_protection(*str_exp, data);
	while (str[++(*i)] != '"')
	{
		if (str[*i] == '$')
		{
			var_name = expand_var(str, str_exp, i, data);
			if (var_name)
			{
				var_value = get_var_value(&var_name, data, 1);
				if (var_value)
					*str_exp = ft_free_strcat(*str_exp, var_value);
			}
		}
		else
		{
			*str_exp = ft_free_strcat(*str_exp, string_from_char(str[*i]));
			malloc_protection(*str_exp, data);
		}
	}
	*str_exp = ft_free_strcat(*str_exp, ft_strdup("\""));
	malloc_protection(*str_exp, data);
}

void	no_quote_exp(char *str, char **str_exp, int *i, t_data *data)
{
	char	*var_name;
	char	*var_value;

	if (str[*i] == '$')
	{
		var_name = expand_var(str, str_exp, i, data);
		if (var_name)
		{
			var_value = get_var_value(&var_name, data, 0);
			if (var_value)
				*str_exp = ft_free_strcat(*str_exp, var_value);
		}
	}
	else
	{
		*str_exp = ft_free_strcat(*str_exp, string_from_char(str[*i]));
		malloc_protection(*str_exp, data);
	}
}
