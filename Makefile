# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabimich <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/27 17:57:39 by mabimich          #+#    #+#              #
#    Updated: 2022/08/27 18:12:38 by mabimich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
NAME_BONUS	= philo_bonus

LIB_DIR		= ./libft

LIBFT		= ./libft/libft.a

SRCS		= main.c
SRCS_BONUS	= main_bonus.c

OBJS		= ${SRCS:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

RM		= rm -f

CC		= cc

FLAGS		= -Wall -Wextra -Werror

all		: ${NAME}
bonus	: ${NAME_BONUS}

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

#${NAME_BONUS}	: ${OBJS_BONUS} ${LIBFT}
#		  @echo "\033[34m___--Compiling bonus--___"
#		  @${CC} ${FLAGS} ${OBJS_BONUS} -o ${NAME_BONUS} ${LIBFT} 
#		  @echo "OK\e[39m"

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
