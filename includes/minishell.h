/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:56:54 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 19:15:35 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************** iMport **********************/
# include <unistd.h>
# include <complex.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>	
# include <stdlib.h>
# include <sys/wait.h>

/*
# include <unistd.h>			// write
# include <complex.h>			// For complex numbers
# include <fcntl.h>				// open, close
# include <readline/history.h>	// functions related w/ readline
# include <readline/readline.h>	// functions related w/ readline
# include <signal.h>			// signal
# include <stdarg.h>			//
# include <stddef.h>			//
# include <stdio.h>				// printf, perror
# include <stdlib.h>			// malloc, free, exit, getenv, EXIT_FAILURE, ...
# include <sys/wait.h>			// waitpid
*/

# define BLUE			"\033[1;34m"
# define CYAN			"\033[1;36m"
# define RESET			"\033[0m"
/********* DECLARATION OF GLOBAL VARIABLE *********/
// declare it in .h file allow us to use it anywhere where we include msh.h
// extern = this exists
extern int					g_signal;

/******************* STRUCTS *********************/
typedef struct s_main_tools	t_main_tools;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/******************* EXECUTOR ********************/
typedef struct s_expander
{
	char			*first;
	char			*second;
	char			*tmp_1;
	char			*tmp_2;
	char			*final;
	t_list			*exp_list;
	int				i;
}	t_expander;

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
	int				flag;
	t_token_list	token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

/******************** PARSER **********************/
typedef struct s_simple_cmd
{
	char				**str;
	int					arg_count;
	t_lexer				*lexer_list;
	char				*heredoc_filename;
	struct s_simple_cmd	*next;
	struct s_simple_cmd	*prev;
	int					(*builtin)(struct s_main_tools *,
			struct s_simple_cmd *);
}	t_simple_cmd;

/********* THE SUPERIOR, CENTRAL STRUCTS **********/
typedef struct s_env
{
	char			*name;
	char			*value;
	char			*full_string;
	struct s_env	*next;
}	t_env;

typedef struct s_main_tools
{
	t_lexer			*lexer_list;
	t_simple_cmd	*simple_cmd_list;
	char			**envp_cpy;
	char			**paths;
	char			*args;
	char			*pwd;
	char			*old_pwd;
	int				*pid;
	int				pipes;
	int				finished;
	int				error_type;
	int				exit_status;
}	t_main_tools;

/******************* PROTOTYPES *******************/
//	MAIN
int				minishell_loop(t_main_tools *tools);
void			exit_minishell(t_main_tools *tools, int exit_num);

//	LEXER
int				lexer(t_main_tools *tools);
t_token_list	check_token(int c);
int				handle_quotes(int i, char *str, char del);
int				is_whitespace(char c);
int				skip_spaces(char *str, int i);
int				add_node(char *str, t_token_list token, t_lexer **lexer_list);

//	PARSER
void			parser(t_main_tools *tools);
void			unexpected_token_officer(t_lexer *head, t_main_tools *tools);
void			connect_node_to_list(t_simple_cmd **list, t_simple_cmd *nn);
int				count_pipes(t_lexer *lexer_list);
int				count_args(t_lexer *lexer_list);
t_simple_cmd	*get_last_cmd_node(t_simple_cmd **lexer_list);
void			first_node_not_pipe(t_lexer *lex_head, t_main_tools *tools);
void			init_first_scmd(t_simple_cmd **list, t_simple_cmd *new_node);
void			isc(t_simple_cmd **cl, t_lexer *ll, t_main_tools *t);
void			r_p_word(t_simple_cmd **cmd, t_lexer *ll, t_main_tools *t);
int				val_red(t_simple_cmd **cmd, t_lexer **cl, t_main_tools *t);
void			i_cmd(t_simple_cmd **cmd_list, t_lexer *ll, t_main_tools *t);
t_lexer			*append_redirection(t_simple_cmd **cmd, t_lexer *arg);
void			check_cmds(t_simple_cmd **cmd, t_lexer *lexer_list);

//	HEREDOC
int				heredoc(t_main_tools *tools, t_simple_cmd *cmd);
char			*delete_quotes(char *str, char c);

//	EXECUTOR
int				executor(t_main_tools *tools);
int				read_from(t_simple_cmd *cmd, t_lexer *tmp, t_token_list r);
int				write_to(t_lexer *tmp, t_token_list redirection);
int				check_builtin(t_main_tools *tools, t_simple_cmd *cmd);
void			prepare_exec(t_main_tools *tools, t_simple_cmd *cmd);
int				forking(t_main_tools *t, t_simple_cmd *cmd, int fd[2], int f);

