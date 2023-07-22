# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnorazma <nnorazma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 14:22:32 by nnorazma          #+#    #+#              #
#    Updated: 2023/07/22 17:31:15 by nnorazma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = btc

CC = c++
FLAGS = -Wall -Werror -Wextra -I -fsanitize=address

RM = rm -rf

SRCS = main.cpp BitcoinExchange.cpp
INC = BitcoinExchange.hpp

OBJS = ${SRCS:%.cpp=%.o}

%.o: %.cpp ${INC}
		@printf "\033[38;5;121mCompiling $<...\033[0m\r"
		@${CC} ${FLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
		@echo "\n\033[38;5;204mBitcoin Exchange\033[0m"
		@${CC} ${FLAGS} ${OBJS} -o $@

clean:
		@echo "\033[38;5;227mRemoving Objects\033[0m"
		@${RM} ${OBJS}

fclean:	clean
		@echo "\033[38;5;81mRemoving Executable\033[0m"
		@${RM} ${NAME}

re: fclean all