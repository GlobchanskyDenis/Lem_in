# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/16 14:32:21 by bsabre-c          #+#    #+#              #
#    Updated: 2019/09/28 13:19:50 by bsabre-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEMIN_NAME	= lem-in
GRAF_NAME	= grafix.out
FLAGS		= -Wall -Wextra -Werror 

# directories
DIR		=	./

# files
SRC_LEMIN	= $(DIR)main.c					$(DIR)new_room.c		\
			  $(DIR)read_rooms.c			$(DIR)gnl.c				\
			  $(DIR)get_first_last_room.c	$(DIR)temp.c			\
			  $(DIR)free.c					$(DIR)make_linkage.c	\
			  $(DIR)array.c					$(DIR)dijkstra_1.c		\
			  $(DIR)queue.c					$(DIR)dijkstra_2.c		\
			  $(DIR)karpov-globchansky.c	$(DIR)karpov-globchansky_2.c
SRC_GRAFIX	= 
INC_LEMIN	= $(DIR)lem_in.h
INC_GRAFIX	= $(DIR)grafix.h
MLX			= mlx/libmlx.a -lmlx -framework OpenGL -framework AppKit

# libraries
L_FT 		= ./libft/
L_FT_A 		= $(L_FT)libft.a

$(LEMIN_NAME) :
			@make -sC $(L_FT)
			@echo "Combiling lem_in"
			@gcc $(FLAGS) $(SRC_LEMIN) -I$(INC_LEMIN) $(L_FT_A) -o $(LEMIN_NAME)
			@echo "file $(LEMIN_NAME) was created succesfully"

clean :
			@echo "start cleaning"
			@make clean -sC $(L_FT)
			@rm -rf .DS_Store
			@rm -rf $(L_FT).DS_Store
			@echo "cleaning finished"

fclean : clean
			@rm -f $(L_FT_A)
			@rm -f $(LEMIN_NAME)

lemin :
			@rm -r log.txt
			@touch log.txt
			@chmod 777 log.txt
			@./$(LEMIN_NAME) < maps/src4
			@rm -rf lem-in.dSYM

all : $(LEMIN_NAME)

re: fclean all
