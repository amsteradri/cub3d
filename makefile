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
SRCS		=	cub3d.c parsing_errors.c parsing.c cub_window.c ray_casting.c movements.c

LIBFT		=	libft/libft.a

CFLAGS		=	#-Wall -Werror -Wextra #-fsanitize=address
MLXFLAGS	=	-L ./mlx/ -lmlx -framework OpenGL -framework AppKit -lz
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