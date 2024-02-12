#include "../includes/minishell.h"

void	tester(t_lexer	*lexer_list)
{
	while (lexer_list)
	{
		printf("str of the lexer list number\t %d: %s\n", lexer_list->index, lexer_list->sub_str);
		printf("token of the lexer list number\t %d: %d\n", lexer_list->index, lexer_list->token);
		printf("------------------\n");
		lexer_list = lexer_list->next;
	}
}
