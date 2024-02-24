/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:22:51 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/24 14:09:48 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "get_next_line_bonus.h"

# define ERROR_MSG "Error\n"
# define PA "pa\n"
# define PB "pb\n"
# define SA "sa\n"
# define SB "sb\n"
# define SS "ss\n"
# define RA "ra\n"
# define RB "rb\n"
# define RRA "rra\n"
# define RRB "rrb\n"
# define RR "rr\n"
# define RRR "rrr\n"

typedef struct s_list
{
	int				value;
	int				index;
	int				moves;
	struct s_list	*next;
}	t_list;

int		*check_args(int argc, char *argv[], int *count);
t_list	**create_stack(int **array, int count);
void	sort_stack(t_list **stack_a, int count);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstnew(int value);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst);
void	swap_stack(t_list **stack, char *order);
void	push_stack(t_list **src, t_list **dst, char *order);
void	rotate_stack(t_list **stack, char *order);
void	reverse_rotate_stack(t_list **stack, char *order);
void	swap_both_stacks(t_list **stack_a, t_list **stack_b, char *order);
void	rotate_both_stacks(t_list **stack_a, t_list **stack_b, char *order);
void	rev_rotate_both_stacks(t_list **stack_a, t_list **stack_b, char *order);
void	free_and_exit(void *ptr);
void	free_stack(t_list **stack);
int		get_highest_index(t_list *stack);
void	move_stack(int index, t_list **stack, char stack_id);
int		search_closest_index(int index, t_list **stack, int count);
int		up_or_down(t_list *stack, int index);
void	preview_moves(t_list **stack_a, t_list **stack_b);
int		search_previous_position(int index, t_list *stack);
int		get_cheap_idx(t_list **stack_a);
void	*ft_calloc(size_t nelem, size_t elsize);
void	ft_bzero(void *s, size_t n);
void	protected_write(char *order, int size);
//Bonus
int		is_sorted(t_list **stack_a, int count);
int		ft_strcmp(char *next, char *order);
void	free_both_stacks(t_list **stack_a, t_list **stack_b);

#endif
