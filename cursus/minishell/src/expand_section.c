/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_section.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:05:50 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/23 17:58:19 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 *	Function Name: expand_vars
 *
 *	Description:
 *		This function creates the resulting string with all the values of the
 *		expanded environment variables.
 *		It will be the final value stored in the t_section.
 *
 *	Parameters:
 *		t_data *data	- The pointer to the t_data struct with all
 *							the execution data.
 *	Return value:
 *		char *expanded_str - The string resulting from the whole process of
 *								expanding environment variables.
 */
char	*expand_vars(t_data *data)
{
	int		i;
	char	*expanded_str;
	char	*tmp;

	i = -1;
	expanded_str = NULL;
	while (data->expand_vars[++i])
	{
		tmp = expanded_str;
		if (data->expand_vars[i][0] == '$' && data->expand_vars[i][1] != '\0')
			concat_var_value(&expanded_str, &data->expand_vars[i][1], data);
		else
			expanded_str = ft_strcat(expanded_str, data->expand_vars[i]);
		if (tmp)
			free(tmp);
		if (!expanded_str)
			print_error_exit(MALLOC_ERROR, data);
	}
	return (expanded_str);
}

/**
 *	Function Name: add_new_var
 *
 *	Description:
 *		This function calculates the length of the environment variable and calls
 *		the ft_strcut function to make a copy of it and add it to the char** into
 *		the t_data struct of variables to be expanded.
 *
 *	Parameters:
 *		int *i			- The pointer to the index of the string where the
 *							environment variable starts.
 *		char *str		- The string that contains the unexpanded variables.
 *		t_data *data	- The pointer to the t_data struct with all
 *							the execution data.
 */
void	add_new_var(int *i, char *str, t_data *data)
{
	int		len;
	char	*aux;

	len = 1;
	(*i)++;
	while (str[*i] != '$' && str[*i] != '\\' && str[*i] != ' '
		&& str[*i] != '\0')
	{
		len++;
		(*i)++;
	}
	aux = ft_strcut(&(str[(*i) - len]), len);
	data->expand_vars = add_to_array(&data->expand_vars, aux);
	free(aux);
	(*i)--;
}

/**
 *	Function Name: trim_vars
 *
 *	Description:
 *		This function manages the splitting of environment variables or characters
 *		that are not part of them, with the help of other auxiliary functions, and
 *		stores them in a char** into the t_data struct.
 *
 *	Parameters:
 *		char *str		- The string that contains the unexpanded variables.
 *		int *i			- The pointer to the current index of the string.
 *		t_data *data	- The pointer to the t_data struct with all
 *							the execution data.
 */
void	trim_vars(char *str, int *i, t_data *data)
{
	char	*tmp;

	if (str[*i] == '\\' && str[*i + 1] == '$' && (*i)++ >= 0)
	{
		if (str[*i + 1] == '$' && (*i)++ >= 0)
			data->expand_vars = add_to_array(&data->expand_vars, "40078");
		else if (str[*i + 1] == '?' && (*i)++ >= 0)
		{
			tmp = ft_itoa(data->last_exit_status);
			if (!tmp)
				print_error_exit(MALLOC_ERROR, data);
			data->expand_vars = add_to_array(&data->expand_vars, tmp);
			free(tmp);
		}
		else
			add_new_var(i, str, data);
	}
	else
	{
		tmp = string_from_char(str[*i]);
		if (!tmp)
			print_error_exit(MALLOC_ERROR, data);
		data->expand_vars = add_to_array(&data->expand_vars, tmp);
		free(tmp);
	}
}

/**
 *	Function Name: get_str_expanded
 *
 *	Description:
 *		This function scans the string that contains the environment variables
 *		to be expanded. It calls the function in charge of splitting them and
 *		then the function in charge of expanding them.
 *		It frees the memory of the original string and returns the new string
 *		with the values of the variables.
 *
 *	Parameters:
 *		char *str		- The string that contains the unexpanded variables.
 *		t_data *data	- The pointer to the t_data struct with all
 *							the execution data.
 *	Return Value:
 *		char *str_expanded	-The string with the expanded values.
 *
 *	Example:
 *		str = "I'm the user \$USER and i'm in the directory \$PWD"
 *		str_expanded = "I'm the user igarcia2 and i'm in the directory
 *						/home/igarcia2" 
 */
char	*get_str_expanded(char *str, t_data *data)
{
	int		i;
	char	*str_expanded;

	i = -1;
	while (str[++i])
	{
		trim_vars(str, &i, data);
		if (!data->expand_vars)
			print_error_exit(MALLOC_ERROR, data);
	}
	free(str);
	str_expanded = expand_vars(data);
	free_split(&data->expand_vars);
	return (str_expanded);
}

/**
 *	Function Name: expand_section
 *
 *	Description:
 *		This function searches in the command (section->cmd) and filename
 *		(section->files->file_name) strings of each section for the flag (\)
 *		previously set in the @ref expand_marks function and calls the @ref
 *		get_str_expanded function to expand the environment variables they contain.
 *
 *	Parameters:
 *		t_section *section	- The pointer to the section from which to expand its
 *								variables.
 *		t_data *data		- The pointer to the t_data struct with all
 *								the execution data.
 *
 */
void	expand_section(t_section *section, t_data *data)
{
	int		i;
	t_files	*curr_file;

	i = 0;
	while (section->cmd && section->cmd[i])
	{
		if (ft_strchr(section->cmd[i], '\\'))
			section->cmd[i] = get_str_expanded(section->cmd[i], data);
		i++;
	}
	curr_file = section->files;
	while (curr_file)
	{
		if (ft_strchr(curr_file->file_name, '\\'))
			curr_file->file_name = get_str_expanded(curr_file->file_name, data);
		curr_file = curr_file->next;
	}
}
