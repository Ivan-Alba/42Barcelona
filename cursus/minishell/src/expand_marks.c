/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_marks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:53:07 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/17 14:22:02 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Counts how many variables to expand contains the string and returns the number
int	count_env_var(char *str)
{
	int	i;
	int	num_to_exp;

	num_to_exp = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0'
			&& str[i + 1] != '\'')
			num_to_exp++;
		if (str[i] == '$' && str[i + 1] == '$')
			i++;
	}
	return (num_to_exp);
}

//Creates a new string adding a flag in front of each variable to be expanded
char	*expand_marks(char *str)
{
	int		i;
	int		j;
	char	*result;

	if (count_env_var(str) > 0)
	{
		result = malloc(sizeof(char *)
				* (count_env_var(str) + ft_strlen(str) + 1));
		if (!result)
			return (NULL);
		i = -1;
		j = 0;
		while (str[++i])
		{
			if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0'
				&& str[i + 1] != '\'')
				result[j++] = '\\';
			if (str[i] == '$' && str[i + 1] == '$')
				result[j++] = str[i++];
			result[j++] = str[i];
		}
		result[j] = '\0';
		return (result);
	}
	return (ft_strdup(str));
}
