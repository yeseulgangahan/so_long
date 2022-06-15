# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 15:50:12 by yehan             #+#    #+#              #
#    Updated: 2022/06/16 08:15:50 by yehan            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME		:= so_long

FTDIR		:= ./libft
MLXDIR		:= ./libmlx

CFLAGS		:= -Wall -Wextra -Werror

FRAMEFLAGS	:= -framework OpenGL -framework Appkit
RM			:= rm -f

SRCS	:= \
				main.c \
				setmap.c \
				setimg.c \
				keypress.c

OBJS		= $(SRCS:.c=.o)
LIBS		= $(FTDIR)/libft.a $(MLXDIR)/libmlx.a

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
			$(CC) $(CFLAGS) $^ $(LIBS) $(FRAMEFLAGS) -o $@
