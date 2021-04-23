NAME		=	cub3D
CFLAGS		=	-Wall -Werror -Wextra -g -I. -o $(NAME)
LIBFT		=	srcs/libs/libft/
GNL			=	srcs/libs/gnl/get_next_line.c srcs/libs/gnl/get_next_line_utils.c 
SRCS		=	$(GNL) cub3D.c srcs/ft_error.c srcs/key_events.c srcs/ft_save_img.c\
				srcs/ft_extension.c srcs/ft_flgcmp.c srcs/alloc_utils.c srcs/ft_spaceskip.c srcs/ft_mtxcpy.c\
				srcs/ft_parse.c srcs/checkMap.c srcs/map_utils.c srcs/checkResolution.c srcs/checkTexture.c srcs/checkColor.c \
				srcs/ft_raycast.c srcs/raycast_utils.c \
				srcs/ft_sprites.c srcs/sprites_utils.c \
				srcs/ft_transform.c
OBJS		=	$(SRCS:.c=.o)
CC			=	gcc
MATH		=	-lm
FRAMEWORK 	= 	-lmlx -framework OpenGL -framework AppKit

%.o: %.c
	$(CC) -c $< -o $@

all: libft $(NAME)

$(NAME): $(OBJS)
	gcc $(OBJS) $(CFLAGS) $(FRAMEWORK) -L$(LIBFT) $(LIBFT)libft.a

libft:
	make bonus -C $(LIBFT)

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)
	rm -f libft.a

re: fclean all

.PHONY:	all libft clean clean_lib fclean re
