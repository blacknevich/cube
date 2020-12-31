NAME		= cub3D
#####################################sources#######################################
SRC			= $(GNL)\
			$(PARSER)\
			$(DRAW)
#####################################parser#######################################
PARSER_PATH	= parser/
PARSER		= $(PARSER_PATH)cube_start.c\
			$(PARSER_PATH)cube_parser_utils.c\
			$(PARSER_PATH)validation_of_map.c\
			$(PARSER_PATH)cube_parser.c
#####################################get_next_line#################################
GNL_PATH	= gnl/
GNL			= $(GNL_PATH)get_next_line.c\
			$(GNL_PATH)get_next_line_utils.c
#####################################draw#######################################
DRAW_PATH	= game/
DRAW		= $(DRAW_PATH)game_start.c\
			$(DRAW_PATH)draw_utils.c
#####################################objects#######################################
OBJ			= $(SRC:.c=.o)
#####################################libft#######################################
L_PATH		= libft/
L_NAME		= libft.a
#####################################mlx#######################################
MLX_PATH	= minilibx_opengl_20191021/
MLX_LIB		= libmlx.a
#####################################flags#######################################
MLX_FLAGS	= -framework OpenGL -framework AppKit
CFLAGS		= -Wall -Wextra -Werror
INC			= includes/

.c.o:
	gcc $(CFLAGS) -I$(INC) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ) 
	make -C $(L_PATH)
	make -C $(MLX_PATH)
	gcc $(CFLAGS) $(MLX_FLAGS) $(L_PATH)$(L_NAME) $(MLX_PATH)$(MLX_LIB) $(OBJ) -o $(NAME)

all:  $(NAME)

clean:
	make clean -C $(L_PATH)
	make clean -C $(MLX_PATH)
	rm -rf $(OBJ) 

fclean: clean
	rm -rf $(L_PATH)$(L_NAME)
	rm -rf $(NAME)
	rm -rf $(MLX_PATH)$(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re
