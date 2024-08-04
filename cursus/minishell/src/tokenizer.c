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

	printf("--------PRINT TOKENS--------\n");
	current_token = data->tokens;
	while (current_token)
	{
		printf("%s\n", current_token->str);
		current_token = current_token->next;
	}
	printf("--------END TOKENS---------\n");
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
	else if (current[0] == '(' || current[0] == ')')
		token_brackets(data, i);
	else if (current[0] == ' ')
        ft_token_add_back(&(data->tokens), ft_token_new(ft_strdup(current), SPC));	
	else
		token_word(data, i);
}

void	merge_tokens(t_data *data)
{
	t_token	*current;
	t_token	*aux;
	char	*str1;

	current = data->tokens;
	while (current)
	{
		if (current->type == WORD && current->next && (current->next)->type == WORD)
		{
			aux = current->next->next;
			str1 = ft_strdup(current->str);
			free(current->str);
			current->str = ft_strcat(str1, current->next->str);
			free(current->next->str);
			free(current->next);
			free(str1);
			current->next = aux;
		}
		else
			current = current->next;
	}
}

/*void	check_tokens_format(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		
		current = current->next;
	}
}*/

void	delete_space_tokens(t_data *data)
{
	t_token	*current;
	t_token	*aux;

	current = data->tokens;
	while (current)
	{
		if (current->next && current->next->type == SPC)
		{
			aux = current->next->next;
			free(current->next->str);
			free(current->next);
			current->next = aux;
		}
		else
			current = current->next;
	}
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
	//Concatenar tokens tipo WORD
	merge_tokens(data);
	//TODO delete spaces
	delete_space_tokens(data);
	//TODO check tokens format
	//check_tokens_format(data);
	print_tokens(data);
	return (0);
}
