# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igarcia2 <igarcia2@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 21:07:38 by igarcia2          #+#    #+#              #
#    Updated: 2024/09/03 16:50:18 by igarcia2         ###   ########.fr        #
#
# **************************************************************************** #

NAME = minishell

SRC_DIR = src/

# Subdirectories to include
SUBDIRS = main tokenizer sectionizer files execution expansion builtins \
						signals wildcard utils

# Find all .c files only in the specified subdirectories
SRC_FULL_DIR = $(foreach dir, $(SUBDIRS), $(wildcard $(SRC_DIR)$(dir)/*.c))

LIBFT = src/libft/libft.a
LIBFT_DIR = src/libft/

OBJ_DIR = bin/
OBJ = $(SRC_FULL_DIR:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

DEPS = $(OBJ:.o=.d)

CC = gcc
CFLAGS = -Wall -Wextra -Werror $(READLINE_INCLUDE)
RM = rm -rf

# Color codes
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
WHITE   = \033[0;37m
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

# Function to display header
define SHOW_HEADER
	@clear; \
	echo "==================================================================="; \
	echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "; \
	echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "; \
	echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "; \
	echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "; \
	echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"; \
	echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"; \
	echo "==================================================================="; \
	echo "                                  Created by:$(1)igarcia2$(RESET) &&$(1)ctacconi$(RESET)"; \
	echo ""; \

endef

# Modify the all target to include the header
all: 
	$(call SHOW_HEADER, $(BLUE))
	@make -C $(LIBFT_DIR) --no-print-directory
	@$(MAKE) $(NAME) --no-print-directory
	@echo "\n$(GREEN) $(CHECKMARK) -------- ALL DONE -------- $(CHECKMARK)$(RESET)\n"

bonus:
	$(call SHOW_HEADER, $(BLUE))
	@$(MAKE) $(NAME) --no-print-directory
	@echo "\n$(GREEN) $(CHECKMARK) -------- ALL DONE -------- $(CHECKMARK)$(RESET)\n"

READLINE_MARKER = $(READLINE_DIR)/.readline_installed

check_readline: $(READLINE_MARKER)

$(READLINE_MARKER):
	@test -f $(READLINE_DIR)/include/readline/readline.h || { \
		curl -O https://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz; \
		tar -xzvf readline-8.1.tar.gz; \
		cd readline-8.1 && ./configure --prefix=$(READLINE_DIR) && make && make install && cd ..; \
		pwd && rm -rf readline-8.1.tar.gz && rm -rf readline-8.1; }; \
	touch $(READLINE_MARKER)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile | create_obj_dirs
		@$(call SHOW_MESSAGE, $(INFO), " Compiling $<...")
		@$(CC) $(CFLAGS) -c -MMD $< -o $@
		@$(call SHOW_MESSAGE, $(CHECKMARK), " Compiled $<")

$(NAME): $(READLINE_MARKER) $(OBJ_DIR) $(OBJ)
		@echo ""
		@$(call SHOW_MESSAGE, $(YELLOW)$(INFO), " LINKING MINISHELL...")
		@$(CC) -o $(NAME) $(OBJ) $(LIBFT) $(READLINE_LIB) -fsanitize=address
		@$(call SHOW_MESSAGE, $(GREEN)$(CHECKMARK), " MINISHELL DONE!")

$(OBJ_DIR): Makefile $(LIBFT)
		@rm -rf $(OBJ_DIR)
		@echo "$(YELLOW)COMPILING MINISHELL FILES...$(RESET)"
		@mkdir $(OBJ_DIR)

# Create necessary directories for object files and dependencies
create_obj_dirs:
		@mkdir -p $(OBJ_DIR) $(foreach dir, $(SUBDIRS), $(OBJ_DIR)$(dir))

$(LIBFT): 
		@$(call SHOW_MESSAGE, $(YELLOW)$(INFO), " COMPILING LIBFT...")
		@make -C $(LIBFT_DIR) --no-print-directory
		@$(call SHOW_MESSAGE, $(GREEN)$(CHECKMARK), " LIBFT DONE!")
		@echo "\n"

clean: libft_clean
		$(call SHOW_HEADER, $(BLUE))
		@$(call SHOW_MESSAGE, $(YELLOW)$(INFO), " CLEANING...")
		@$(RM) $(OBJ_DIR)
		@$(call SHOW_MESSAGE, $(GREEN)$(CHECKMARK), "	DONE!")
		@echo "\n"

libft_clean:
		@make clean -C $(LIBFT_DIR) --no-print-directory

fclean: clean libft_fclean
		@$(call SHOW_MESSAGE, $(YELLOW)$(INFO), " FCLEANING...")
		@$(RM) $(NAME)
		@$(call SHOW_MESSAGE, $(GREEN)$(CHECKMARK), "	DONE!")
		@echo "\n"

libft_fclean:
		@make fclean -C $(LIBFT_DIR) --no-print-directory

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
