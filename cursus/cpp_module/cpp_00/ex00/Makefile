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

NAME = megaphone

MAIN = megaphone.cpp

DEPS = $(MAIN:.cpp=.d)

MAIN_OBJ = $(MAIN:.cpp=.o)

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -f

all: $(NAME)

%.o: %.cpp Makefile
	$(CC) $(CFLAGS) -c -MMD $<

$(NAME): $(MAIN_OBJ)
	$(CC) -o $(NAME) $(MAIN_OBJ)

clean:
	$(RM) $(MAIN_OBJ) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re

