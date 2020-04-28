# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashishae <ashishae@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/25 17:53:15 by ashishae          #+#    #+#              #
#    Updated: 2020/01/17 19:06:09 by ashishae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/bmp.c srcs/check_scene.c srcs/color2_utils.c srcs/ft_split.c\
srcs/inter.c srcs/main.c srcs/parser.c srcs/parser_utils.c srcs/ray.c\
srcs/sphere.c srcs/v3.c srcs/buffer.c srcs/color.c srcs/cylinder.c\
srcs/get_next_line.c srcs/intersect.c srcs/matrix.c srcs/parser_directives.c\
srcs/plane.c srcs/shading.c srcs/square.c srcs/v3_ops.c srcs/check_directives.c\
srcs/color2.c srcs/ft_atoi_len.c srcs/get_next_line_utils.c srcs/list.c\
srcs/minirt.c srcs/parser_objects.c srcs/quadratic.c srcs/specular.c\
srcs/triangle.c
OBJS = $(SRCS:.c=.o)
NAME = miniRT

CFLAGS = -Wall -Wextra -Werror

.PHONY: 	clean fclean all re bonus

all:		$(NAME)

.c.o:
			gcc $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			make -C ./MinilibX
			gcc -o $(NAME) $(OBJS) $(CFLAGS) -lmlx -L./MinilibX -framework OpenGL -framework AppKit

clean:
			rm -f $(OBJS)

fclean: 	clean
			rm -f $(NAME)

re:			fclean all
