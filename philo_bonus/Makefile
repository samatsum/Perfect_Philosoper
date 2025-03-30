# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/04 21:01:21 by samatsum          #+#    #+#              #
#    Updated: 2025/03/30 17:03:01 by samatsum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
#-g #-fsanitize=thread
SRC_DIR = src/
OBJ_DIR = objects/

SRC =	check_input_bonus \
		ft_atoi_bonus \
		ft_eat_bonus \
		init_data_bonus \
		philo_main_bonus \
    	routine_bonus \
		processes_bonus \
    	utils_02_bonus \
		utils_bonus \
		monitor_bonus \

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean re
