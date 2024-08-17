/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:53:07 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/17 14:22:02 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Receives the pointer to a list of t_token and frees all its contents
void	ft_token_lstclear(t_token **lst)
{
	if ((!lst) || !(*lst))
		return ;
	ft_token_lstclear((void *)&(*lst)->next);
	if ((*lst)->str)
		free((*lst)->str);
	(*lst)->str = NULL;
	free(*lst);
	*lst = NULL;
}

//Recieve the pointer to a list of t_token and returns the last element
t_token	*ft_token_last(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

//Create a new node of type t_token and returns it
t_token	*ft_token_new(char *str, enum e_token_type type)
{
	t_token	*new;

	new = (t_token *) malloc(sizeof(t_token));
	//TODO REVISAR RETURN NULL FREE DATA
	if (!new)
		return (print_error_exit(MALLOC_ERROR, NULL), NULL);
	new->str = str;
	new->type = type;
	new->next = NULL;
	return (new);
}

//Add a new node at the end of a t_token list 
void	ft_token_add(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!lst)
		lst = &new;
	else
	{
		if (!*lst)
			*lst = new;
		else
		{
			last = ft_token_last(*lst);
			last->next = new;
		}
	}
}

//(TEST) Prints the contents of the token list received by parameter
void	print_tokens(t_data *data)
{
	t_token	*current_token;

	printf("--------PRINT TOKENS--------\n");
	current_token = data->tokens;
	while (current_token)
	{
		printf("%s - Type:%d\n", current_token->str, current_token->type);
		current_token = current_token->next;
	}
	printf("--------END TOKENS---------\n");
}
