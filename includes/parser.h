#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

typedef enum s_token
{
	PIPE,
	LESS,
	LESS_LESS,
	GREAT,
	GREAT_GREAT,
}	t_token;

typedef struct s_lexer
{
	char	*str;
	int		i;
	t_token	token;
	struct	s_lexer	*next;
	struct	s_lexer	*prev;	
}	t_lexer;

#endif