//	EXPANDER
void			expander(t_simple_cmd *curr_simple_cmd);
void			remove_quotes(char *str, char quote_type);
int				there_is_single_quote(char *str);
char			*clear_env_variable(char *str);
int				quotes_classifier(char *str);
int				env_not_valid(char *str);
int				there_is_dollar_in_str(char *str);
int				there_is_dollar_in_list(char **list);
int				num_of_dollars_in_list(char **str);
int				next_dollar(char *str);
int				first_char_not_dollar(char *str);
void			exp_to_default(t_expander *exp);

//	LIBFT
void			*ft_calloc(size_t nmemb, size_t size);
void			ft_putstr_fd(char *s, int fd);
char			*ft_itoa(int n);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *str);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
void			ft_strcpy(char *dest, char *src);
unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *str, int character);
char			*ft_strrchr(const char *str, int character);
int				ft_atoi(const char *nptr);
int				ft_isdigit(int c);
void			ft_putendl_fd(char *s, int fd);
void			ft_lstadd_back(t_list **lst, t_list *new);
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);

// PRINTF
int				ft_printf(const char *format, ...);
void			ft_putchar_and_strlen(char c, int *count);
void			ft_num_to_str(int num, int *count);
void			ft_putstr(char *str, int *count);
void			ft_u_int_to_str(unsigned int u, int *count);
void			ft_int_to_hex(char specifier, unsigned int uint_num, int *c);
void			ft_pointer(unsigned long u_int_num, int *count);

// REST OF LIBMS
void			create_list(t_lexer **list, int i, t_token_list tok, char *s);
t_lexer			*get_last_node(t_lexer *list_head);
void			tools_to_default_setting(t_main_tools *tools);
char			*ft_str_sepdup(char *s);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strdup(const char *s1);
void			free_arr(char **split_arr);
void			ft_putstr_fd_exit(char *message, int fd_num, int exit_num);
int				substring_counter(char *str);
char			*ft_strtrim(char const *s1, char const *set);
void			set_pwd(t_main_tools *tools);
char			*ft_strstr(char *str, char *to_find);
void			ft_str_replace(char **str, char *result);
char			*list_to_array(t_list *list);
void			free_list(t_list *list);
void			set_pwd(t_main_tools *tools);
void			validate_history(char *args);

// ENV_MANAGEMENT
int				get_paths(t_main_tools *tools);
char			**ft_arrdup(char **src);
void			change_path(t_main_tools *tools);
int				parse_envp(t_main_tools *tools);

// BUILTINS
int				msh_echo(t_main_tools *tools, t_simple_cmd *cmd);
int				msh_pwd(t_main_tools *tools, t_simple_cmd *cmd);
int				msh_cd(t_main_tools *tools, t_simple_cmd *cmd);
int				msh_env(t_main_tools *tools, t_simple_cmd *cmd);
int				msh_exit(t_main_tools *tools, t_simple_cmd *cmd);
int				msh_unset(t_main_tools *tools, t_simple_cmd *cmd);
int				msh_export(t_main_tools *tools, t_simple_cmd *cmd);

// ERROR_MANAGEMENT
int				error_police(int err_code, t_main_tools *tools);
void			clear_for_continue(t_main_tools *tools);
void			clear_all(t_main_tools *tools);
void			memory_error(void *p, t_main_tools *t, int ec, t_simple_cmd *c);
void			file_error(t_lexer *next_arg, t_main_tools *tools);

// SIGNALS
int				signal_exit_of_child(int *status);
void			handle_sigint(int sig_num);
void			handle_sigint_when_child_running(int sig_num);
void			handle_sigint_heredoc(int sig_num);
void			reset_signals_default(void);
void			ctrl_d(void);

/******************** MACROS **********************/
# define STDIN			0
# define STDOUT			1
# define STDERR			2
# define EXIT_MALLOC	4

# define INVISIBLE		0
# define VISIBLE		1

# define LEXER_LIST		0
# define CMD_LIST		1

# define FALSE			0
# define TRUE			1

# define TOKEN_NUM		5
# define HEREDOC_MSG	"\033[1;34m> \033[0m"
# define READLINE_MSG	"\033[1;36mnikita&peta:msh\033[34m$ \033[0m"

# define NO_Q			0
# define SINGLE_Q		1
# define DOUBLE_Q		2

#endif
