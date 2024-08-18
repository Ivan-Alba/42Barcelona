/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:30:27 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/17 18:24:36 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Function that initializes the necessary data of the main structure
void	init_data(t_data **data, char **env)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		print_error_exit(MALLOC_ERROR, NULL);
	(*data)->env = env;
	(*data)->last_exit_status = 0;
	(*data)->tokens = NULL;
	(*data)->split_info = NULL;
	(*data)->section_id = 0;
	(*data)->sections = NULL;
	(*data)->prompt_init = NULL;
	(*data)->prompt = NULL;
}

//Function that checks if there is any export or unset command at the prompt
int	is_unset_or_export(t_data *data)
{
	int		i;
	char	*current;

	i = 0;
	current = NULL;
	if (data->split_info->splitted_prompt)
		current = data->split_info->splitted_prompt[i];
	while (current)
	{
		if (ft_strncmp("export", current, 7) == 0)
			return (1);
		if (ft_strncmp("unset", current, 6) == 0)
			return (1);
		current = data->split_info->splitted_prompt[++i];
	}
	return (0);
}

//Function that manages the reading of the prompt entered by the user
void	read_prompt(t_data *data)
{
	char	*aux;

	aux = data->prompt;
	data->prompt_init = ft_strtrim(data->prompt, " ");
	free(aux);
	data->prompt = data->prompt_init;
	if (check_syntax(data))
		return ;
	ft_token_split("<>|& ()\"\';\\", data);
	//TODO expand only if not export || unset
	/*if (!is_unset_or_export(data))
	{
		if (expand_var(data))
			return ;
	}*/
	if (tokenizer(data))
		return ;
	sectionizer(data);
	//TODO TEST PRINT
	print_sections(data->sections);
}

//Main function
int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argv;
	if (argc != 1)
		print_error_exit(NO_ARGS_REQUIRED, NULL);
	data = NULL;
	init_data(&data, env);
	while (1)
	{
		data->prompt = readline("minishell: ");
		if (data->prompt && data->prompt[0])
		{
			add_history(data->prompt);
			read_prompt(data);
			//TODO EXECUTE
			clean_prompt_data(data);
		}
		else if (!data->prompt)
			break ;
		else
			free(data->prompt);
	}
	free_data(data);
	exit(0);
}
