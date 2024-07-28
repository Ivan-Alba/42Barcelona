# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 21:07:38 by igarcia2          #+#    #+#              #
#    Updated: 2024/07/28 16:47:29 by igarcia2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell 

SRC = utils.c main.c ft_token_split.c check_quotes.c

SRC_DIR = src/

SRC_FULL_DIR =  $(addprefix $(SRC_DIR), $(SRC))

LIBFT = libft.a

LIBFT_DIR = src/libft/

OBJ = $(SRC:.c=.o)

OBJ_DIR = bin/

OBJ_FULL_DIR = $(addprefix $(OBJ_DIR), $(OBJ))

DEPS = $(SRC:.c=.d)

CC = gcc
CFLAGS = -Wall -Wextra -Werror $(READLINE_INCLUDE)
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


CURRENT_OS = $(shell uname -s)
ifeq ($(CURRENT_OS), Linux)
READLINE_DIR = $(HOME)/local
READLINE_INCLUDE = -I$(READLINE_DIR)/include
READLINE_LIB = -L$(READLINE_DIR)/lib -lreadline -lncurses

else
READLINE_INCLUDE =
READLINE_LIB =
endif


all: $(NAME)	

bonus:	$(NAME)

check_readline:
	@test -f $(READLINE_DIR)/include/readline/readline.h || { \
		curl -O https://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz; \
		tar -xzvf readline-8.1.tar.gz; \
		cd readline-8.1 && ./configure --prefix=$(READLINE_DIR) && make && make install && cd ..; \
		pwd && rm -rf readline-8.1.tar.gz && rm -rf readline-8.1;}	

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile
	@$(call SHOW_MESSAGE, $(INFO), " Compiling $<...")
	@$(CC) $(CFLAGS) -c -MMD $< -o $@ 
	@$(call SHOW_MESSAGE, $(CHECKMARK), " Compiled $<")

$(NAME): check_readline $(LIBFT) $(OBJ_DIR) $(OBJ_FULL_DIR)
	@echo "$(YELLOW)LINKING $(NAME)...$(RESET)"
	$(CC) -o $(NAME) $(OBJ_FULL_DIR) $(LIBFT_DIR)/$(LIBFT) $(READLINE_LIB) -fsanitize=address 

$(OBJ_DIR): 
	@mkdir $(OBJ_DIR)

$(LIBFT):
	@echo "$(YELLOW)COMPILING LIBFT...$(RESET)"
	@make -C $(LIBFT_DIR) --no-print-directory
	@echo "$(YELLOW)DONE$(CHECKMARK)$(RESET)"
	@echo "\n"
   
clean:	libft_clean
	@echo "$(WARNING) Cleaning..."
	@$(RM) $(OBJ_DIR)
	@echo "Done $(CHECKMARK)"
	
libft_clean:
	@make clean -C $(LIBFT_DIR) --no-print-directory

fclean: clean libft_fclean
	@echo "$(WARNING) Fcleaning..."
	@$(RM) $(NAME)
	@echo "Done $(CHECKMARK)"

libft_fclean:
	@make fclean -C $(LIBFT_DIR) --no-print-directory

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
