NAME	=	cub3D
CFLAGS	=	-Wall -Werror -Wextra
GNL		=	srcs/gnl/get_next_line.c
SRCS	=	$(GNL) cub3D.c ft_transform.c ft_raycaster.c ft_controls.c
OBJS	=	$(SRCS:.c=.o)
CC		=	gcc
MATH	=	-lm

all: $(NAME)

$(NAME): $(OBJS)
	make -C srcs/mlx
	make -C srcs/libft
	cp srcs/libft/libft.a .
	gcc $(OBJS) $(CFLAGS) -Lminilibx -lmlx -framework OpenGL -framework AppKit -L./ -lft -o $(NAME) $(MATH)

all: $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C srcs/mlx
	make clean -C srcs/libft

fclean: clean
	rm -f $(NAME)
	make fclean -C srcs/libft
	rm -f libft.a

re: fclean all

test:
		gcc -g -L mlx -lmlx -framework OpenGL -framework AppKit cubTestD.c
		./a.out

.PHONY:	all test clean fclean re