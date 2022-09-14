# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabimich <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/27 17:57:39 by mabimich          #+#    #+#              #
#    Updated: 2022/09/09 04:54:56 by manuel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

SRCS		= main.c philo.c utils.c utils2.c

OBJS		= ${SRCS:.c=.o}

RM			= rm -f

CC			= cc

FLAGS		= -Wall -Wextra -Werror -pthread

all		: ${NAME}

%.o: %.c
	$(CC) -Wall -Wextra -Werror -o3 -g3 -c $< -o $@

${NAME}		: ${OBJS}
		  @echo "\033[34m----Compiling----"
		  @${CC} ${FLAGS} ${OBJS} -o ${NAME} 
		  @echo "OK\e[39m"

clean		:
		  @echo "\033[31m----Cleaning objects----"
		  @${RM} ${OBJS}
		  @${RM} ${OBJS_BONUS}
		  @echo "OK\e[39m"

fclean		: clean
		  @echo "\033[33m----Cleaning all----"
		  @${RM} ${NAME}
		  @${RM} ${NAME_BONUS}
		  @echo "OK\e[39m"

re		: fclean all

.PHONY	: all clean fclean re
