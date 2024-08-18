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
	if (!new)
		return (NULL);
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

//Manages the creation of a new t_token node and adds it to the list
void	add_new_token(t_data *data, char *str, enum e_token_type type)
{
	t_token	*new_token;

	new_token = ft_token_new(str, type);
	if (!new_token)
		print_error_exit(MALLOC_ERROR, data);
	ft_token_add(&(data->tokens), new_token);
}
