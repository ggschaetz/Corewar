# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybenoit <ybenoit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/19 18:35:20 by ybenoit           #+#    #+#              #
#    Updated: 2017/12/05 12:10:56 by ybenoit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=@gcc -g
NAME=asm

INCLUDES=./includes

SRC_DIR=srcs
SRC_BASE=main.c\
		extension.c\
		writter.c\
		parsing.c\
		line_reader.c\
		treatment.c\
		op.c\
		conversion_in_bin.c\
		usefull.c\
		label.c\
		recup_arg.c\
		error.c\
		error_part2.c\
		checking_param.c\
		parsing_line.c\
		checking.c\
		recup_direct_classic.c\
		options.c\
		fork_zjmp_live_in_bin.c\
		live.c\
		indirect.c\
		zjmp.c\
		ft_check_if_is_number.c\
		free_asm.c\
		ft_malloc_tab.c

SRCS=$(addprefix $(SRC_DIR)/, $(SRC_BASE))
OBJS=$(addprefix $(SRC_DIR)/, $(SRC_BASE:.c=.o))

LIBDIR=../libft
LIBFTA=libftprintf.a
LIB=$(addprefix $(LIBDIR)/, $(LIBFTA))

C_NO="\033[00m"
C_OK="\033[32m"
C_GOOD="\033[32m"
C_ERROR="\033[31m"
C_WARN="\033[33m"

SUCCESS=$(C_GOOD)SUCCESS$(C_NO)
OK=$(C_OK)OK$(C_NO)

all: libftprintf42 $(NAME)

$(NAME): $(OBJS)
		@$(CC) -o $(NAME) $(OBJS) $(LIB)
		@echo "\033[31m    _   ___ __  __   ___ ___  ___ _____      ___   ___\033[00m"
		@echo "\033[31m   /_\ / __|  \/  | / __/ _ \| _ \ __\ \    / /_\ | _ \ \033[00m"
		@echo "\033[31m  / _ \\__ \| |\/| || (_| (_) |   / _| \ \/\/ / _ \|   / \033[00m"
		@echo "\033[31m /_/ \_\___/_|  |_|_\___\___/|_|_\___| \_/\_/_/ \_\_|_\ \033[00m"
		@echo "\033[31m                 |___|                                  \033[00m"

%.o: %.c $(INCLUDES)/libft.h $(INCLUDES)/ft_printf.h
		@$(CC) -c -o $@ $< $(LIB) -I $(INCLUDES)

libftprintf42:
		@make -C $(LIBDIR)

clean:
		@rm -f $(OBJS)
		@make -C $(LIBDIR) clean
		@echo "Cleaning" [ $(NAME) ] "..." $(OK)

fclean: clean
		@rm -f $(NAME)
		@make -C $(LIBDIR) fclean
		@echo "Delete" [ $(NAME) ] $(OK)


re: fclean all


.PHONY: clean all re fclean
