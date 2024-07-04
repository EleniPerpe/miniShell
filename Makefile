# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/26 14:16:08 by eperperi          #+#    #+#              #
#    Updated: 2024/07/04 17:46:56 by eperperi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME	=	minishell

CC			=	gcc -g #-fsanitize=address
# LEAKS = -L../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next -I ../LeakSanitize
CFLAGS		=	-Wall -Wextra -Werror -I$(HOME)/local/include
LDFLAGS = -L $(HOME)/local/lib -lreadline -lhistory

GREEN	=	\033[0;32m
CYAN	=	\033[0;36m
WHITE	=	\033[0m

SRC_DIR	=	./srcs/
OBJ_DIR	=	./objs/
GNL_DIR =	./Get_next_line/

SRC		 =	$(SRC_DIR)main.c $(SRC_DIR)init.c $(SRC_DIR)pipe.c $(SRC_DIR)quotes.c $(SRC_DIR)init_redirector.c \
			$(SRC_DIR)path.c $(SRC_DIR)standard_IO.c $(SRC_DIR)exec.c 
GNL_SRC  =	$(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c

OBJ		 =	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
GNL_OBJ	 =	$(GNL_SRC:$(GNL_DIR)%.c=$(OBJ_DIR)%.o)
LIB		 =	Libft/libft.a

$(NAME): $(OBJ) $(GNL_OBJ) $(LIB)
		@$(MAKE) -C Libft
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) $(GNL_OBJ) $(LDFLAGS) -l readline

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(GNL_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	@$(MAKE) -C Libft


all:	$(NAME)

clean:
		@$(MAKE) -C Libft clean
		@rm -rf $(OBJ_DIR)
		@echo "$(CYAN)Object files cleaned!$(WHITE)"

fclean:	clean
		@$(MAKE) -C Libft fclean
		@rm -f $(NAME)
		@echo "$(CYAN)Executable and object files cleaned!$(WHITE)"


re:		fclean all

.PHONY: all clean fclean re
