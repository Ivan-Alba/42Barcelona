# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/20 19:47:37 by igarcia2          #+#    #+#              #
#    Updated: 2024/02/11 12:46:29 by igarcia2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SOURCES = ft_printf.c ft_utoa.c ft_utils.c

BONUS = ft_check_flags_bonus.c ft_utils_bonus.c ft_print_flags_bonus.c ft_int_flags_bonus.c ft_hexa_flags_bonus.c ft_free_bonus.c


OBJECTS = $(SOURCES:.c=.o)
BONUSOBJ = $(BONUS:.c=.o)

LIBFT = libft.a
CC = gcc # -g
CFLAGS = -Wall -Wextra -Werror # -fsanitize=address
RM = rm -f
AR = ar rcs

all: $(NAME) bonus

$(NAME): $(LIBFT) $(OBJECTS)
	mv libft/libft.a $(NAME)
	$(AR) $(NAME) $(OBJECTS)

%.o: %.c ft_printf.h Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

libft.a:
	make -C libft

bonus: $(NAME) $(BONUSOBJ)
	$(AR) $(NAME) $(BONUSOBJ)

clean:
	$(RM) $(OBJECTS) libft/*.o $(BONUSOBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
