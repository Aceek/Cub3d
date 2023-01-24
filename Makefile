NAME				=	cub3d

HEAD				= -I mlx_linux -I srcs/

SRCS				=	cub3d.c ft_parsing.c ft_utils.c ft_split.c

OBJ					=	${addprefix srcs/,${SRCS:.c=.o}}

CC					=	gcc

MLX_FLAGS			=	-lm -lmlx -lXext -lX11

CFLAGS				=	-Wall -Werror -Wextra -g #-fsanitize=address

LD_FLAGS			=	-L mlx_linux

${NAME}				:	${OBJ}
					make -C mlx_linux
					${CC} ${CFLAGS} ${LD_FLAGS} ${OBJ} -o ${NAME} ${MLX_FLAGS}

all					:	${NAME}

.c.o				:	${HEAD}
					${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

clean				:
					make clean -C mlx_linux
					@rm -rf ${OBJ}

fclean				:	clean
					@rm -rf ${NAME}

re					:	fclean all

.PHONY				:	all clean fclean re