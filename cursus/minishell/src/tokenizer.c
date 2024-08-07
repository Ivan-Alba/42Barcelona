/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:00:14 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/08 17:03:38 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		ft_token_add(&(data->tokens), ft_token_new(ft_strdup(current), SPC));
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
		if (current->type == WORD && current->next
			&& (current->next)->type == WORD)
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

int	check_tokens_format(t_data *data, int checking)
{
	t_token	*current;

	current = data->tokens;
	if (check_first_token(current))
		return (1);
	while (current && current->next)
	{
		if (current->type == AND || current->type == OR)
			checking = check_and_or(current);
		else if (current->type == OPEN_BRACKET)
			checking = check_open_bracket(current);
		else if (current->type == CLOSE_BRACKET)
			checking = check_close_bracket(current);
		else if (current->type == PIPE)
			checking = check_pipe(current);
		else if (current->type == WORD && current->next->type == OPEN_BRACKET)
			return (print_error(UNEXPECTED_TOKEN, current->next->str), 1);
		else if (current->next->type != WORD)
			return (print_error(UNEXPECTED_TOKEN, current->next->str), 1);
		if (checking)
			return (1);
		current = current->next;
	}
	return (0);
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
	merge_tokens(data);
	delete_space_tokens(data);
	print_tokens(data);
	if (check_tokens_format(data, 0))
		return (1);
	return (0);
}
