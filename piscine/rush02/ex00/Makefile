# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anovio-c <anovio-c@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/05 20:26:01 by anovio-c          #+#    #+#              #
#    Updated: 2023/11/05 21:52:59 by anovio-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCDIR  = ./srcs/
SRCNAME = main.c auxiliar.c auxiliar2.c number_format.c search_dict.c
SRCS    = ${addprefix ${SRCDIR}, ${SRCNAME}}
OBJS    = ${SRCS:.c=.o}
NAME    = rush-02
CC      = cc
RM      = rm -f
CFLAGS  = -Wall -Wextra -Werror
.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
${NAME}:    ${OBJS}
			${CC} -o ${NAME} ${OBJS}
all:        ${NAME}
clean:
			${RM} ${OBJS}
fclean:     clean
			${RM} ${NAME}
re:         fclean all
.PHONY:     clean fclean re all