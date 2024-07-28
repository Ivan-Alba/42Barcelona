/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:30:27 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/28 18:23:08 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_data(t_data *data, char **env)
{
	data->env = env;
}

void	read_prompt(t_data *data)
{
	data->prompt_init = data->prompt;
	if (check_syntax(data))
		return ;
	ft_token_split("<>|& ()\"\'", data);
	print_split(data->split_info->splitted_prompt);
	//TODO Transform splitted on tokens
	
	free_split(&(data->split_info->splitted_prompt));
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argv;
	if (argc != 1)
		print_error_exit("Error: no args required", NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		print_error_exit("Error: allocating memory", NULL);
	init_data(data, env);
	while (1)
	{
		data->prompt = readline("minishell: ");
		read_prompt(data);
		free(data->prompt_init);
		data->prompt_init = NULL;
		//free_data(data);
		//exit(0);
	}
}
