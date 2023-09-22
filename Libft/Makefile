# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luide-so <luide-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 15:35:28 by luide-so          #+#    #+#              #
#    Updated: 2023/09/09 12:33:23 by luide-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FT_ = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c ft_itoa.c ft_memchr.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
		ft_strdup.c ft_striteri.c ft_strjoin.c ft_strjoin_free_s1.c ft_strlcat.c ft_strlcpy.c \
		ft_strlen.c ft_strchrlen.c ft_strmapi.c ft_strncmp.c ft_strcmp.c \
		ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
		ft_tolower.c ft_toupper.c ft_strclen.c ft_free_array.c ft_free_array_size.c \
		ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
		ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
FT_PRINTF = ft_intlen.c ft_itoapositive.c ft_printf.c ft_puthex_fd.c print_chr.c \
			print_hex.c print_nbr.c print_pointer.c print_str.c print_unsigned.c
FT_GET_NEXT_LINE = get_next_line.c

SRC = ${FT_} ${FT_PRINTF} ${FT_GET_NEXT_LINE}
OBJS = ${addprefix ../Libft_obj/, ${SRC:.c=.o}}
HEADER = libft.h
INCLUDE = -I .
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS} ${HEADER}
	@ar rcs ../Libft_obj/${NAME} ${OBJS} ${HEADER}
	@echo "\n${NAME} created"

../Libft_obj/%.o: %.c
	@mkdir -p ../Libft_obj
	@${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

clean:
	@${RM} ${OBJS}
	@${RM} -r ../Libft_obj
	@echo "\nObjects deleted - libft"

fclean: clean
	@echo "\n${NAME} deleted"

re: fclean all

.PHONY: all clean fclean re
