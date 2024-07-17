# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 21:07:38 by igarcia2          #+#    #+#              #
#    Updated: 2024/07/17 15:30:14 by igarcia2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = src/main.c src/utils.c src/read_map.c src/event_controller.c \
	  src/print_pixels.c src/map_info.c src/menu.c

DEPS = $(SRC:.c=.d)

OBJ = $(SRC:.c=.o)

LIBFT = src/libft/libft.a

MAKE_LIBFT = src/libft/Makefile

CC = gcc
CFLAGS = -Wextra -Werror -Wall 
RM = rm -f

all:	$(NAME)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -MMD -Imlx -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(LIBFT): src/libft/libft.h $(MAKE_LIBFT)
	make -C src/libft

clean:	libft_clean
	$(RM) $(OBJ) $(DEPS)

libft_clean:
	make -C src/libft clean

fclean: clean libft_fclean
	$(RM) $(NAME)

libft_fclean:
	make -C src/libft fclean

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
