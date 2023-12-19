# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 18:15:03 by adgutier          #+#    #+#              #
#    Updated: 2023/10/07 18:15:03 by adgutier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d
CC			=	gcc
SRCS		=	src/cub3d.c src/parse/parsing_errors.c src/parse/parsing.c src/parse/parsemap.c\
				src/window/cub_window.c src/raycast/raycast.c src/movements/movements.c \
				src/render/render.c src/render/render2d.c src/render/render3d.c src/utils/utils.c \
				src/raycast/textures.c src/raycast/textures2.c

LIBFT		=	libft/libft.a

CFLAGS		=	-Wall -Werror -Wextra -O3 -I inc -fsanitize=address
MLXFLAGS	=	-L ./mlx/ -lmlx -framework OpenGL -framework AppKit -lz # -> MAC. -L/usr/X11/lib -lXext -lX11  ## a partir de -L es para mi propio
#MLXFLAGS	=	-L ./mlx/ -lmlx -lz -L/usr/X11/lib -lXext -lX11 -lm
RM			=	rm -f

all:		$(NAME)

OBJ_DIR		=	obj
OBJS		=	$(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(LIBFT):
			@make -C libft >/dev/null 2>&1
			@make clean -C libft >/dev/null 2>&1

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(OBJS) $(LIBFT) $(MLXFLAGS) $(CFLAGS) -o $(NAME) >/dev/null 2>&1

clean:
	@$(RM) $(OBJS) >/dev/null 2>&1
	@$(RM) -r $(OBJ_DIR) >/dev/null 2>&1

fclean: clean
	@$(RM) $(NAME) >/dev/null 2>&1
	@make fclean -C libft/ >/dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re