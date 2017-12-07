# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkantzer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/21 10:40:00 by mkantzer          #+#    #+#              #
#    Updated: 2017/12/05 14:24:13 by arive-de         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
WHERE = vm
INC = $(WHERE)/includes
CFLAGS = -Wall -Werror -Wextra
LIB_DIR = libft/
SRC_DIR = $(WHERE)/srcs
SRC_BASE = main.c \
		   list.c \
		   op.c \
		   op_f.c \
		   play.c \
		   init.c \
		   get_champ.c \
		   print_p.c \
		   tools.c \
		   verbose.c \
		   tools_f.c \
		   print.c \
		   rip.c \
		   cur_op.c \
		   checkeur.c \
		   set_len.c\
		   live.c \
		   ld.c \
		   ldi.c \
		   lld.c \
		   lldi.c \
		   st.c \
		   sti.c \
		   aff.c \
		   add.c \
		   sub.c \
		   and.c \
		   or.c \
		   xor.c \
		   zjmp.c \
		   fork.c \
		   lfork.c

OBJ_DIR = $(WHERE)/obj
OBJ_BASE = $(SRC_BASE:.c=.o)

SRC=$(addprefix $(SRC_DIR)/, $(SRC_BASE))
OBJ=$(addprefix $(OBJ_DIR)/, $(SRC_BASE:.c=.o))

C_NO="\033[00m"
C_OK="\033[32m"
C_GOOD="\033[32m"
C_ERROR="\033[31m"
C_WARN="\033[33m"

SUCCESS=$(C_GOOD)SUCCESS$(C_NO)
OK=$(C_OK)OK$(C_NO)

all: $(NAME)

$(NAME): $(LIB_DIR)/libftprintf.a $(OBJ)
	@gcc $(CFLAGS) -L$(LIB_DIR) -lftprintf $(OBJ) -o $@
	@echo "\033[31m   ___ ___  ___ _____      ___   ___\033[00m"
	@echo "\033[31m  / __/ _ \| _ \ __\ \    / /_\ | _ \ \033[00m"
	@echo "\033[31m | (_| (_) |   / _| \ \/\/ / _ \|   / \033[00m"
	@echo "\033[31m  \___\___/|_|_\___| \_/\_/_/ \_\_|_\ \033[00m"
	@echo "\033[31m                                      \033[00m"

ASM:
	Make -C ./ASM all

$(OBJ_DIR):
	mkdir $@

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)/vm.h
	@gcc $(CFLAGS) -I$(INC) -I$(LIB_DIR)/includes -c $< -o $@

$(LIB_DIR)/libftprintf.a:
	@Make -C ./$(LIB_DIR)

clean:
	@Make -C ./$(LIB_DIR) clean
	@rm -f $(OBJ)
	@echo "Cleaning" [ $(NAME) ] "..." $(OK)

fclean:
	@Make -C ./$(LIB_DIR) fclean
	@rm -f $(NAME)
	@echo "Delete" [ $(NAME) ] $(OK)

full_clean: clean
	@Make -C ./ASM clean

full_fclean: full_clean fclean
	@rm -f ASM/asm

full: all
	@Make -C ./ASM asm

full_re: full_fclean full

re: fclean all

.PHONY: full_clean full_fclean full $(NAME) clean fclean all re full_re ASM 
