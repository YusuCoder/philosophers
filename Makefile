# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 18:08:30 by ryusupov          #+#    #+#              #
#    Updated: 2024/06/28 16:40:10 by ryusupov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -g -pthread
RM			:= rm -rf
#####################################################
#						PATHS						#
#####################################################
OBJ_PATH	:= ./objs
SRCS_PATH	:= ./philo_srcs
MAIN		:= main.c
PHILO_SRCS	:= philo_srcs/init_philo.c \
			   philo_srcs/input_check.c \
			   philo_srcs/helper_functions.c \
			   philo_srcs/actions.c \
			   philo_srcs/philo_thread.c \
			   philo_srcs/input_check_utils.c \
			   philo_srcs/action_utils.c \
			   philo_srcs/philo_th_utils.c
#####################################################
#					OBJECT FILES					#
#####################################################
PHILO_OBJS	:= $(patsubst %, $(OBJ_PATH)/%, $(PHILO_SRCS:.c=.o))
MAIN_OBJ	:= $(OBJ_PATH)/main.o
#####################################################
#					COPILATIONS						#
#####################################################
all: git_sub_update $(NAME)

git_sub_update:
	@git submodule update --init --recursive

$(NAME): $(MAIN_OBJ) $(PHILO_OBJS)
	@$(CC) $(CFLAGS) $^ -o $@
#	$(ANIMATE_WELCOME)

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
#####################################################
#					Animation						#
#####################################################
 define ANIMATE_WELCOME
     @printf "\n\033[1;32mProcessing"
     @sleep 0.1
     @for i in {1..10}; do \
         printf "."; \
         sleep 0.2; \
     done
     @printf "\033[0m\n\n\n"
     @sleep 0.5
     @for frame in $(FRAMES); do \
         printf "\033[1;35m%s\n\033[0m" "$$frame"; \
		sleep 0.1; \
     done
     @echo
 endef

 define ANIMATE_PROCESSING
     @printf "\n\033[1;31mCleaning"
     @sleep 0.5
     @for i in {1..10}; do \
         printf "."; \
         sleep 0.1; \
     done
     @printf "\033[0m\n\n"
 endef
#####################################################
#						FRAMES						#
#####################################################
FRAMES := 	"██████╗s██╗ss██╗██╗██╗ssssss██████╗s███████╗s██████╗s██████╗s██╗ss██╗███████╗██████╗s███████╗ssss" \
			"██╔══██╗██║ss██║██║██║sssss██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║ss██║██╔════╝██╔══██╗██╔════╝ssss" \
			"██████╔╝███████║██║██║sssss██║sss██║███████╗██║sss██║██████╔╝███████║█████╗ss██████╔╝███████╗ssss" \
			"██╔═══╝s██╔══██║██║██║sssss██║sss██║╚════██║██║sss██║██╔═══╝s██╔══██║██╔══╝ss██╔══██╗╚════██║ssss" \
			"██║sssss██║ss██║██║███████╗╚██████╔╝███████║╚██████╔╝██║sssss██║ss██║███████╗██║ss██║███████║ssss" \
			"╚═╝sssss╚═╝ss╚═╝╚═╝╚══════╝s╚═════╝s╚══════╝s╚═════╝s╚═╝sssss╚═╝ss╚═╝╚══════╝╚═╝ss╚═╝╚══════╝ssss" \
			"sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss"

