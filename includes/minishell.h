#ifndef MINISHELL_H
# define MINISHELL_H

/******************** iMport **********************/
# include <stdio.h>
# include <stdlib.h>
# include "lexer.h"
# include "utils.h"

/******************** LEXER **********************/

/******************** PARSER **********************/
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

/******************** UTILS **********************/
char	*str_sepdup(char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *src);

/******************** COLORS **********************/

#endif 
