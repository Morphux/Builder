################################# LICENSE ####################################
#                            Copyright 2017 Morphux                            #
#                                                                              #
#        Licensed under the Apache License, Version 2.0 (the "License");       #
#        you may not use this file except in compliance with the License.      #
#                  You may obtain a copy of the License at                     #
#                                                                              #
#                 http://www.apache.org/licenses/LICENSE-2.0                   #
#                                                                              #
#      Unless required by applicable law or agreed to in writing, software     #
#       distributed under the License is distributed on an "AS IS" BASIS,      #
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  #
#        See the License for the specific language governing permissions and   #
#                       limitations under the License.                         #
################################################################################

NAME =		test
CC =		gcc
CFLAGS =	-Wall -Wextra -Wno-unused-result -g -O3 -I../lib/inc -I../inc -lmorphux -DCOMPILE_WITH_TEST -std=c99
SRCS =		$(wildcard *.c) $(wildcard ../src/*.c)
OBJS =		$(SRCS:%.c=%.o)
OSTYPE =	$(shell uname)
COVFLAGS =	-coverage -lgcov

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L../lib/ -lmorphux -ldl

check: $(NAME)
	./$(NAME)

valgrind: $(NAME)
	valgrind --leak-check=full --error-exitcode=1 ./$(NAME)

coverage:
	$(MAKE) fclean all CFLAGS="$(CFLAGS) $(COVFLAGS)"
	./$(NAME)

clean:
	rm -f $(OBJS)
	rm -f *.gcda
	rm -f *.gcno

fclean: clean
	rm -f $(NAME)

re: fclean all
