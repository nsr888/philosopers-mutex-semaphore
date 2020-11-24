# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksinistr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/05 12:31:46 by ksinistr          #+#    #+#              #
#    Updated: 2020/11/24 10:59:48 by ksinistr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
SRC = main.c \
	  ft_atoi.c \
	  ft_itoa.c \
	  ft_strjoin.c \
	  ft_calloc.c \
	  ft_usleep.c \
	  init_structures.c \
	  philo_work.c \
	  check_threads.c \
	  print_timestamp.c
OBJ = $(SRC:%.c=%.o)
GCC = gcc -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ) philo.h
	$(GCC) $(OBJ) -o $@
$(OBJ): %.o: %.c
	$(GCC) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re:	fclean all
.PHONY: clean fclean re
