# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 21:07:38 by igarcia2          #+#    #+#              #
#    Updated: 2024/08/07 12:38:22 by igarcia2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo 

MAIN = main.c

SRC = check_args.c actions.c run.c monitor.c utils.c

DEPS = $(SRC:.c=.d) $(MAIN:.c=.d)

MAIN_OBJ = $(MAIN:.c=.o)
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c -MMD $<

all:	$(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ)
	$(CC) -o $(NAME) $(OBJ) $(MAIN_OBJ) -fsanitize=address
   
clean:
	$(RM) $(OBJ) $(MAIN_OBJ) $(DEPS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
