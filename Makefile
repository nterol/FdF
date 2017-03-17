# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nterol <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/18 15:10:26 by nterol            #+#    #+#              #
#    Updated: 2017/03/08 05:44:08 by nterol           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CFLAGS = -Wall -Werror -Wextra

SRC = main.c map_it.c key_function.c fdf_trivia.c

OBJ = main.o map_it.o key_function.o fdf_trivia.o

LIB = ./libft/libft.a

FRAM = -framework OpenGL -framework Appkit

all : $(NAME)

$(NAME) : $(OBJ)
	#make -C ./libft
	#make -C ./minilibx_macos/
	gcc -c $(SRC) $(FLAGS)
	gcc -o $(NAME) $(OBJ) $(LIB) -I minilibx_macos ./minilibx_macos/libmlx.a $(FRAM)

clean :
	rm -rf $(OBJ)
	#make -C ./minilibx_macos/ clean
fclean : clean
	rm -rf $(NAME)
	#make -C ./minilibx_macos fclean

re : fclean all
