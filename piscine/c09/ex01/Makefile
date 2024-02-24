# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anovio-c <anovio-c@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/05 20:26:01 by anovio-c          #+#    #+#              #
#    Updated: 2023/11/09 19:31:44 by igarcia2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCDIR  = ./srcs/
HEAD	= ./includes/
SRCNAME = ft_putchar.c ft_swap.c ft_putstr.c ft_strlen.c ft_strcmp.c
SRCS    = ${addprefix ${SRCDIR}, ${SRCNAME}}
OBJS    = ${SRCS:.c=.o}
NAME    = libft.a
GCC		= gcc
AR		= ar rc
RM      = rm -f
LIB		= ranlib
CFLAGS  = -Wall -Wextra -Werror

.c.o:
			${GCC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o}

${NAME}:    ${OBJS}
			${AR} ${NAME} ${OBJS}
			${LIB} ${NAME}

all:        ${NAME}

clean:
			${RM} ${OBJS}

fclean:     clean
			${RM} ${NAME}

re:         fclean all

.PHONY:     clean fclean re all
