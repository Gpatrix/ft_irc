CC		= c++
CFLAGS	= -Wall -Wextra -Werror -std=c++98 -g3 -O3

RM		= rm -f

NAME	= ircserv

FILE	:= main.cpp src/Server/Server.cpp src/User/User.cpp src/Channel/Channel.cpp src/Server/parser.cpp \
			src/Server/exec/exec.cpp

FILE += src/Server/exec/CAP.cpp src/Server/exec/NICK.cpp src/Server/exec/USER.cpp

FILE += src/Numerics/_001_RPL_WELCOME.cpp src/Numerics/_464_ERR_PASSWDMISMATCH.cpp

OBJS	= $(FILE:%.cpp=%.o)

all: $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I ./include

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

clean:
	@$(RM) $(OBJS)

fclean:		clean
	@$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
