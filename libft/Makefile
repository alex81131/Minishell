# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyeh <kyeh@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 12:27:51 by kyeh              #+#    #+#              #
#    Updated: 2024/09/05 16:23:01 by kyeh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=address
LIBC	= ar rcs

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
RM		= rm -f
HEADER	= include

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER) Makefile
	@mkdir -p $(OBJ_PATH)
	@printf "\033[2K\r\033[0;31;5;110mCompiling...	\033[37m$<\033[36m \033[0m"
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

${NAME}: $(OBJ)
	$(LIBC) $@ $^

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
# all, clean,... are phony targets, not actual files, used as conditions after make command
# when "make", it builds only the first target in the makefile
#
# -c means compile without linking, and thus renders .o files
# $< represents the dependency to build the target
# $@ represents the target name itself
# -o means output
# $@ specifies that the output should have the same name as the target file
# ar rcs = ar rc + ranlib
