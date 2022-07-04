# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chanhuil <chanhuil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/13 15:59:22 by chanhuil          #+#    #+#              #
#    Updated: 2022/07/04 14:54:08 by chanhuil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_containers
SRCS		= main.cpp
OBJS		= ${SRCS:.cpp=.o}

CC			= c++
RM			= rm -f

CPPFLAGS	= -Wall -Wextra -Werror -std=c++98

.c.o:
	${CC} ${CPPFLAGS} -I ./incs -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
	${CC} ${CPPFLAGS} -I ./incs ${OBJS} -o ${NAME}

all:		${NAME}

clean:
	${RM} ${OBJS}

fclean:		clean
	${RM} ${NAME}

re:			fclean all

.PHONY: .c.o all clean fclean re
