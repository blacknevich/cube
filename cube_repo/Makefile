#####################################Makefile#######################################
NAME		= cub3D
#####################################sources#######################################
SRC			= cube_start.c\
			  cube_parser_utils.c\
			  cube_parser.c\
			  validation_of_map.c\
			  $(GNL)
#####################################get_next_line#################################
GNL_PATH	= gnl/
GNL			= $(GNL_PATH)get_next_line.c\
			  $(GNL_PATH)get_next_line_utils.c
#####################################objects#######################################
OBJ			= $(SRC:.c=.o)
#####################################headers#######################################
HDR			= cube.h
#####################################libft#######################################
L_PATH		= libft/
L_NAME		= libft.a
#####################################flags#######################################
CFLAGS		= -Wall -Wextra -Werror

all:  $(NAME)

.c.o:
	gcc $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ) $(HDR)
	make bonus -C $(L_PATH)
	gcc $(CFLAGS) $(OBJ) $(L_PATH)$(L_NAME) -o $(NAME)

clean:
	make clean -C $(L_PATH)
	rm -rf $(OBJ) 

fclean: clean
	rm -rf $(L_PATH)$(L_NAME)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
