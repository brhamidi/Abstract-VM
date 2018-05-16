# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhamidi <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/22 18:13:38 by bhamidi           #+#    #+#              #
#    Updated: 2018/05/04 18:25:27 by bhamidi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX=clang++
CXXFLAGS=-I$(INCLUDE_DIR) -Wall -Wextra -Werror -O2 -std=c++11

SRCS=main.cpp Lexer.cpp Parser.cpp Abstrack.cpp Factory.cpp
OBJS=$(SRCS:.cpp=.o)

INCLUDE_DIR=./

EXEC=abstract_vm

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
	@echo Program linked

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS)
	@echo "Objects files deleted"

fclean: clean
	rm -rf $(EXEC)
	@echo "Program deleted"

re: fclean all

.PHONY: clean fclean re all
