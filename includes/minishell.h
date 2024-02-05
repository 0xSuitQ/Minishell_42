#ifndef MINISHELL_H
# define MINISHELL_H

/******************** iMport **********************/
# include <stdio.h>
# include <stdlib.h>

/******************** LEXER **********************/
typedef enum s_token_list
{
	PIPE,
	LESS,
	LESS_LESS,
	GREAT,
	GREAT_GREAT,
}	t_token_list;

typedef struct s_token_matrix
{
    char			*str_symbol;
    t_token_list	type;
}	t_token_matrix;

typedef struct s_lexer
{
	char			*sub_str;
	int				index;
	t_token_list	token;
	struct s_lexer	*next;
	struct s_lexer	*prev;	
}	t_lexer;

/******************** PARSER **********************/

/******************** UTILS **********************/
char	*str_sepdup(char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *src);

/******************** COLORS **********************/
# define RESET_COLOR	"\033[0m"
# define RED     		"\033[31m"
# define GREEN   		"\033[32m"
# define BLUE    		"\033[34m"

/******************** MACROS **********************/
# define TOKEN_NUM		5
# define WELCOME_MSG	"\033[96m╔════════════════════════════════════════════════════════════════════════════════╗\n║                                                                                ║\n║                  \033[95m█▀█ █▀▀ █▀▀   █▀█ █▀█ █▀▀ █▀ █▀▀ █▄░█ ▀█▀ █▀                  \033[96m║\n║                  \033[95m█▀▀ █▀░ █▄▄   █▀▀ █▀▄ ██▄ ▄█ ██▄ █░▀█ ░█░ ▄█                  \033[96m║\n║                                                                                ║\n║      \033[35m ███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░       \033[96m║\n║      \033[35m ████╗░████║██║████╗░██║██║██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░       \033[96m║\n║     \033[35m  ██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░       \033[96m║\n║     \033[35m  ██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░       \033[96m║\n║     \033[35m  ██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗       \033[96m║\n║      \033[35m ╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝       \033[96m║\n║                                                                                ║\n╚════════════════════════════════════════════════════════════════════════════════╝"
# define HEREDOC_MSG	"\033[1;34m> \033[0m"
# define READLINE_MSG	"\033[1;36mminishell\033[34m$ \033[0m"

#endif 
