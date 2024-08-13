/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:30:27 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/13 15:08:55 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Function that initializes the necessary data of the main structure
void	init_data(t_data *data, char **env)
{
	data->env = env;
	data->last_exit_status = 0;
	data->tokens = NULL;
	data->split_info = NULL;
}

//Function that manages the reading of the prompt entered by the user
void	read_prompt(t_data *data)
{
	char	*aux;

	aux = data->prompt;
	data->prompt = ft_strtrim(data->prompt, " ");
	free(aux);
	data->prompt_init = data->prompt;
	if (check_syntax(data))
		return ;
	ft_token_split("<>|& ()\"\'", data);
	//TODO expand only if not export
	//if (expand_var(data))
		//return ;
	if (tokenizer(data))
		return ;
}

void clean_prompt_data(t_data *data)
{
	free(data->prompt_init);
	data->prompt_init = NULL;
	free_split(&(data->split_info->splitted_prompt));
	ft_token_lstclear(&data->tokens);
}

//Main function
int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	(void)argv;
	if (argc != 1)
		print_error_exit(NO_ARGS_REQUIRED, NULL);
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		print_error_exit(MALLOC_ERROR, NULL);
	init_data(data, env);
	while (1)
	{
		data->prompt = readline("minishell: ");
		if (data->prompt && data->prompt[0])
			add_history(data->prompt);
		read_prompt(data);
		clean_prompt_data(data);
		/*free(data->prompt_init);
		data->prompt_init = NULL;
		free_split(&(data->split_info->splitted_prompt));
		ft_token_lstclear(&data->tokens);
		free_data(data);
		exit(0);*/
	}
}
