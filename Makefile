# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/26 14:16:08 by eperperi          #+#    #+#              #
#    Updated: 2024/07/08 17:43:15 by rshatra          ###   ########.fr        #
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

SRC		 =	$(SRC_DIR)main.c $(SRC_DIR)init.c $(SRC_DIR)pipe.c $(SRC_DIR)quotes.c $(SRC_DIR)init_redirector.c \
			$(SRC_DIR)path.c $(SRC_DIR)standard_IO.c $(SRC_DIR)exec.c $(SRC_DIR)process_manager.c
OBJ		 =	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
LIB		 =	Libft/libft.a

$(NAME): $(OBJ) $(LIB)
		@$(MAKE) -C Libft
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) $(LDFLAGS) -l readline

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
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
