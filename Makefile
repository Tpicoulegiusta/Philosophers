# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 15:07:49 by tpicoule          #+#    #+#              #
#    Updated: 2024/02/16 14:03:18 by tpicoule         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= philo

SOURCES		= philo.c \
			checker_args.c \
			checker_args_2.c \
			thread.c \
			philo_utils.c
OBJECTS		= ${SOURCES:.c=.o}
RM			= rm -f
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: 	${OBJECTS}
	${CC} ${CFLAGS} ${MLX} ${OBJECTS} -o ${NAME}

all:		${NAME}

clean:
	${RM} ${OBJECTS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re