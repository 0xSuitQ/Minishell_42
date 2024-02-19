/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:09:30 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/19 11:09:45 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*token_to_str(t_lexer *token)
{
	int						i;
	static t_token_matrix	tokens[] = {
	{"|", PIPE},
	{"<", LESS}, {"<<", LESS_LESS},
	{">", GREAT}, {">>", GREAT_GREAT}
	};

	i = -1;
	while (++i < TOKEN_NUM)
		if (token && token->token == tokens[i].type)
			return (tokens[i].str_sym);
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

t_lexer	*append_redirection(t_simple_cmd **cmd, t_lexer *arg)
{
	t_lexer	*new_arg;
	t_lexer	*last;
	
	new_arg = malloc(sizeof(t_lexer));
	if (!new_arg)
		return (NULL);
	*new_arg = *arg;
	new_arg->next = NULL;
	new_arg->prev = NULL;
	if (!(*cmd)->lexer_list)
		(*cmd)->lexer_list = new_arg;
	else
	{
		last = get_last_node((*cmd)->lexer_list);
		last->next = new_arg;
		new_arg->prev = last;
	}
	new_arg->flag = INVISIBLE;
	return (new_arg);
}

void	first_node_not_pipe(t_lexer *lex_head)
{
	if (lex_head->token == PIPE)
		ft_putstr_fd_exit("syntax error near unexpected token `|'\n",
		STDOUT, 0);
} // check for consecutive pipes '| |'

void	validate_and_append_redirection(t_simple_cmd **cmd, t_lexer ***current_lexer)
{
	t_lexer	*the_arg;
	t_lexer	*next_arg;

	if (!(**current_lexer) || !(*cmd))
		return ;
	the_arg = **current_lexer;
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
	the_arg = append_redirection(cmd, the_arg);
	if (next_arg)
	{
		next_arg = append_redirection(cmd, next_arg);
		**current_lexer = next_arg; // Move lexer pointer forward
		// arent we moving the pointer twice? OR isnt it unnecessary?
	}
}

static void	init_first_scmd(t_simple_cmd ***list, t_simple_cmd *new_node)
{
	**list = new_node;
	(**list)->prev = NULL;
}

t_simple_cmd	*get_last_cmd_node(t_simple_cmd ***lexer_list)
{
	if ((**lexer_list) == NULL)
		return (NULL);
	while ((**lexer_list)->next)
		**lexer_list = (**lexer_list)->next;
	return ((**lexer_list));
}

static void	connect_node_to_list(t_simple_cmd ***list, t_simple_cmd **new_node)
{
	(*new_node)->prev = get_last_cmd_node(list);
	(**list)->next = *new_node;
	(*new_node)->next = NULL;
}

void	init_simple_cmd(t_simple_cmd **s_cmd_list, t_lexer *lexer_list)
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
		init_first_scmd(&s_cmd_list, new_node);
	else
		connect_node_to_list(&s_cmd_list, &new_node);
	new_node->lexer_list = NULL;
	new_node->next = NULL;
}

void	check_pipes(t_simple_cmd **cmd, t_lexer *lexer_list)
{
	while(lexer_list)
	{
		if (lexer_list->token == PIPE)
			init_simple_cmd(cmd, lexer_list->next); // Not to start counting from pipe
		lexer_list = lexer_list->next;
	}
}

void	check_redirection(t_simple_cmd **cmd, t_lexer **lexer_list)
{
	while (*lexer_list)
	{
		if ((*lexer_list)->token && (*lexer_list)->token != PIPE)
			validate_and_append_redirection(cmd, &lexer_list);
		else if ((*lexer_list)->token == PIPE)
			*cmd = (*cmd)->next;
		*lexer_list = (*lexer_list)->next;
	}
}

void	check_cmds(t_simple_cmd **cmd, t_lexer *lexer_list)
{
	t_simple_cmd *head;
	int i;

	head = *cmd;
	i = -1;
	while (lexer_list)
	{
		if (lexer_list->token == PIPE)
		{
			(*cmd)->str[i] = NULL;
			*cmd = (*cmd)->next;
			printf("cmd pointer: %p\n", *cmd); // delete
			i = -1;
		}
		else if (lexer_list->flag == INVISIBLE)
			lexer_list = lexer_list->next;
		(*cmd)->str[++i] = ft_strdup(lexer_list->sub_str);
		lexer_list = lexer_list->next;
	}
	if (i == -1)
		i++;
	(*cmd)->str[i] = NULL;
	
	*cmd = head;
	int j;
	while (*cmd)
	{
		j = 0;
		while((*cmd)->str[j])
			printf("%s ", (*cmd)->str[j++]);
		printf("\n");
		*cmd = (*cmd)->next;
	}
	*cmd = head;
}

void check_redirections_tokens(t_simple_cmd *cmd) 
{
	while (cmd != NULL)
	{
		while (cmd->lexer_list != NULL)
		{
			printf("Redirection token: %s\n", cmd->lexer_list->sub_str);
			cmd->lexer_list = cmd->lexer_list->next;
		}
		cmd = cmd->next;
	}
}

void print_simple_cmds(t_simple_cmd *cmd)
{
	t_simple_cmd *head = cmd;

	write(1, "\n", 1);
	while (cmd != NULL)
	{
		int i = -1;
		while (cmd->str[++i] != NULL)
			printf("%s ", cmd->str[i]);
		cmd = cmd->next;
	}
	write(1, "\n", 1);
	check_redirections_tokens(head);
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
	first_node_not_pipe(lex_head);
	init_simple_cmd(&s_cmd_list, lexer_list);
	scmd_head = s_cmd_list;
	check_pipes(&s_cmd_list, lexer_list);
	s_cmd_list = scmd_head;
	check_redirection(&s_cmd_list, &lexer_list);
	s_cmd_list = scmd_head;
	lexer_list = lex_head;
	check_cmds(&s_cmd_list, lexer_list);
	/*
	lexer_list = lex_head;
	s_cmd_list = scmd_head;
	// FREE T_LEXER LIST
	s_cmd_list = scmd_head;
	print_simple_cmds(s_cmd_list);
	*/
	// int count = 0;
	// while (s_cmd_list)
	// {
	// 	count++;
	// 	s_cmd_list = s_cmd_list->next;
	// }
	// printf("count: %d\n", count);
	// print the simple commands
	// s_cmd_list = scmd_head;
}
