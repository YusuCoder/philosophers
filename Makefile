# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 18:08:30 by ryusupov          #+#    #+#              #
#    Updated: 2024/06/19 14:27:39 by ryusupov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -g -fsanitize=thread
RM			:= rm -rf

OBJ_PATH	:= ./objs
SRCS_PATH	:= ./philo_srcs

MAIN		:= main.c
PHILO_SRCS	:= philo_srcs/init_philo.c \
			   philo_srcs/input_check.c \
			   philo_srcs/helper_functions.c \
			   philo_srcs/actions.c \
			   philo_srcs/philo_thread.c

PHILO_OBJS	:= $(patsubst %, $(OBJ_PATH)/%, $(PHILO_SRCS:.c=.o))
MAIN_OBJ	:= $(OBJ_PATH)/main.o

all: git_sub_update $(NAME)

git_sub_update:
	@git submodule update --init --recursive

$(NAME): $(MAIN_OBJ) $(PHILO_OBJS)
	@$(CC) $(CFLAGS) $^ -o $@

$(OBJ_PATH)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)/%.o: $(SRCS_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re git_sub_update
