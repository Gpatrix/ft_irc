CC		= c++
CFLAGS	=  -g3 -std=c++98
# -Wall -Wextra -Werror
RM		= rm -f

NAME	= ircserv

FILE	:= main.cpp src/Server/Server.cpp src/User/User.cpp src/Channel/Channel.cpp

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
