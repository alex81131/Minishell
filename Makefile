# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 14:58:30 by kyeh              #+#    #+#              #
#    Updated: 2024/08/13 18:59:59 by kyeh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
BLUE		= \033[0;38;5;123m
LIGHT_PINK	= \033[0;38;5;200m
PINK		= \033[0;38;5;198m
DARK_BLUE 	= \033[1;38;5;110m
GREEN		= \033[1;32;111m
LIGHT_GREEN	= \033[0;38;5;121m
LIGHT_RED	= \033[0;31;5;110m
FLASH_GREEN	= \033[33;32m
WHITE_BOLD	= \033[37m
GREY		= \033[3;90m
ORANGE		= \033[3;91m
YELLOW		= \033[0;33m
NOCOLOR		= \033[0m

# Name
NAME	= minishell

# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g3

# Source files
SRC_PARSING	=	$(addprefix parsing/, \
				analyzer.c			fill_str_with_var.c		operator.c \
				operator_counter.c	parsing.c				parse_cmd.c \
				quote_error.c)
SRC_EXEC	=	$(addprefix exec/, \
				builtin.c				builtin_cd.c		builtin_export.c \
				exec_cmd.c				signal.c)
SRC_VAR		=	$(addprefix var/, \
				env.c)
SRC_REDIR	=	$(addprefix redirection/, \
				redirection.c			left_redirection.c	right_redirection.c \
				lonely_command.c)
SRC_DISPLAY	=	$(addprefix display/, \
				display.c)
SRC_UTILS	=	$(addprefix utils/, \
				ft_arrlen.c				ft_arrjoin.c			ft_charpos.c \
				ft_count_whitespace.c	ft_exit.c				ft_insert.c \
				ft_memdel.c				ft_split_minishell.c	ft_strclean.c \
				ft_strjoin_free.c		ft_strtok.c				free_string.c \
				skip_quote.c)
SRC_HASH	=	$(addprefix hash/, \
				ft_hash_initialize.c	ft_hashnew.c		ft_hash_addfront.c \
				ft_hash_addback.c		ft_hashdel.c		ft_hash_free.c \
				ft_hash_search_value.c	ft_hash_find.c		ft_hash_change_value.c \
				ft_hashlen.c			ft_hash_display.c	ft_hash_sort.c)
SRC_FILES	=	main.c $(SRC_PARSING) $(SRC_EXEC) $(SRC_VAR) $(SRC_REDIR) $(SRC_DISPLAY) $(SRC_UTILS) $(SRC_HASH)
SRC_PATH	=	src/
SRC			=	$(addprefix $(SRC_PATH), $(SRC_FILES))

HEADER		=	include/

# Object files
OBJ_FILES	=	$(SRC_FILES:%.c=%.o)
OBJ_PATH	=	obj/
OBJ			=	$(addprefix $(OBJ_PATH), $(OBJ_FILES))

RM		=	rm -rf

LIBFT	=	libft+/libft.a
#######################################################

$(NAME): $(OBJ)
	@gcc $(CFLAGS) $^ $(LIBFT) -o  $@
	@printf "	\033[2K\r$(DARK_BLUE)minishell\t: $(LIGHT_GREEN)Updated\n\033[0m"

all: $(OBJ_PATH) $(LIBFT) $(NAME) $(HEADER)
	@:

e:	exec
exec:
	@$(MAKE) all
	@./minishell

# Clean file directory
clfd:
	@rm -f bli blo blu ble cat ls env a b c aa bb pouet toto make 2>/dev/null

$(LIBFT): libft+/include/libft.h
	@$(MAKE) -C libft+/

$(OBJ_PATH):
	@mkdir -p obj/ 2> /dev/null
	@mkdir -p obj/parsing 2> /dev/null
	@mkdir -p obj/exec 2> /dev/null
	@mkdir -p obj/var 2> /dev/null
	@mkdir -p obj/display 2> /dev/null
	@mkdir -p obj/redirection 2> /dev/null
	@mkdir -p obj/utils 2> /dev/null

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER)/minishell.h Makefile
	@mkdir -p $(dir $@)
	@printf "\033[2K\r$(LIGHT_RED)Compiling...	\033[37m$<\033[36m \033[0m"
	@gcc $(CFLAGS) -I $(HEADER) -I libft+/include -c $< -o $@

clean:
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/.	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/..	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/...	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/.	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/..	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Deleting minishell srcs/...	\033[37m"
	@sleep 0.1
	@${RM} ${OBJ_PATH} cube3D.dSYM
	@printf "\33[2K\r$(LIGHT_RED)Deleted successfully!\n\033[0m"

fclean: clean
	$(RM) $(NAME)

re:
	@$(MAKE) fclean
	@make -C libft+/ re
	@$(MAKE) all

norm:
	@printf "\n${GREEN}##########${YELLOW} NORMINETTE ${GREEN}##########${NOCOLOR}\n"
	@printf "\n${GREEN}Minishell:${BLUE}\n\n"
	@norminette $(SRC_PATH) $(HEADER)
	@printf "${NOCOLOR}"
full_norm:
	@printf "\n${GREEN}##########${YELLOW} NORMINETTE ${GREEN}##########${NOCOLOR}\n"
	@printf "\n${GREEN}LIBFT:${BLUE}\n\n"
	@norminette libft+
	@printf "\n${GREEN}Minishell:${BLUE}\n\n"
	@norminette $(SRC_PATH)
	@printf "${NOCOLOR}"

normed:
	@norminette $(SRC_PATH) $(HEADER)
	@$(MAKE) continue
	@echo ""
	@git add .
	@git commit -m "normed" 1>/dev/null
	@printf "\33[2K\r$(YELLOW)Push on repositories ?\n\033[0m"
	@$(MAKE) continue
	@echo ""
	@$(MAKE) push

push:
	@printf "\33[2K\r$(LIGHT_RED)Pushing 	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Pushing .	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Pushing ..	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Pushing ...	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Pushing 	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Pushing .	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Pushing ..	\033[37m"
	@sleep 0.1
	@printf "\33[2K\r$(LIGHT_RED)Pushing ...	\033[37m"
	@sleep 0.1
	@git push origin `git symbolic-ref --short HEAD`
	@printf "\33[2K\r$(FLASH_GREEN)Pushed successfully on vogsphere !\n\033[0m"

update:
	@git request-pull HEAD https://github.com/alex81131/Minishell.git master

lib:
	@$(MAKE) -C libft+
cleanlib:
	@$(MAKE) clean
	@$(MAKE) -C libft+/ clean
fcleanlib:
	@$(MAKE) fclean
	@$(MAKE) -C libft+/ fclean
relib:
	@$(MAKE) fclean
	@$(MAKE) -C libft+/ re
	@$(MAKE) all

continue:
	@echo ""
	@while [ -z "$$CONTINUE" ]; do \
		read -r -p "Press [y/N] to continue : " CONTINUE; \
	done ; \
	[ $$CONTINUE == "y" ] || [ $$CONTINUE == "Y" ] || (echo "Exiting ..." ; exit 1 2> /dev/null)

git-%:
	@$(MAKE) clfd
	# @$(MAKE) norm
	@$(MAKE) continue
	@echo ""
	@$(MAKE) test
	@$(MAKE) continue
	@echo ""
	@git add .
	@git status
	@$(MAKE) continue
	@echo ""
	@printf "\33[2K\r$(FLASH_GREEN)Commit name :\t[$(@:git-%=%)]\n\033[0m"
	@$(MAKE) continue
	@git commit -m "$(@:git-%=%)" 1>/dev/null
	@printf "\33[2K\r$(YELLOW)\nPush on repositories ?\033[0m"
	@echo ""
	@$(MAKE) continue
	@echo ""
	@$(MAKE) push
	@echo ""
	@printf "\33[2K\r$(GREEN)Everything done\n\n\033[0m"

pull:
	@git checkout master
	@git pull origin master
	@gco $USER 2> /dev/null
	@git merge master

call: all
	@nm -g $(addprefix ${OBJ_PATH}, ${OBJ_FILES})

test: all
	@sh tester/test.sh 0.01
	@printf "\33[2K\r$(GREEN)Test done\n\n\033[0m"

full_check: all
	@$(MAKE) full_norm
	@$(MAKE) continue
	@echo ""
	@$(MAKE) call
	@$(MAKE) continue
	@echo ""
	@$(MAKE) relib
	@printf "\33[2K\r$(FLASH_GREEN)\nCommit ?\n\033[0m"
	@$(MAKE) continue
	@echo ""
	@git add .
	@git commit -m "Fully checked" 1>/dev/null
	@printf "\33[2K\r$(YELLOW)Push on repositories ?\n\033[0m"
	@$(MAKE) continue
	@echo ""
	@$(MAKE) push

.PHONY: all e exec clfd libft+/include/libft.h clean fclean re norm full_norm normed push update lib cleanlib fcleanlib relib continue git-% pull call test full_check
#	@mkdir -p $(dir $@) is used in Makefile rules to ensure that the directory where the object file will be placed exists before attempting to create the object file.
#		-p flag creates any missing parent directories in the specified path:
#			mkdir -p path/to/directory
#			it'll create path and path/to if either of them does not exist.
#		$(dir $@) retrieves the directory path from the target file path:
#			if $@ is obj/main.o, $(dir $@) will be obj/