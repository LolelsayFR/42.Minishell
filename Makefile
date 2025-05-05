NAME			=	minishell

SRC				=	srcs/main.c\
					srcs/signals.c\
					srcs/built-in/ms_cd.c\
					srcs/built-in/ms_echo.c\
					srcs/built-in/ms_env.c\
					srcs/built-in/ms_exit.c\
					srcs/built-in/ms_export.c\
					srcs/built-in/ms_pwd.c\
					srcs/built-in/ms_unset.c\
					srcs/exec/built_in_ex.c\
					srcs/exec/check_standard.c\
					srcs/exec/ex_free.c\
					srcs/exec/files_access.c\
					srcs/exec/is_cmd_in_id.c\
					srcs/exec/join.c\
					srcs/exec/ms_ex_check_struct.c\
					srcs/exec/numb_of_no_nl.c\
					srcs/exec/path.c\
					srcs/exec/unlink_all.c\
					srcs/exec/message_utils.c\
					srcs/exec/exec_all/finds.c\
					srcs/exec/exec_all/ms_exec.c\
					srcs/exec/exec_all/ms_exec_utils.c\
					srcs/exec/exec_all/ms_ex_free.c\
					srcs/exec/exec_all/opens.c\
					srcs/exec/exec_all/pipping.c\
					srcs/exec/exec_one/exec_one.c\
					srcs/exec/exec_one/finds.c\
					srcs/exec/exec_one/inits_and_free.c\
					srcs/parsing/ms_prompt_handler.c\
					srcs/parsing/ms_prompt_heredocs.c\
					srcs/parsing/ms_prompt_splitter.c\
					srcs/parsing/ms_tab_to_tokken.c\
					srcs/parsing/ms_tokken_cleaner.c\
					srcs/prefix/prefix.c\
					srcs/prefix/prefix_rgb.c\
					srcs/utils/double_close.c\
					srcs/utils/env_export.c\
					srcs/utils/env_to_lst.c\
					srcs/utils/env_to_tab.c\
					srcs/utils/ft_atoll.c\
					srcs/utils/ft_is_ll.c\
					srcs/utils/ft_is_only_quote.c\
					srcs/utils/ft_split_space.c\
					srcs/utils/ft_str_is_num.c\
					srcs/utils/ft_str_is_space.c\
					srcs/utils/ft_strjointab.c\
					srcs/utils/ft_strncat.c\
					srcs/utils/ft_tabstr_len.c\
					srcs/utils/get_env.c\
					srcs/utils/get_env_lst.c\
					srcs/utils/get_env_var.c\
					srcs/utils/is_builtin.c\
					srcs/utils/ms_args_split.c\
					srcs/utils/ms_ft_strncmp.c\
					srcs/utils/ms_tokken_printer.c\
					srcs/utils/pars_injector.c\
					srcs/utils/print_tab.c\
					srcs/utils/str_unquote.c\
					srcs/utils/countwords.c

CFLAGS			=	-Wall -Werror -Wextra -Iheaders -lreadline -g

LIBFT_PATH		=	./submodules/42.libft
LIBFT			=	$(LIBFT_PATH)/libft.a

all:	hello $(NAME)

hello:
	@echo "\e[48;2;100;0;100;1m Welcome to "$(NAME)" Makefile !\e[0m\n"

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

re:
	+make fclean
	+make all

.PHONY: all clean fclean re
