/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:00:14 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/29 15:41:25 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Checks the type of token to be created and calls the corresponding function
void	create_token(t_data *data, int *i)
{
	char	*current;

	current = data->split_info->splitted_prompt[*i];
	if (current[0] == '<' || current[0] == '>')
		token_great_less(data, i);
	else if (current[0] == '|')
		token_pipe_or(data, i);
	else if (current[0] == '&')
		token_amper_and(data, i);
	else if (current[0] == '(' || current[0] == ')')
		token_brackets(data, i);
	else if (current[0] == '\'' || current[0] == '"')
		token_quotes(data, i);
	else if (current[0] == ' ')
		add_new_token(data, ft_strdup(current), SPC);
	else if (current[0] == '\\' || current[0] == ';')
		add_new_token(data, ft_strdup(current), FORB);
	else
		add_new_token(data, ft_strdup(current), WORD);
}

//Merges WORD type tokens that do not contain SPC type tokens between them
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

//Removes SPC tokens from the token list
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

//Manages token list format checking
int	check_tokens_format(t_token *current, t_data *data, int checking, int hrdcs)
{
	while (current && current->next)
	{
		if (current->type == AND || current->type == OR
			|| current->type == AMPER || current->type == FORB)
			checking = check_and_or(current);
		else if (current->type == OPEN_BRACKET)
			checking = check_open_bracket(current);
		else if (current->type == CLOSE_BRACKET)
			checking = check_close_bracket(current);
		else if (current->type == PIPE)
			checking = check_pipe(current);
		else if (current->type == WORD && current->next->type == OPEN_BRACKET)
			return (print_error(UNEXPECTED_TOKEN, current->next->str), 1);
		else if (current->type != WORD && current->next->type != WORD)
			return (print_error(UNEXPECTED_TOKEN, current->next->str), 1);
		if (checking)
			return (1);
		if (current->type == HEREDOC && ++hrdcs > 16)
			print_error_exit(MAX_HEREDOCS_ERROR, data);
		current = current->next;
	}
	if (check_first_last_token(current, 0))
		return (1);
	return (0);
}

//Manages the creation of the token list and the checking of its format
int	tokenizer(t_data *data)
{
	int		i;

	i = -1;
	data->tokens = NULL;
	while (data->split_info->splitted_prompt[++i])
		create_token(data, &i);
	merge_tokens(data);
	delete_space_tokens(data);
	if (check_first_last_token(data->tokens, 1))
		return (1);
	if (check_tokens_format(data->tokens, data, 0, 0))
	{
		data->last_exit_status = 2;
		return (1);
	}
	return (0);
}
