/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:00:14 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/02 17:37:12 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_tokens(t_data *data)
{
	t_token	*current_token;

	printf("PRINT TOKENS: \n");
	current_token = data->tokens;
	while (current_token)
	{
		printf("%s\n", current_token->str);
		current_token = current_token->next;
	}
	printf("TERMINAN TOKENS\n");
}

void	create_token(t_data *data, int *i)
{
	char	*current;

	current = data->split_info->splitted_prompt[*i];
	if (current[0] == '<' || current[0] == '>')
		token_great_less(data, i);
	else if (current[0] == '|' || current[0] == '&')
		token_pipe_or_and(data, i);
	else if (current[0] == '\'' || current[0] == '"')
		token_quotes(data, i);
	/*else if (current[0] == '$')
		token_env_variable(data, i);
	else if (current[0] == ' ')
		return ;
	else
		token_word(data, i);*/
}

int	tokenizer(t_data *data)
{
	int	i;

	i = 0;
	data->tokens = NULL;
	while (data->split_info->splitted_prompt[i])
	{
		create_token(data, &i);
		i++;
	}
	print_tokens(data);
	//TODO check tokens format
	return (0);
}
