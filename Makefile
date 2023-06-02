# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amenesca <amenesca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 14:08:11 by amenesca          #+#    #+#              #
#    Updated: 2023/05/24 18:30:14 by amenesca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= cub3d

LIBFT		= ./libft/libft.a

SRCS		= ./sources/main.c ./sources/treat_initial_errors/treat_args_errors.c ./sources/utils/utils.c ./sources/utils/utils2.c  tests_purpose_functions.c\
 ./sources/read_get_validate/get_colors_textures.c ./sources/read_get_validate/read_map.c ./sources/read_get_validate/validate_colors_textures.c\
 ./sources/read_get_validate/split_colors.c ./sources/read_get_validate/split_textures.c ./sources/read_get_validate/validate_map.c\
 ./sources/read_get_validate/test_colors.c ./sources/read_get_validate/get_map.c ./sources/read_get_validate/get_n_validate.c

OBJS		= $(SRCS:.c=.o)

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

UNAME		= $(shell uname)

ifeq ($(UNAME), Linux)
	OFLAGS		= $(CFLAGS) -L ./mlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
	MLX			= ./mlx_linux
else
	OFLAGS		= $(CFLAGS) -L ./mlx -l mlx -framework OpenGl -framework Appkit
	MLX			= ./mlx
endif

.c.o:
			@cc $(CFLAGS) -c $< -o $(<:.c=.o) -I ./includes

$(NAME):	$(OBJS)
				@make -C ./libft
				@make -C $(MLX) &> /dev/null
				cc $(OBJS) $(OFLAGS) $(LIBFT) -o $(NAME)

all:		$(NAME)

clean:
			@$(RM) $(OBJS)
				@make clean -C ./libft
				@make clean -C $(MLX)

fclean:		clean
				@$(RM) $(NAME)
				@make fclean -C ./libft

re:			fclean all

.PHONY:		all clean fclean re