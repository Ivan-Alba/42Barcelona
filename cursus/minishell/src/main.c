/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:30:27 by igarcia2          #+#    #+#             */
/*   Updated: 2024/07/20 18:58:09 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_split(char **splitted)
{
	int	i;

	i = 0;
	if (splitted)
	{
		while (splitted[i])
		{
			ft_printf("%s\n", splitted[i]);
			i++;
		}
	}
}


/*void	create_tokens(char **splitted_prompt, t_data *data)
{
	int	i;

	i = 0;
	if (splitted)
	{
		while (splitted[i])
		{
			if (splitted[i][0] == '<' && ) 
		}
	}
}*/


void	read_prompt(char *prompt, t_data *data)
{
	(void)data;
	ft_token_split(prompt, "<>&| ", data);

	//create_tokens(splitted_prompt, data);

	print_split(data->splitted_prompt);
	//free_split(splitted_prompt);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*prompt;

	(void)argv;
	if (argc != 1)
		print_error_exit("Error: no args required", NULL);
	data = malloc(sizeof(t_data *));
	if (!data)
		print_error_exit("Error: allocating memory", NULL);
	data->env = env;
	while (1)
	{
		prompt = readline("minishell: ");
		read_prompt(prompt, data);
	}
}
