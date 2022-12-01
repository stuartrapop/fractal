NAME = test

SRCS_PATH =./

OBJS_PATH = ./

SRCS_NAME = screen_helpers.c \
			fractal.c


SRCS = $(addprefix $(SRCS_PATH)/,$(SRCS_NAME))


HEADER_DIR = ./

FLAG = -Wall -Wextra -Werror -I$(HEADER_DIR)

CC = GCC $(FLAG)

OBJS = ${SRCS:.c=.o}

%.o:%.c
	$(CC) -o $@ -c $<

${NAME} : ${OBJS}
	# $(CC)   -L.  -g  -lmlx -lGLEW -lglfw -framework OpenGL -framework AppKit  $(OBJS) -o ${NAME}
	$(CC)   -L.  -g -lm -lmlx  -framework OpenGL -framework AppKit  $(OBJS) -o ${NAME}

all : ${NAME}

clean :
	rm -f ${OBJS} $(OBJS_BONUS)

fclean : clean
	rm -f ${NAME}

re : fclean all

	

.PHONY : all clean fclean re
