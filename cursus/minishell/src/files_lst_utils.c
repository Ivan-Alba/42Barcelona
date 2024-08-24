/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:41:11 by igarcia2          #+#    #+#             */
/*   Updated: 2024/08/22 20:21:03 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Receives the pointer to a list of t_files and frees all its contents
void	ft_files_lstclear(t_files **lst)
{
	if ((!lst) || !(*lst))
		return ;
	ft_files_lstclear((void *)&(*lst)->next);
	if ((*lst)->file_name)
		free((*lst)->file_name);
	(*lst)->file_name = NULL;
	if ((*lst)->hrdc_file_name)
		free((*lst)->hrdc_file_name);
	free(*lst);
	*lst = NULL;
}

//Recieve the pointer to a list of t_files and returns the last element
t_files	*ft_files_last(t_files *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

//Create a new node of type t_files and returns it
t_files	*ft_files_new(char *file_name, enum e_token_type type)
{
	t_files	*new;

	new = (t_files *) malloc(sizeof(t_files));
	if (!new)
		return (NULL);
	new->file_type = type;
	if (type == HEREDOC)
	{
		new->file_name = ft_strcat(file_name, "\n");
		free(file_name);
		file_name = NULL;
	}
	else
		new->file_name = file_name;
	new->fd = -1;
	new->hrdc_file_name = NULL;
	new->next = NULL;
	return (new);
}

//Add a new node at the end of a t_files list
void	ft_files_add(t_files **lst, t_files *new)
{
	t_files	*last;

	if (!lst)
		lst = &new;
	else
	{
		if (!*lst)
			*lst = new;
		else
		{
			last = ft_files_last(*lst);
			last->next = new;
		}
	}
}
