################################# LICENSE ####################################
#                            Copyright 2016 Morphux                            #
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

NAME=		builder
CC =		gcc
LIB =		-Llib
CFLAGS =	-Wall -Wextra -Werror -Wno-unused-result \
			-Iinc -Ilib/inc \
			-std=c99 -g -O3 \
			-DVERSION="\"$(VERSION)\"" -DMAINTAINER="\"$(MAINTAINER)\"" -DNAME="\"$(NAME)\""
LFLAGS =	-lmorphux
SRCS =		$(wildcard src/*.c)
OBJS =		$(SRCS:%.c=%.o)
VERSION = 0.0.0.0
MAINTAINER = Jules HEZARD <hezardj@gmail.com>

all: $(NAME)

$(NAME): $(OBJS) lib
	make -C lib/
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB) $(LFLAGS)

check:
	make -C tests check

doc:
	doxygen docs/doxyfile

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean clean all
