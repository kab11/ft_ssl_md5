# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kblack <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/14 20:26:15 by kblack            #+#    #+#              #
#    Updated: 2019/03/07 21:53:57 by kblack           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

SRC		=	ascii_handler.c \
			ascii_helpers.c \
			float_helpers.c \
			ft_printf.c \
			handle_precision.c \
			print_conversion.c \
			print_digits.c \
			print_float.c \
			print_hex_digits.c \
			signed_int_handler.c \
			unsigned_int_handler.c 


INC_FT	=	-I libft
LINK_FT	=	-L libft -l ft
FT		=	$(INC_FT) $(LINK_FT)

OFL = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OFL)
	make -C libft
	cp libft/libft.a ./$(NAME)
	ar rc $(NAME) $(OFL)
	ranlib $(NAME)

$(OFL): $(SRC)
	@$(CC) $(CFLAGS) $(INC_FT) -I . -c $(SRC)

clean:
	rm -rf $(OFL)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all
	make -C libft re
