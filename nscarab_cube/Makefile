NAME		= cub3D
#####################################sources#######################################
SRC			= $(GNL)\
			$(PARSER)\
			$(GAME)\
			$(SCREENSHOT)
#####################################parser#######################################
PARSER_PATH	= parser/
PARSER		= $(PARSER_PATH)cube_start.c\
			$(PARSER_PATH)cube_parser_utils.c\
			$(PARSER_PATH)validation_of_map.c\
			$(PARSER_PATH)exit_functions.c\
			$(PARSER_PATH)parse_premap.c\
			$(PARSER_PATH)parser_logic.c\
			$(PARSER_PATH)cube_parser.c
#####################################get_next_line#################################
GNL_PATH	= gnl/
GNL			= $(GNL_PATH)get_next_line.c\
			$(GNL_PATH)get_next_line_utils.c
#####################################game#######################################
GAME_PATH	= game/
GAME		= $(GAME_PATH)game_start.c\
			$(GAME_PATH)draw_utils.c\
			$(GAME_PATH)prep_graphics.c\
			$(GAME_PATH)key_processing.c\
			$(GAME_PATH)move_player.c\
			$(GAME_PATH)render_rays.c\
			$(GAME_PATH)render_sprites.c\
			$(GAME_PATH)handle_sprites.c\
			$(GAME_PATH)draw_texture.c\
			$(GAME_PATH)move_player_logic.c\
			$(GAME_PATH)prep_game.c
#####################################screenshot#######################################
SCREEN_PATH	= screenshot/
SCREENSHOT	= $(SCREEN_PATH)make_screenshot.c
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
SANITIZE	= -fsanitize=address
#####################################headers#######################################
INC			= includes/
HDR			= $(INC)cube.h\
			  $(INC)libft.h\
			  $(INC)get_next_line.h

.c.o: $(HDR)
	gcc $(CFLAGS) -I$(INC) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ) $(HDR)
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

norm: $(SRC)
	norminette $(SRC) $(HDR)

.PHONY: all clean fclean re
