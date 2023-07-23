# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: m4rrs <m4rrs@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 14:22:32 by nnorazma          #+#    #+#              #
#    Updated: 2023/07/23 22:53:16 by m4rrs            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RPN

CC = c++
FLAGS = -Wall -Werror -Wextra  -I -std=c++98 -fsanitize=address

RM = rm -rf

SRCS = main.cpp RPN.cpp
INC = RPN.hpp

OBJS = ${SRCS:%.cpp=%.o}

%.o: %.cpp ${INC}
		@printf "\033[38;5;121mCompiling $<...\033[0m\r"
		@${CC} ${FLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
		@echo "\n\033[38;5;204mWho thought reverse polish notation was a good idea?\033[0m"
		@${CC} ${FLAGS} ${OBJS} -o $@

clean:
		@echo "\033[38;5;227mRemoving Objects\033[0m"
		@${RM} ${OBJS}

fclean:	clean
		@echo "\033[38;5;81mRemoving Executable\033[0m"
		@${RM} ${NAME}

re: fclean all