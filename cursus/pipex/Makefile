# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 21:07:38 by igarcia2          #+#    #+#              #
#    Updated: 2024/02/24 15:00:00 by igarcia2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex 

MAIN = main.c

SRC = 

LIBFT = libft.a

DEPS = $(SRC:.c=.d) $(MAIN:.c=.d)

MAIN_OBJ = $(MAIN:.c=.o)
OBJ = $(SRC:.c=.o)


CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all:	$(NAME)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c -MMD $<

$(NAME): $(LIBFT) $(OBJ) $(MAIN_OBJ)
	$(CC) -o $(NAME) $(OBJ) $(MAIN_OBJ) libft/libft.a

$(LIBFT):
	make -C libft/
   
clean:	
	$(RM) $(OBJ) $(MAIN_OBJ) $(DEPS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re