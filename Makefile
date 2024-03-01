# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 15:07:49 by tpicoule          #+#    #+#              #
#    Updated: 2024/03/01 11:23:25 by tpicoule         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= philo

SOURCES		= philo.c \
			checker_args.c \
			checker_args_2.c \
			thread.c \
			forks_utils.c \
			philo_utils.c
OBJECTS		= ${SOURCES:.c=.o}
RM			= rm -f
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -fsanitize=thread

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: 	${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o ${NAME}

all:		${NAME}

clean:
	${RM} ${OBJECTS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
