NAME		=	cub3D
NAME_T		=	cubTestD
CFLAGS		=	-Wall -Werror -Wextra -g
GNL			=	srcs/gnl/get_next_line.c srcs/gnl/get_next_line_utils.c 
SRCS		=	$(GNL) cub3D.c ft_transform.c ft_raycaster.c ft_spritecaster.c ft_controls.c ft_reader.c ft_check_map.c ft_check_tex.c ft_check_res.c ft_check_color.c check_utils.c
SRCS_T		=	$(GNL) test.c ft_reader.c ft_check_map.c ft_check_tex.c ft_check_res.c ft_check_color.c check_utils.c
OBJS		=	$(SRCS:.c=.o)
OBJS_T		=	$(SRCS_T:.c=.o)
CC			=	gcc
MATH		=	-lm
FRAMEWORK 	= 	-L . -lmlx -lft -framework OpenGL -framework AppKit

$(NAME): $(OBJS)
	make -C srcs/mlx
	make bonus -C srcs/libft
	mv srcs/libft/libft.a .
	mv srcs/mlx/libmlx.a .
	gcc $(OBJS) $(CFLAGS) -Lminilibx -lmlx -framework OpenGL -framework AppKit -L./ -lft -o $(NAME) $(MATH)

$(NAME_T): $(OBJS_T)
	# make -C srcs/mlx
	make bonus -C srcs/libft
	mv srcs/libft/libft.a .
	# mv srcs/mlx/libmlx.a .
	${CC} $(OBJS_T) $(CFLAGS) $(FRAMEWORK) -o $(NAME_T) $(MATH)

all: $(NAME)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_T)
	make clean -C srcs/mlx
	make clean -C srcs/libft

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_T)
	make fclean -C srcs/libft
	rm -f libft.a

re: fclean all

re_file:	fclean file

test:
		gcc -g -L mlx -lmlx -framework OpenGL -framework AppKit cubTestD.c
		./a.out

file: $(NAME_T)
		
.PHONY:	all test clean fclean re