#include "../includes/minishell.h"

void	tester(t_main_tools *tools)
{
	t_lexer			*lexer_list;
	t_simple_cmd	*simple_cmds;

	lexer_list = tools->lexer_list;
	simple_cmds = tools->simple_cmd_list;
	if (lexer_list)
		while (lexer_list)
		{
			printf("str of the lexer list number\t %d: %s\n", lexer_list->index, lexer_list->sub_str);
			printf("token of the lexer list number\t %d: %d\n", lexer_list->index, lexer_list->token);
			printf("------------------\n");
			lexer_list = lexer_list->next;
		}
	if (!simple_cmds)
		return ;
	while (simple_cmds->lexer_list)
	{
		printf("token: \t\t%i\nsub_str: \t%s\nflag: \t\t%d\n",\
		simple_cmds->lexer_list->token, simple_cmds->lexer_list->sub_str,\
		simple_cmds->lexer_list->flag);
		printf("------------------------\n");
		//printf("and next redirection in the list: %s---", simple_cmds->lexer_list->next->sub_str);
		simple_cmds->lexer_list = simple_cmds->lexer_list->next;
	}
}
