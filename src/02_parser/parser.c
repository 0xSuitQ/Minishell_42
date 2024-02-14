/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:09:30 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/14 20:54:41 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*token_to_str(t_lexer *token)
{
	static int				i = -1;
	static t_token_matrix	tokens[] = {
	{"|", PIPE},
	{"<", LESS}, {"<<", LESS_LESS},
	{">", GREAT}, {">>", GREAT_GREAT}
	};

	while (++i < TOKEN_NUM)
	{
		if (token->token == tokens[i].type)
			return (tokens[i].str_sym);
	}
	return ("newline"); // if !token
}

int	count_args(t_lexer *lexer_list)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = lexer_list;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->index >= 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	append_redirection(t_simple_cmd **cmd, t_lexer *redirection)
{
	t_lexer	*new_redirection;
	t_lexer	*last;
	
	new_redirection = malloc(sizeof(t_lexer));
	if (!new_redirection)
		return ;
	*new_redirection = *redirection;
	new_redirection->next = NULL;
	new_redirection->prev = NULL;
	if (!(*cmd)->redirections)
		(*cmd)->redirections = new_redirection;
	else
	{
		last = get_last_node((*cmd)->redirections);
		last->next = new_redirection;
		new_redirection->prev = last;
	}
	new_redirection->flag = INVISIBLE;
}

void	first_node_not_pipe(t_lexer *lex_head)
{
	if (lex_head->token == PIPE)
	{
		ft_putstr_fd_exit("syntax error near unexpected token `|'\n",
		STDOUT, 0);
	}
} // check for consecutive pipes '| |'

void	validate_and_append_redirection(t_simple_cmd **cmd, t_lexer **current_lexer)
{
	t_lexer	*the_arg;
	t_lexer	*next_arg;

	if (!(*current_lexer) || !(*cmd))
		return ;
	the_arg = *current_lexer;
	next_arg = the_arg->next;

	if ((!next_arg || next_arg->token != 0) && the_arg)
	{
		ft_printf("syntax error near unexpected token `%s'", token_to_str(next_arg));
		ft_putstr_fd_exit("\n", STDOUT, 0);
	}
	if (the_arg->token == LESS)
	{
		if (access(next_arg->sub_str, F_OK) == -1)
		{
			ft_printf("no such file or directory: %s\\n", next_arg->sub_str);
			return; // Exit on error for non-existing file
		}
	}
	append_redirection(cmd, the_arg);
	if (next_arg)
	{
		append_redirection(cmd, next_arg);
		*current_lexer = next_arg; // Move lexer pointer forward
		// arent we moving the pointer twice? OR isnt it unnecessary?
	}
}

static void	create_first_scmd(t_simple_cmd ***list, t_simple_cmd *new_node)
{
	**list = new_node;
	(**list)->prev = NULL;
}

t_simple_cmd	*get_last_cmd_node(t_simple_cmd *list_head)
{
	if (list_head == NULL)
		return (NULL);
	while (list_head->next)
		list_head = list_head->next;
	return (list_head);
}

static void	connect_node_to_list(t_simple_cmd ***list, t_simple_cmd **new_node)
{
	(*new_node)->prev = get_last_cmd_node(**list);
	(**list)->next = *new_node;
	(*new_node)->next = NULL;
}

void	create_simple_cmd(t_simple_cmd **s_cmd_list, t_lexer *lexer_list)
{
	t_simple_cmd	*new_node;
	int				arg_size;

	arg_size = count_args(lexer_list);
	new_node = malloc(sizeof(t_simple_cmd));
	if (!new_node)
		return ;
	new_node->str = malloc((arg_size + 1) * sizeof(char *));
	if (!new_node->str)
	{
		free(new_node);
		return ;
	}
	if (*s_cmd_list == NULL)
		create_first_scmd(&s_cmd_list, new_node);
	else
		connect_node_to_list(&s_cmd_list, &new_node);
	//new_node->str[0] = strdup("");
	// if (!simple_cmds->str[0]) 
	// {
	// 	free(simple_cmds->str);
	// 	free(simple_cmds);
  	// 	return ;
	// }
	new_node->redirections = NULL;
	new_node->next = NULL;
}

void	check_pipes(t_simple_cmd **cmd, t_lexer *current_lexer)
{
	while(current_lexer)
	{
		if (current_lexer->token == PIPE)
			create_simple_cmd(cmd, current_lexer->next); // Not to start counting from pipe
		current_lexer = current_lexer->next;
	}
}

void	check_redirection(t_simple_cmd **cmd, t_lexer *current_lexer)
{
	while (current_lexer)
	{
		if (current_lexer->token && current_lexer->token != PIPE)
			validate_and_append_redirection(cmd, &current_lexer);
		else if (current_lexer->token == PIPE)
			*cmd = (*cmd)->next;
		current_lexer = current_lexer->next;
	}
}

void	check_cmds(t_simple_cmd **cmd, t_lexer **current_lexer)
{
	int i;

	i = 0;
	while (*current_lexer)
	{
		if ((*current_lexer)->token == PIPE)
		{
			*cmd = (*cmd)->next;
			i = 0;
		}
		else if ((*current_lexer)->flag == INVISIBLE)
			*current_lexer = (*current_lexer)->next;
		(*cmd)->str[i++] = ft_strdup((*current_lexer)->sub_str);
		*current_lexer = (*current_lexer)->next;
	}
	(*cmd)->str[i] = NULL;
}

void	parser(t_main_tools *tools)
{
	t_lexer			*lexer_list;
	t_simple_cmd	*s_cmd_list;
	t_lexer			*lex_head;
	t_simple_cmd 	*scmd_head;

	lexer_list = tools->lexer_list;
	s_cmd_list = tools->simple_cmd_list;
	lex_head = lexer_list;
	scmd_head = s_cmd_list;
	first_node_not_pipe(lex_head);
	create_simple_cmd(&s_cmd_list, lexer_list);
	check_pipes(&s_cmd_list, lexer_list);
	lexer_list = lex_head;
	s_cmd_list = scmd_head;
	check_redirection(&s_cmd_list, lexer_list);
	lexer_list = lex_head;
	s_cmd_list = scmd_head;
	check_cmds(&s_cmd_list, &lexer_list);
	// FREE T_LEXER LIST
}


/*void	parser(t_lexer *lexer_list)
{
	static int		i = 0;
	t_simple_cmd	*simple_cmds;

	simple_cmds = malloc(sizeof(t_simple_cmd));
	simple_cmds->str = ft_strdup(""); // TODO FREE
	simple_cmds->next = NULL;
	simple_cmds->prev = NULL;
	simple_cmds->redirections = NULL;
	t_simple_cmd *head = simple_cmds;
	// TODO builtin
	while (lexer_list)
	{
		if (lexer_list->token != PIPE && lexer_list->token != 0)
			token_case(simple_cmds, lexer_list);
		else if (lexer_list->token == 0)
			substr_case(simple_cmds, lexer_list);
		if (lexer_list->token == PIPE)
		{
			simple_cmds->next = malloc(sizeof(t_simple_cmd));
			simple_cmds->next->prev = simple_cmds;
			simple_cmds = simple_cmds->next;
			simple_cmds->str = ft_strdup("");
			simple_cmds->next = NULL;
			simple_cmds->redirections = NULL;
		}
		lexer_list = lexer_list->next;
	}
}*/