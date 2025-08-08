# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aimokhta <aimokhta@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 18:19:41 by aimokhta          #+#    #+#              #
#    Updated: 2025/08/08 10:02:19 by aimokhta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

#compilation flags
CFLAG = -Wall -Werror -Wextra -g -O0 -fsanitize=address #-fsanitize-recover=leak
# -g3 -O3 -O0 -fsanitize=address 
# valgrind --leak-check=full --show-leak-kinds=all
# valgrind --tool=helgrind
# -g = gives error messages for debugging, needed by gdb / valgrind / helgrind
# for philo, without optimization (-O0) for best result

#link option 
LFLAG = -pthread
# -pthread = enable to use multi-threading functions	

# directory that contains source files
SRC_DIR = src

SRC =	\
		$(SRC_DIR)/1_main.c \
		$(SRC_DIR)/2_parsing.c \
		$(SRC_DIR)/3_philo_routine.c \
		$(SRC_DIR)/4_philo_check.c \
		$(SRC_DIR)/5_monitor.c \
		$(SRC_DIR)/utils.c \
	
INC = -I include
# this is what is caused to not write explicit path for all #includes in all header and c files
# -I means it will search the header in that directory that is mentioned in the each file's #include

OBJ_FOLDER = obj_files

# patsubst : pattern substitution function
# create a list of .o files in the object folder
OBJ_SRC = $(patsubst %.c, $(OBJ_FOLDER)/%.o, $(SRC))

# color
GREEN = \033[0;32m
BLUE = \033[0;34m
RESET = \033[0m  	#white

all: $(NAME)

$(NAME) : $(OBJ_SRC)
	$(CC) $(CFLAG) $(INC) $(OBJ_SRC) $(LFLAG) -o $(NAME)
	@echo "${GREEN}----------COMPILED DONE----------\n${RESET}"

$(OBJ_FOLDER)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAG) $(INC) -c $< -o $@
# add $(INC) to not do explicit path to all #include of all header and c files

clean:
	@rm -rf $(OBJ_FOLDER)
	@echo "${GREEN}----------CLEANED----------\n${RESET}"

fclean : clean
	rm -f $(NAME)
	@echo "${GREEN}----------FULLY REMOVE----------\n${RESET}"

re : fclean all

.PHONY : all clean fclean re