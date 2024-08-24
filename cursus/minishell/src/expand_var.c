/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:05:50 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/23 17:58:19 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*int	check_var_format(t_data *data, int i)
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
}*/

//Searches for var on environment variable and stores it
char	*get_var_value(char *var, t_data *data)
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
		return (ft_strdup(ft_strchr(data->env[i], '=') + 1));
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

char	*expand(char ***vars, t_data *data)
{
	int		i;
	char	*value;
	char	*result;
	char	*tmp;

	i = -1;
	result = NULL;
	while ((*vars)[++i])
	{
		tmp = result;
		if ((*vars)[i][0] == '$' && (*vars)[i][1] != '\0')
		{
			value = get_var_value(&(*vars)[i][1], data);
			if (!value)
				print_error_exit(MALLOC_ERROR, data);
			result = ft_strcat(result, value);
			free(value);
		}
		else
			result = ft_strcat(result, (*vars)[i]);
		if (tmp)
			free(tmp);
		if (!result)
			print_error_exit(MALLOC_ERROR, data);
	}
	free_split(vars);
	return (result);
}

void	add_new_var(char ***vars, int *i, char *current)
{
	int		len;
	char	*aux;

	len = 1;
	(*i)++;
	while (current[*i] != '$' && current[*i] != '\\' && current[*i] != ' '
		&& current[*i] != '\0')
	{
		len++;
		(*i)++;
	}
	aux = ft_strcut(&(current[(*i) - len]), len);
	(*vars) = add_to_array(vars, aux);
	free(aux);
	(*i)--;
}

char	*trim_env_vars(char *current, t_data *data)
{
	int		i;
	char	*aux;

	i = -1;
	while (current[++i])
	{
		if (current[i] == '\\' && current[i + 1] == '$' && i++ >=0)
			if (current[i + 1] == '$' && i++ >= 0)
			data->expand_vars = add_to_array(&data->expand_vars, "40078");
			else
				add_new_var(&data->expand_vars, &i, current);
		else
		{
			aux = string_from_char(current[i]);
			if (!aux)
				print_error_exit(MALLOC_ERROR, data);
			data->expand_vars = add_to_array(&data->expand_vars, aux);
			free(aux);
		}
		if (!data->expand_vars)
			print_error_exit(MALLOC_ERROR, data);
	}
	free(current);
	return (expand(&data->expand_vars, data));
}

void	expand_vars(t_section *section, t_data *data)
{
	int		i;
	t_files	*curr_file;

	i = 0;

	printf("CMD EXPANDED:\n");
	while (section->cmd && section->cmd[i])
	{
		if (ft_strchr(section->cmd[i], '\\'))
			section->cmd[i] = trim_env_vars(section->cmd[i], data);
		printf("[%d]%s\n", i, section->cmd[i]);
		i++;
	}
	curr_file = section->files;
	printf("FILES EXPANDED:\n");
	while (curr_file)
	{
		if (ft_strchr(curr_file->file_name, '\\'))
			curr_file->file_name = trim_env_vars(curr_file->file_name, data);
		printf("%s\n", curr_file->file_name);
		curr_file = curr_file->next;
	}
}
