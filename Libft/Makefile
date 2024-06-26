# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eperperi <eperperi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/14 15:40:36 by eperperi          #+#    #+#              #
#    Updated: 2024/03/20 10:19:44 by eperperi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_putstr_fd.c ft_split.c  ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
ft_tolower.c ft_toupper.c

SRCS_BONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c \
ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstmap_bonus.c ft_lstiter_bonus.c
  
OFILES = $(SRCS:.c=.o)

OFILES_BONUS = $(SRCS_BONUS:.c=.o)

NAME = libft.a

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

bonus: $(OFILES_BONUS)
	ar rcs $(NAME) $(OFILES_BONUS)

clean:
	$(RM) -f $(OFILES) $(OFILES_BONUS)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY:  all clean fclean re bonus