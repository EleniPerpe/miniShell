# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/26 14:16:08 by eperperi          #+#    #+#              #
#    Updated: 2024/08/05 16:13:05 by eperperi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = minishell

CC = gcc  -g -fsanitize=address
# LEAKS = -L../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next -I ../LeakSanitize
CFLAGS = -Wall -Wextra -Werror -I$(HOME)/local/include
LDFLAGS = -L $(HOME)/local/lib -lreadline -lhistory

GREEN = \033[0;32m
CYAN = \033[0;36m
WHITE = \033[0m

SRC_DIR = ./srcs/
OBJ_DIR = ./objs/
PARSING_DIR = ./srcs/parsing/
BUILTINS_DIR = ./srcs/builtins/
EXECUTION_DIR = ./srcs/execution/
SIGNALS_DIR = ./srcs/signals/

SRC = $(SRC_DIR)main.c \
      $(SRC_DIR)main_utilities.c \
      $(EXECUTION_DIR)standard_io.c \
      $(EXECUTION_DIR)exec.c \
      $(EXECUTION_DIR)process_manager.c \
      $(PARSING_DIR)heredoc_handle.c \
      $(PARSING_DIR)init.c \
      $(PARSING_DIR)quotes.c \
      $(PARSING_DIR)init_redirector.c \
      $(PARSING_DIR)path.c \
      $(PARSING_DIR)expander.c \
      $(PARSING_DIR)utils_parsing.c \
      $(BUILTINS_DIR)echo.c \
      $(BUILTINS_DIR)builtins.c \
      $(BUILTINS_DIR)builtins_checker.c \
      $(BUILTINS_DIR)pwd.c \
      $(BUILTINS_DIR)env.c \
      $(BUILTINS_DIR)export.c \
      $(BUILTINS_DIR)export_remove.c \
      $(BUILTINS_DIR)unset.c \
      $(BUILTINS_DIR)exit.c \
      $(BUILTINS_DIR)cd.c \
      $(BUILTINS_DIR)cd_old.c \
      $(BUILTINS_DIR)cd_back.c \
      $(BUILTINS_DIR)export_append.c \
      $(EXECUTION_DIR)pipes_fork_utilities.c \
      $(EXECUTION_DIR)errors_free.c \
      $(EXECUTION_DIR)build_nodes.c \
      $(SIGNALS_DIR)signals.c \
      $(SIGNALS_DIR)status.c \

OBJ = $(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))
LIB = Libft/libft.a

# Rule to create the executable
$(NAME): $(OBJ) $(LIB)
	@$(MAKE) -C Libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) $(LDFLAGS) -l readline
	@echo "$(GREEN)$(NAME) built successfully!$(WHITE)"

# Rule to create object files from source files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(PARSING_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(BUILTINS_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(EXECUTION_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(SIGNALS_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Rule to build the libft library
$(LIB):
	@$(MAKE) -C Libft

# Default target to build everything
all: $(NAME)

# Clean object files and the libft library
clean:
	@$(MAKE) -C Libft clean
	@rm -rf $(OBJ_DIR)
	@echo "$(CYAN)Object files cleaned!$(WHITE)"

# Full clean, including the executable
fclean: clean
	@$(MAKE) -C Libft fclean
	@rm -f $(NAME)
	@echo "$(CYAN)Executable and object files cleaned!$(WHITE)"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
