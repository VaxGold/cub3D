SRCS    = test.c

OBJS    = ${SRCS:.c=.o}

NAME    = cub3D.a

CC      = gcc

RM      = rm -f

CFLAGS  = -Wall -Werror -Wextra

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
$(NAME):    ${OBJS}

all:       ${NAME}

clean:
		${RM} ${OBJS} ${OBJS_BONUS}

fclean:     clean
		${RM} ${NAME}

re:         fclean bonus

.PHONY:	clean all fclean re