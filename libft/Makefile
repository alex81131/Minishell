# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 12:27:51 by kyeh              #+#    #+#              #
#    Updated: 2024/09/21 19:45:13 by kyeh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3 -fPIC #-fsanitize=address
LIBC	= ar rcs

# Colors
DEFAULT		= \e[0;39m
BLACK		= \e[0;30m
WHITE		= \e[0;97m
WHITE_BOLD	= \e[1;97m
GREY		= \e[0;37m
GREY_DARK	= \e[0;90m
GREY_ITALIC	= \e[3;90m
RED			= \e[0;31m
RED_BOLD	= \e[1;31m
RED_LIGHT	= \e[0;31;110m
RED_FLASH	= \e[0;31;5;110m
PINK		= \e[0;38;5;198m
PINK_BOLD	= \e[1;95m
PINK_LIGHT	= \e[0;38;5;200m
ORANGE_ITALIC= \e[3;91m
YELLOW		= \e[0;33m
YELLOW_BOLD	= \e[1;33m
GREEN		= \e[1;32;111m
GREEN_BOLD	= \e[1;32m
GREEN_LIGHT	= \e[0;38;5;121m
BLUE_BOLD	= \e[1;34m
BLUE_LIGHT	= \e[0;38;5;123m
BLUE_GREY	= \e[1;38;5;110m
SKY			= \e[0;36m
SKY_BOLD	= \e[1;36m
CYAN_LIGHT	= \e[0;96m
NOCOLOR		= \e[0m
RESET_LINE	= \e[2K\r

# Source files
LIBFT = \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_toupper.c ft_tolower.c \
		\
		ft_memset.c ft_strlen.c ft_bzero.c ft_memcpy.c \
		ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_strchr.c \
		ft_strrchr.c ft_strcmp.c ft_strncmp.c ft_memchr.c \
		ft_memcmp.c ft_strnstr.c ft_strdup.c \
		\
		ft_atoi.c ft_atoi_base.c ft_calloc.c \
		\
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
		ft_itoa.c ft_strmapi.c ft_striter.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		\
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		ft_lstmap.c
FT_PRINTF = \
		ft_putchar.c ft_putstr.c ft_putnbr.c \
		ft_printf.c ft_printf_number_hex.c\
		ft_printf_ptr.c ft_printf_unsigned_int.c \
		ft_printf_fd.c ft_printf_ptr_fd.c ft_printf_number_hex_fd.c
GNL = \
		get_next_line.c
FDF = \
		fdf.c
MINISHELL = \
		ft_strndup.c ft_strjoin_free.c

SRC_FILES = \
		$(LIBFT) $(FT_PRINTF) $(GNL) $(FDF) $(MINISHELL)
SRC_PATH = src/
SRC = $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ_FILES	= ${SRC_FILES:.c=.o}
OBJ_PATH = obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))


NAME	= libft.a
RM		= rm -rf
HEADER	= include

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER) Makefile
	@mkdir -p $(OBJ_PATH)
	@printf "$(RESET_LINE)$(RED_FLASH)Compiling...	$(GREY)$<$(SKY) $(NOCOLOR)"
	@$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

${NAME}: $(OBJ)
	@$(LIBC) $@ $^
	@printf "$(RESET_LINE)$(BLUE_GREY)libft\t: $(GREEN_LIGHT)Updated\n$(NOCOLOR)"

all: $(NAME)

clean:
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting libft srcs/	$(GREY)"
	@sleep 0.1
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting libft srcs/.	$(GREY)"
	@sleep 0.1
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting libft srcs/..	$(GREY)"
	@sleep 0.1
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting libft srcs/...	$(GREY)"
	@sleep 0.1
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting libft srcs/	$(GREY)"
	@sleep 0.1
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting libft srcs/.	$(GREY)"
	@sleep 0.1
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting libft srcs/..	$(GREY)"
	@sleep 0.1
	@printf "$(RESET_LINE)$(RED_FLASH)Deleting libft srcs/...	$(GREY)"
	@sleep 0.1
	@$(RM) $(OBJ_PATH)
	@printf "$(RESET_LINE)$(RED_FLASH)Deleted successfully!\n$(NOCOLOR)"

fclean: clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
# @ suppresses the command being printed to the terminal when it's executed.
# all, clean,... are phony targets, not actual files, used as conditions after make command
# when "make", it builds only the first target in the makefile
#
# -c means compile without linking, and thus renders .o files
# $< represents the dependency to build the target
# $@ represents the target name itself
# -o means output
# $@ specifies that the output should have the same name as the target file
# ar rcs = ar rc + ranlib