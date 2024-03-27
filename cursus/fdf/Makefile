# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 21:07:38 by igarcia2          #+#    #+#              #
#    Updated: 2024/03/23 02:25:34 by igarcia2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = main.c utils.c read_map.c event_controller.c print_pixels.c map_info.c

DEPS = $(SRC:.c=.d)

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

MAKE_LIBFT = libft/Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all:	$(NAME)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -MMD -Imlx -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(LIBFT): libft/libft.h $(MAKE_LIBFT)
	make -C libft

clean:	libft_clean
	$(RM) $(OBJ) $(DEPS)

libft_clean:
	make -C libft clean

fclean: clean libft_fclean
	$(RM) $(NAME)

libft_fclean:
	make -C libft fclean

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
