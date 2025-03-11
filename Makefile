# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchauvet <lchauvet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/06 10:15:47 by max               #+#    #+#              #
#    Updated: 2025/03/11 11:33:06 by lchauvet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables

NAME        = ircserv


INCLUDE     = include

TMP 	   = .tmp/
CC          = c++
CFLAGS      = -Wall -Wextra -Werror -std=c++98 -g3 -O0

RM          = rm -f
MKDIR       = mkdir


# **************************************************************************** #
#                                   Colors                                     #
# **************************************************************************** #

DEF_COLOR           =   \033[0;39m
GRAY                =   \033[0;90m
RED                 =   \033[0;91m
GREEN               =   \033[0;92m
YELLOW              =   \033[0;93m
BLUE                =   \033[0;94m
MAGENTA	            =   \033[0;95m
CYAN                =   \033[0;96m
WHITE               =   \033[0;97m
BOLD                =   $'\x1b[1m'
END                 =   $'\x1b[0m'
TERM_UP             =   \033[1A
TERM_CLEAR_LINE     =   \033[2K\r

# **************************************************************************** #
#                                   Sources                                    #
# **************************************************************************** #

SRC = ./main.cpp ./src/Channel/Channel.cpp ./src/Numerics/_001_RPL_WELCOME.cpp ./src/Numerics/_332_RPL_TOPIC.cpp ./src/Numerics/_353_RPL_NAMREPLY.cpp ./src/Numerics/_366_RPL_ENDOFNAMES.cpp ./src/Numerics/_405_ERR_TOOMANYCHANNELS.cpp ./src/Numerics/_421_ERR_UNKNOWNCOMMAND.cpp ./src/Numerics/_461_ERR_NEEDMOREPARAMS.cpp ./src/Numerics/_464_ERR_PASSWDMISMATCH.cpp ./src/Numerics/_475_ERR_BADCHANNELKEY.cpp ./src/Numerics/_433_ERR_NICKNAMEINUSE.cpp ./src/Numerics/_432_ERR_ERRONEUSNICKNAME.cpp ./src/Server/Server.cpp ./src/Server/cmd/CAP.cpp ./src/Server/cmd/NICK.cpp ./src/Server/cmd/PASS.cpp ./src/Server/cmd/PING.cpp ./src/Server/cmd/USER.cpp ./src/Server/cmd/JOIN.cpp ./src/Server/cmd/PRIVMSG.cpp ./src/Server/exec.cpp ./src/Server/utils.cpp ./src/Server/parser.cpp ./src/User/User.cpp 



OBJ_DIR       = $(TMP)obj/
OBJ           = $(patsubst %.cpp, $(OBJ_DIR)%.o, $(SRC))

DEPS            = $(OBJ:.o=.d)

# **************************************************************************** #
#                             progress_update                                  #
# **************************************************************************** #

COMPILED_COUNT  = 0

TOTAL_FILES     = $(words $(SRC)) 
define progress_update
    @if [ ! -f .compiled_count ]; then \
        echo 0 > .compiled_count; \
        printf "\n"; \
    fi; \
    COMPILED_COUNT=$$(cat .compiled_count); \
    COMPILED_COUNT=$$((COMPILED_COUNT + 1)); \
    echo $$COMPILED_COUNT > .compiled_count; \
    printf "$(TERM_UP)$(TERM_CLEAR_LINE)$(CYAN)Compilation progress: \
        $$((COMPILED_COUNT * 100 / $(TOTAL_FILES)))%% $(BLUE) ->$(1) $(DEF_COLOR)\n"; \
    if [ $$COMPILED_COUNT -eq $(TOTAL_FILES) ]; then \
        rm -f .compiled_count; \
    fi
endef
# **************************************************************************** #\
#                                   Rules                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "$(GREEN)%s compiled!\n$(DEF_COLOR)" $(NAME)
	@if [ -e .compiled_count ] ; then \
        $(RM) .compiled_count ;\
    fi

$(OBJ_DIR)%.o: %.cpp | $(OBJF)
	@mkdir -p $(dir $@)
	$(call progress_update,$(notdir $@))
	@$(CC) $(CFLAGS)  -I $(INCLUDE) -c $< -o $@

-include $(DEPS)

%.d: %.cpp
	@$(CC) $(CFLAGS) -MM $< -MF $@

$(OBJF):
	@$(MKDIR) -p $(OBJ_DIR)

clean:
	@if [ -d $(OBJ_DIR) ]; then \
		$(RM) -r $(OBJ_DIR); \
		printf "$(YELLOW)Removing %d objects from \"%s\" folder.\n$(DEF_COLOR)" $(words $(OBJ)) $(OBJ_DIR);\
	fi

fclean: clean
	@if [ -e $(NAME) ]; then \
		printf "$(YELLOW)Removing \"%s\"...\n$(DEF_COLOR)" $(NAME);\
		$(RM) -r $(NAME);\
	fi

re: fclean all

.PHONY: all clean fclean re 