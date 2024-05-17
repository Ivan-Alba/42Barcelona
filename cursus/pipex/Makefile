# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 21:07:38 by igarcia2          #+#    #+#              #
#    Updated: 2024/05/17 23:13:56 by igarcia2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex 

MAIN = main.c

SRC = init_data.c free_data.c execute.c

LIBFT = libft.a

DEPS = $(SRC:.c=.d) $(MAIN:.c=.d)

MAIN_OBJ = $(MAIN:.c=.o)
OBJ = $(SRC:.c=.o)


CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

%.o: %.c Makefile pipex.h
	$(CC) $(CFLAGS) -c -MMD $<

all:	$(NAME)

bonus:	$(NAME);

$(NAME): $(LIBFT) $(OBJ) $(MAIN_OBJ)
	$(CC) -o $(NAME) $(OBJ) $(MAIN_OBJ) libft/libft.a

$(LIBFT):
	make -C libft/
   
clean:	libft_clean
	$(RM) $(OBJ) $(MAIN_OBJ) $(DEPS)
	
libft_clean:
	make clean -C libft/

fclean: clean libft_fclean
		$(RM) $(NAME)

libft_fclean:
	make fclean -C libft/

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
