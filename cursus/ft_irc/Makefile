# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 21:07:38 by igarcia2          #+#    #+#              #
#    Updated: 2025/04/18 17:54:45 by igarcia2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

SRC = main.cpp Server.cpp Client.cpp Channel.cpp

SRC_DIR = src/

SRC_FULL_DIR =  $(addprefix $(SRC_DIR), $(SRC))

OBJ = $(SRC:.cpp=.o)

OBJ_DIR = bin/

OBJ_FULL_DIR = $(addprefix $(OBJ_DIR), $(OBJ))

DEPS = $(OBJ_FULL_DIR:.o=.d)

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g
RM = rm -rf

# Color codes
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
RESET   = \033[0m

CHECKMARK = ✅
ERROR     = ❌
WARNING   = ⚠️
INFO      = ℹ️

# Function to display messages with icons
define SHOW_MESSAGE
	@echo "$(1)$(2)$(RESET)"
endef


# Length of the progress bar
BAR_LENGTH = 50

# Function to display a progress bar
define SHOW_PROGRESS
	@printf "$(YELLOW)[[[[%${BAR_LENGTH}s] %3d%%\r" "$(1)" $(2)
endef


all: $(NAME)	

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp Makefile
	@$(call SHOW_MESSAGE, $(INFO), " Compiling $<...")
	@$(CC) $(CFLAGS) -c -MMD $< -o $@ 
	@$(call SHOW_MESSAGE, $(CHECKMARK), " Compiled $<")

$(NAME): $(OBJ_DIR) $(OBJ_FULL_DIR)
	@echo "$(YELLOW)LINKING $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FULL_DIR) 

$(OBJ_DIR): 
	@mkdir $(OBJ_DIR)
 
clean:
	@echo "$(WARNING) Cleaning..."
	@$(RM) $(OBJ_DIR)
	@echo "Done $(CHECKMARK)"
	
fclean: clean
	@echo "$(WARNING) Fcleaning..."
	@$(RM) $(NAME)
	@echo "Done $(CHECKMARK)"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
