# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samatsum <samatsum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/04 21:01:21 by samatsum          #+#    #+#              #
#    Updated: 2025/03/29 23:31:59 by samatsum         ###   ########.fr        #
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
		monitor_bonus \
		philo_main_bonus \
		processes_bonus \
    	routine_bonus \
    	utils_02_bonus \
		utils_bonus \

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

bonus: all

.PHONY: all clean fclean re bonus

# //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# 時   0          1          2          3          4          5          6          7          8          9         10          11          12//
# P1: [Eat==============0..2] [Sleep==========2..4]            [Eat============5..7] [Sleep==========7..9]            [Eat===========10..12]  //
# P3:              [Eat============1..3] [Sleep==========3..5]            [Eat============6..8] [Sleep=========8..10]            [Eat======== //
# P5:                         [Eat============2..4] [Sleep==========4..6]            [Eat============7..9] [Sleep=========9..11]              //
# ~~~~~|~~~~~~~~~~|~~~~~~~~~~|~~~~~~~~~~|~~~~~~~~~~|~~~~~~~~~~|~~~~~~~~~~|~~~~~~~~~~|~~~~~~~~~~|~~~~~~~~~~|~~~~~~~~~|~~~~~~~~~~~|~~~~~~~~~~~  //
# P2:                                    [Eat============3..5] [Sleep==========5..7]            [Eat===========8..10] [Sleep=========10..12]  //
# P4:                                               [Eat============4..6] [Sleep==========6..8]            [Eat===========9..11] [Sleep=====  //
# //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
