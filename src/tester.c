#include "../includes/minishell.h"

void	tester(t_main_tools *tools, int signpost)
{
	if (signpost == LEXER_LIST)
	{
		t_lexer			*lexer_list;
		t_simple_cmd	*simple_cmds;

		lexer_list = tools->lexer_list;
		simple_cmds = tools->simple_cmd_list;
		if (lexer_list)
		{
			while (lexer_list)
			{
				printf("str of the lexer list number\t %d: %s\n", 
				lexer_list->index, lexer_list->sub_str);
				printf("token of the lexer list number\t %d: %d\n", 
				lexer_list->index, lexer_list->token);
				printf("------------------\n");
				lexer_list = lexer_list->next;
			}
		}
	}

	if (signpost == CMD_LIST)
	{
		t_simple_cmd	*tmp2 = tools->simple_cmd_list;
		while(tmp2)
		{
			for (int i = 0; i < tmp2->arg_count; i++)
				printf("arg_count: %d\ttools->simple_cmd_list->str[%d]: %s\n",
				tmp2->arg_count, i, tmp2->str[i]);
			printf("------------------\n");
			tmp2 = tmp2->next;
		}

		t_lexer	*tmp = tools->lexer_list;
		while(tmp)
		{
			printf("l_l->flag: %d\t->sub_str: %s\n", tmp->flag, tmp->sub_str);
			tmp = tmp->next;
		}
	}
}
