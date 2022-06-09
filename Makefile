NAME		:= so_long

FTDIR		:= ./libft
MLXDIR		:= ./libmlx

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g
LIBFLAGS	:= -L $(FTDIR) -lft -L $(MLXDIR) -lmlx
FRAMEFLAGS	:= -framework OpenGL -framework Appkit
RM			:= rm -f

SRCS	:= \
				main.c \
				img.c \
				map.c \
				changes.c

OBJS		= $(SRCS:.c=.o)

.PHONY:		all clean fclean re

all:		$(NAME)

clean:
			make clean --directory=$(FTDIR)
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
			make fclean --directory=$(FTDIR)
			$(RM) $(NAME)

re:			fclean all

$(NAME):	$(OBJS)
			make --directory=$(FTDIR)
			$(CC) $(CFLAGS) $^ $(LIBFLAGS) $(FRAMEFLAGS) -o $@
