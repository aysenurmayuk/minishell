NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
M_SRC = minishell.c \
	parse/dollar.c parse/parse_utils.c parse/parse.c parse/pipe.c parse/prep_for_exec.c parse/prep_for_exec_2.c  parse/quote_check.c parse/redirect_check.c parse/redirect_utils.c parse/redirect_utils_2.c parse/redirect.c \
	builtins/env.c builtins/exit.c builtins/pwd.c builtins/builtin_check.c builtins/echo.c builtins/cd.c builtins/export.c builtins/unset.c \
	utils/utils.c utils/split_func.c utils/gnl.c \
	free/free.c free/free_2.c free/error.c\
	executor/exec.c executor/exec_utils.c
LIBSRC = libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c \
	libft/ft_isprint.c libft/ft_itoa.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c \
	libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strchr.c \
	libft/ft_strdup.c libft/ft_striteri.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strmapi.c \
	libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_toupper.c libft/ft_tolower.c

SRC = $(M_SRC) $(LIBSRC)
OBJECTS = $(SRC:.c=.o)
READLINE = -L./lib/readline/lib -I./lib/readline/include/readline -lreadline -lncurses
DIR = $(shell echo $(PWD))
RL = ./lib/readline/lib/libreadline.a
RM = rm -rf

all: $(NAME)

$(NAME): $(RL) $(SRC)
		$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(READLINE)
$(RL):
			@echo "Downloading the readline library"
			@curl -O https://ftp.gnu.org/gnu/readline/readline-8.2-rc1.tar.gz
			@tar -xvf readline-8.2-rc1.tar.gz
			@$(RM) readline-8.2-rc1.tar.gz
			@cd readline-8.2-rc1 && ./configure --prefix=$(DIR)/lib/readline && make && make install
			@$(RM) readline-8.2-rc1
			@echo "Download completed"

rclean:
	@$(RM) lib/readline
	@echo "Readline removed"

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re push