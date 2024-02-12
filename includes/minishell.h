/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:56:54 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/12 09:44:13 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************** iMport **********************/
# include <stdio.h>				// printf, perror
# include <unistd.h>			// write
# include <stdarg.h>			// 
# include <stddef.h>			// 
# include <stdlib.h>			// malloc, free, exit, getenv
# include <signal.h>			// signal
# include <readline/readline.h> // functions related w/ readline
# include <readline/history.h>	// functions related w/ readline

/********* DECLARATION OF GLOBAL VARIABLE *********/
// declare it in .h file allow us to use it anywhere where we include msh.h
// extern = this exists
extern int	g_signal;

/******************** LEXER **********************/
typedef enum s_token_list
{
	PIPE = 1,
	LESS,
	LESS_LESS,
	GREAT,
	GREAT_GREAT,
}	t_token_list;

typedef struct s_token_matrix
{
	char			*str_sym;
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

typedef struct s_main_tools
{
	char	*envp;
}	t_main_tools;


/******************** PARSER **********************/
typedef struct s_simple_cmd
{
	char			*sub_str; // str of the command
	// command itself
	t_token_list	token;
	struct s_simple_cmd	*next;
	struct s_simple_cmd	*prev;
}	s_simple_cmd;

/******************** LIBMSH **********************/
// LIBFT
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_putstr_fd(char *s, int fd);
// PRINTF
int		ft_printf(const char *format, ...);
void	ft_putchar_and_strlen(char c, int *count);
void	ft_num_to_str(int num, int *count);
void	ft_putstr(char *str, int *count);
void	ft_u_int_to_str(unsigned int u, int *count);
void	ft_int_to_hex(char specifier, unsigned int uint_num, int *count);
void	ft_pointer(unsigned long u_int_num, int *count);
// ARRAY DUPLICATOR
char	**ft_arrdup(char **arr);
// LEXER
t_lexer	*lexer(char *input);
// ***** UTILS ***** //
char	*ft_str_sepdup(char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *src);
void	free_arr(char **split_arr);
void	ft_putstr_fd_exit(char *message, int fd_num, int exit_num);
// SUBSTRING COUNTER
int		substring_counter(char *str);
// CREATE_LIST
void	create_list(t_lexer **list, int index, t_token_list tok, char *sub_str);
// SIGNALS
// void	handle_sigint(int signum);

/******************** MACROS **********************/
# define STDIN			0
# define STDOUT			1
# define STDERR			2

# define TOKEN_NUM		5
# define HEREDOC_MSG	"\033[1;34m> \033[0m"
# define READLINE_MSG	"\033[1;36mminishell\033[34m$ \033[0m"

/******************** COLORS **********************/
# define RESET_COLOR	"\033[0m"
# define RED     		"\033[31m"
# define GREEN   		"\033[32m"
# define BLUE    		"\033[34m"

#endif
