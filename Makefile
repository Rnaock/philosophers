# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabimich <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/27 17:57:39 by mabimich          #+#    #+#              #
#    Updated: 2022/09/06 17:34:45 by mabimich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

LIB_DIR		= ./libft

LIBFT		= ./libft/libft.a

SRCS		= main.c philo.c

OBJS		= ${SRCS:.c=.o}

RM		= rm -f

CC		= cc

FLAGS		= -Wall -Wextra -Werror -pthread

all		: ${NAME}

%.o: %.c
	$(CC) -Wall -Wextra -Werror -o3 -g3 -c $< -o $@

${LIBFT}		:
		  @echo "\033[35m----Building libft----"
		  @make -sC ${LIB_DIR}
		  @echo "OK"

${NAME}			: ${OBJS} ${LIBFT}
		  @echo "\033[34m----Compiling----"
		  @${CC} ${FLAGS} ${OBJS} -o ${NAME} ${LIBFT} 
		  @echo "OK\e[39m"

clean		:
		  @echo "\033[31m----Cleaning libft----"
		  @make clean -sC ${LIB_DIR}
		  @echo "OK"
		  @echo "\033[31m----Cleaning objects----"
		  @${RM} ${OBJS}
		  @${RM} ${OBJS_BONUS}
		  @echo "OK\e[39m"

fclean		: clean
		  @echo "\033[33m----Cleaning all----"
		  @${RM} ${NAME}
		  @${RM} ${NAME_BONUS}
		  @${RM} ${LIBFT}
		  @echo "OK\e[39m"

re		: fclean all

.PHONY	: all bonus clean fclean re
