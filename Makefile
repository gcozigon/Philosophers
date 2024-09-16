# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcozigon <gcozigon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 19:43:05 by lboulang          #+#    #+#              #
#    Updated: 2023/10/09 05:10:45 by gcozigon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= 	philo

SRCS_NAMES 		=	main.c utils.c parsing.c routine.c utils_philo.c \

DIR_SRCS		=	srcs

DIR_OBJS		=	objs

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

INC				=	-Iincludes -Ilibft

CC				=	cc

CFLAGS			=	-g3 -Wall -Werror -Wextra -pthread

MAKEFLAGS		=	--no-print-directory

all:	${NAME}

$(NAME): $(DIR_OBJS) $(OBJS)
	$(CC) $(CFLAGS) ${INC} $(OBJS) -o $(NAME)
	@echo "\033[31;5mphilo\033[0m"

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@ 

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

clean:
	rm -rf ${DIR_OBJS}

fclean:	clean
	rm -rf ${NAME}

re:	fclean all

-include $(DEPS)

.PHONY:	all clean fclean re bonus leaks stop