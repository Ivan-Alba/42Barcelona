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

NAME = push_swap
BONUS_NAME = checker

MAIN = main.c
BONUS_MAIN = main_bonus.c

SRC = check_args.c create_stack.c list_utils.c list_utils2.c stack_utils2.c utils.c \
		  sort_stack.c stack_operations.c stack_both_operations.c stack_utils.c
BONUS_SRC = $(SRC) get_next_line_bonus.c get_next_line_utils_bonus.c utils_bonus.c

DEPS = $(SRC:.c=.d) $(MAIN:.c=.d)
DEPS_BONUS = $(BONUS_SRC:.c=.d) $(BONUS_MAIN:.c=.d)

MAIN_OBJ = $(MAIN:.c=.o)
OBJ = $(SRC:.c=.o)

MAIN_BONUS_OBJ = $(BONUS_MAIN:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all:	$(NAME)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c -MMD $<	

$(NAME): $(OBJ) $(MAIN_OBJ)
	$(CC) -o $(NAME) $(OBJ) $(MAIN_OBJ)

bonus:	$(BONUS_NAME)
   
$(BONUS_NAME): $(BONUS_OBJ) $(MAIN_BONUS_OBJ)
	$(CC) -o $(BONUS_NAME) $(BONUS_OBJ) $(MAIN_BONUS_OBJ)

clean:	
	$(RM) $(OBJ) $(BONUS_OBJ) $(MAIN_OBJ) $(MAIN_BONUS_OBJ) $(DEPS) $(DEPS_BONUS)

fclean: clean
		$(RM) $(NAME) $(BONUS_NAME) 

re: fclean all

-include $(DEPS) $(DEPS_BONUS)

.PHONY: all clean fclean re
