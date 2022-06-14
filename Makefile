# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 15:50:12 by yehan             #+#    #+#              #
#    Updated: 2022/06/14 08:14:57 by yehan            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

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
				setmap.c \
				setimg.c \
				keypress.c

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