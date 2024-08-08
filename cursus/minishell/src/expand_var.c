/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:05:50 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/08 17:13:52 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_var_format(t_data *data, int i)
{
	char	*current;
	int		x;

	current = data->split_info->splitted_prompt[i];
	x = 1;
	while (current[x])
	{
		if (x == 1 && (!(ft_isalpha(current[x])) && current[x] != '_'))
			return (1);
		else if (x > 1 && !(ft_isalnum(current[x])) && current[x] != '_')
			return (1);
		x++;
	}
	return (0);
}

//Searches for var on environment variable and stores it
char	*get_var(t_data *data, char *var)
{
	int		i;
	int		found;
	char	*var_equal;

	found = 0;
	i = 0;
	var_equal = ft_strcat(var, "=");
	if (!var_equal)
		print_error_exit(MALLOC_ERROR, data);
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], var_equal, ft_strlen(var_equal)))
		{
			found = 1;
			break ;
		}
		i++;
	}
	free(var_equal);
	if (found)
	{
		return (ft_strdup(ft_strchr(data->env[i], '=') + 1));
	}
	else
		return (ft_strdup(""));
}

//Searches for the PATH environment variable and stores it
/*void    get_path(char **env, t_pipex *data)
{
        int     i;
        int     found;

        found = 0;
        i = 0;
        while (env[i])
        {
                if (ft_strnstr(env[i], "PATH=", 5))
                {
                        found = 1;
                        break ;
                }
                i++;
        }
        if (found)
        {
                data->path = ft_split(env[i] + 5, ':');
                if (!data->path)
                        free_data(data, "Malloc error\n");
        }
        else
                data->path = NULL;
}*/

int	expand(t_data *data, int i)
{
	char	*value;

	if (check_var_format(data, i))
		return (1);
	value = get_var(data, &(data->split_info->splitted_prompt[i][1]));
	free(data->split_info->splitted_prompt[i]);
	data->split_info->splitted_prompt[i] = value;
	return (0);
}

int	expand_var(t_data *data)
{
	int		single_quote;
	int		double_quote;
	int		i;
	char	*current;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	current = data->split_info->splitted_prompt[i];
	while (current)
	{
		if (current[0] == '\'' && double_quote % 2 == 0)
			single_quote++;
		else if (current[0] == '"' && single_quote % 2 == 0)
			double_quote++;
		else if (current[0] == '$' && single_quote % 2 == 0)
		{
			if (expand(data, i))
			{
				print_error(INVALID_VAR_NAME, NULL);
				free_split(&(data->split_info->splitted_prompt));
				return (1);
			}
		}
		current = data->split_info->splitted_prompt[++i];
	}
	return (0);
}
