cmake_minimum_required(VERSION 3.17)
project(cube_repo C)

set(CMAKE_C_STANDARD 11)

add_executable(cube_repo
        cube_start.c
        cube_parser.c
        cube_parser_utils.c
        libft/ft_isdigit.c
        libft/ft_lstnew.c
        libft/ft_lstsize.c
        validation_of_map.c
        libft/ft_memcpy.c
        libft/ft_lstdelone.c
        libft/ft_putchar_fd.c
        libft/ft_putendl_fd.c
        libft/ft_strdup.c
        libft/ft_strlen.c
        libft/ft_lstclear.c
        libft/ft_lstadd_back.c
        gnl/get_next_line.c
        gnl/get_next_line.h
        gnl/get_next_line_utils.c
        map.cub)