# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thde-sou <thde-sou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/23 17:27:45 by thde-sou          #+#    #+#              #
#    Updated: 2025/10/09 02:31:53 by thde-sou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Werror -Wextra
FLAG_THREAD = -g -O0 -pthread

NAME = philo_bonus

SRC = main.c src/inits.c src/utils_1.c src/utils_2.c src/routine.c src/exit.c \
src/monitor.c src/build_name.c src/local_semaphore.c src/close_sem.c \
src/set_local_semaphore.c src/set_global_semaphore.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

race: $(OBJ)
	$(CC) $(FLAG_THREAD) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re