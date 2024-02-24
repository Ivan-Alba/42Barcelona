# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/13 17:28:56 by igarcia2          #+#    #+#              #
#    Updated: 2024/02/24 15:34:15 by igarcia2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = \
	   ft_atoi.c ft_itoa.c ft_putendl_fd.c ft_strlcat.c ft_substr.c \
	   ft_bzero.c ft_memchr.c ft_putnbr_fd.c ft_strlcpy.c ft_tolower.c \
	   ft_calloc.c ft_memcmp.c ft_putstr_fd.c ft_strlen.c ft_toupper.c \
	   ft_isalnum.c ft_memcpy.c ft_split.c ft_strmapi.c ft_isalpha.c \
	   ft_memmove.c ft_strchr.c ft_strncmp.c ft_isascii.c ft_memrchr.c \
	   ft_strdup.c ft_strnstr.c ft_isdigit.c ft_memset.c ft_striteri.c \
	   ft_strrchr.c ft_isprint.c ft_strjoin.c ft_strtrim.c ft_putchar_fd.c \
	   ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	   ft_lstadd_back.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstdelone.c

FT_PRINTF_SRC = ft_printf/ft_check_flags_bonus.c ft_printf/ft_int_flags_bonus.c \
				ft_printf/ft_utoa.c ft_printf/ft_free_bonus.c \
				ft_printf/ft_print_flags_bonus.c ft_printf/ft_utils.c \
				ft_printf/ft_hexa_flags_bonus.c ft_printf/ft_printf.c \
				ft_printf/ft_utils_bonus.c

GET_NEXT_LINE_SRC = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJECTS = $(SRC:.c=.o) $(FT_PRINTF_SRC:.c=.o) $(GET_NEXT_LINE_SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar rcs

%.o: %.c libft.h Makefile
	$(CC) $(CFLAGS) -c $<

all:	$(NAME)

$(NAME): $(OBJECTS) 
	$(AR) $(NAME) $(OBJECTS)

clean:	
	$(RM) $(OBJECTS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
