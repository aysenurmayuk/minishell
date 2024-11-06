NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalpha.c ft_isascii.c\
	   ft_strlcpy.c ft_isalnum.c ft_strlen.c  ft_strlcat.c \
	   ft_atoi.c ft_strncmp.c ft_toupper.c ft_tolower.c \
	   ft_strchr.c  ft_strrchr.c ft_strnstr.c  ft_memset.c \
	   ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c  \
	   ft_strdup.c ft_calloc.c ft_strjoin.c ft_strtrim.c\
	   ft_substr.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	   ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c ft_itoa.c \
	   ft_isprint.c ft_split.c ft_memcmp.c \


OBJS = ${SRCS:.c=.o}

LIBC = ar rcs
CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

clean: 
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re 