# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmatsuka < rmatsuka@student.42tokyo.jp>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/05 22:26:22 by rmatsuka          #+#    #+#              #
#    Updated: 2021/06/09 12:00:00 by rmatsuka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minitalk
SERVER	=	server
CLIENT	=	client
LIBFT	=	libft/libft.a
LIB_DIR	=	libft/
SRCS	=	server.c \
			client.c

OBJS	=	$(SRCS:.c=.o)
CC		= 	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

all:		$(NAME)	## Create server & client

$(NAME):	$(OBJS) $(SERVER) $(CLIENT)

server:		$(OBJS) $(LIBFT)	## Create server
			$(CC) $(CFLAGS) -o $(SERVER) $(LIBFT) server.o

client:		$(OBJS) $(LIBFT)	## Create client
			$(CC) $(CFLAGS) -o $(CLIENT) $(LIBFT) client.o

$(LIBFT):
			make -C $(LIB_DIR)

clean:	## Delete *.o file
			make clean -C $(LIB_DIR)
			$(RM) $(OBJS)

fclean:		clean	## Delete *.o & *.a file
			make fclean -C $(LIB_DIR)
			$(RM) $(SERVER) $(CLIENT)

bonus:		all	## Create bonus server & client

re:			fclean all	## Recompile

.PHONY:		all clean fclean re bonus help

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}'