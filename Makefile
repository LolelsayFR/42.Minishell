NAME			=	minishell

SRC				=	$(wildcard srcs/*.c)\
					$(wildcard srcs/*/*.c)\

CFLAGS			=	-Wall -Werror -Wextra -lreadline

LIBFT_PATH		=	./submodules/42.libft
LIBFT			=	$(LIBFT_PATH)/libft.a

all:	hello $(NAME)

hello:
	@echo "\e[48;2;100;0;00;1m WILDCARD BLYAT !\e[0m\n"
	@echo "\e[48;2;100;0;100;1m Welcome to "$(NAME)" Makefile !\e[0m\n"

d_info: hello
	@echo "\e[48;2;70;70;70;1m "$(NAME)" usage : \e[0m\n"
	@echo "./d_philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"

$(NAME): ${SRC} ${LIBFT}
	@echo "\e[48;2;0;155;0;1m Compile "$(NAME)" \e[0m\n"
	gcc ${SRC} ${CFLAGS} ${LIBFT} -o $(NAME)
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

$(LIBFT):
	git submodule update --init --recursive
	@echo "\e[48;2;0;155;0;1m Make LIBFT \e[0m\n"
	@$(MAKE) --no-print-directory -C $(LIBFT_PATH)
	@$(MAKE) --no-print-directory  clean  -C $(LIBFT_PATH)
	@echo "\e[48;2;0;0;155;1m Done for LIBFT \e[0m\n"

clean: hello
	@echo "\e[48;2;155;100;0;1m Clean "$(NAME)" dependencies \e[0m\n"
	@$(MAKE) --no-print-directory  fclean  -C $(LIBFT_PATH)
	@echo "\n\e[48;2;0;0;155;1m Done \e[0m\n"

fclean: hello clean
	@echo "\e[48;2;155;100;0;1m Uninstall "$(NAME)" \e[0m\n"
	$(RM) $(NAME)
	@echo "\e[48;2;0;0;155;1m Done \e[0m\n"

re:	fclean all

.PHONY: all clean fclean re
