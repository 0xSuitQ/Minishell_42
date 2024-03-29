NAME 	= minishell
FLAGS	= -Wall -Wextra -Werror -g

SRC 	= $(shell find ./src -iname "*.c")
OBJ 	= $(SRC:%.c=%.o)

%.o: %.c
		@cc $(FLAGS) -I includes -c $< -o $(<:.c=.o)

all: $(OBJ)
		@cc ${OBJ} -o ${NAME} -lreadline
		@echo "\033[32m----Minishell Compiled!----\e[0m"

clean:
		@rm -f $(OBJ)
		@echo "\033[31m----Deleting o-files!----\e[0m"

fclean: clean
		@rm -f $(NAME)
		@echo "\033[31m----Deleting o-files & minishell!----\e[0m"

re: 	fclean all

party:
		@curl parrot.live

.PHONY: all clean fclean re party