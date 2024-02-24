/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:32:43 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/22 18:54:45 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Returns the last element of a list
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
	{
		lst = lst -> next;
	}
	return (lst);
}

//Create a new element
t_list	*ft_lstnew(int value)
{
	t_list			*new;

	new = (t_list *) malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new -> value = value;
	new -> next = NULL;
	return (new);
}

//Frees and assigns NULL to all items in a list
void	ft_lstclear(t_list **lst)
{
	if (!(*lst) || !lst)
		return ;
	ft_lstclear(&(*lst)->next);
	free(*lst);
	*lst = NULL;
}
