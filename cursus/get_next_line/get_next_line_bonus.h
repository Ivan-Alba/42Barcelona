/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:39:15 by igarcia2          #+#    #+#             */
/*   Updated: 2024/02/07 17:39:19 by igarcia2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_list
{
	char	*line;
	int		fd;
}	t_list;

int		is_next_line(char *str);
char	*get_next_line(int fd);
char	*free_and_out(char **str);
int		check_stack(char **saved, int i, char **res);
char	*cut_after_next_line(char **str);

#endif
