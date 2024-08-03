/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:30:27 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/03 16:29:18 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_data(t_data *data, char **env)
{
	data->env = env;
}

void	expand_env_var(t_data *data)
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
			//expand_var(data, i);
		}
		current = data->split_info->splitted_prompt[++i];
	}
}

void	read_prompt(t_data *data)
{
	data->prompt_init = data->prompt;
	if (check_syntax(data))
		return ;
	ft_token_split("<>|& ()\"\'", data);
	//TODO EXPAND $
	//expand_env_var(data);
	print_split(data->split_info->splitted_prompt);
	//TODO Transform splitted on tokens
	if (tokenizer(data))
		return ;
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
		ft_token_lstclear(&data->tokens);
		//free_data(data);
		//exit(0);
	}
}
