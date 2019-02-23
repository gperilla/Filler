# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gperilla <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 16:43:17 by gperilla          #+#    #+#              #
#    Updated: 2018/01/31 15:22:56 by gperilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gperilla.filler

CC = gcc

WARNINGS = -Werror -Wextra -Wall

INC = -I. -I libft/ -I libft/ft_printf/

LIB = -L libft/ -lft \

OBJC = 	main.c \
		filler_gets.c \
		filler_inits.c \
		filler_msc.c

OBJ = $(OBJC:.c=.o)

COLOR = $(shell bash -c 'echo $$RANDOM')

define OK
	@$(eval COLOR=$(shell echo $$(($(COLOR)+1))))
	@tput setaf $(COLOR)
	@echo -n $1
	$(eval COLOR=$(shell echo $$(($(COLOR)+1))))
	@tput setaf $(COLOR)
	@echo ' [Compiled]'
	@tput sgr0
endef

define ISOK
	@$(eval COLOR=$(shell echo $$(($(COLOR)+1))))
	@tput setaf $(COLOR)
	@echo $1 '[Ready]'
	$(eval COLOR=$(shell echo $$(($(COLOR)+1))))
	@tput setaf $(COLOR)
	tput smso
	tput smul
	@echo '[Run it you fool]'
	@tput sgr0
endef

all: $(NAME)

$(NAME): $(OBJ)
	@make --silent -C visu
	@make -C libft
	@$(CC) $(INC) $(WARNINGS) $(LIB) $(OBJ) -o $@
ifndef SILENT
	@$(call ISOK, $@)
endif

test:
	@make --silent -C visu/ test
	@make -j4 -C libft SILENT=1
	@$(CC) $(INC) $(LIB) $(OBJC) -o $(NAME)
	@tput smso
	@echo 'test it'

fast:
	@make -j4 -C libft SILENT=1
	@make --silent -C visu
	@make SILENT=1
	@tput smso
	@echo 'ready for action'

%.o: %.c
	@gcc -c $(INC) $(WARNINGS) $< -o $@
ifndef SILENT
	$(call OK, $*)
endif

clean:
	@make --silent -C  visu clean
	@make -C libft clean
	@rm -f $(OBJ)
	@echo 'removed .o'

fclean: clean
	@make --silent -C  visu fclean
	@make -C libft fclean
	@rm -rf $(NAME)
	@echo 'All your base are belong to us'

re: fclean all

.PHONY: all clean fclean re test
