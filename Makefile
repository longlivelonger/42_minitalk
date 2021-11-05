# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbronwyn <sbronwyn@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 14:27:05 by sbronwyn          #+#    #+#              #
#    Updated: 2021/11/03 13:29:18 by sbronwyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SERVER_BIN = server
SERVER_SRC = server.c

CLIENT_BIN = client
CLIENT_SRC = client.c

BONUS_OBJ = server_bonus.o client_bonus.o

RM = rm -rf

all: $(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_SRC:.c=.o)
	$(CC) $(CFLAGS) -o $@ $<

$(CLIENT_BIN): $(CLIENT_SRC:.c=.o)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(SERVER_SRC:.c=.o) $(CLIENT_SRC:.c=.o) $(BONUS_OBJ)

fclean: clean
	$(RM) $(SERVER_BIN) $(CLIENT_BIN)

re: fclean all

bonus:
	@make SERVER_SRC="server_bonus.c" CLIENT_SRC="client_bonus.c" all

.PHONY: all re clean fclean bonus