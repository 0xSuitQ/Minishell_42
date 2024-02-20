/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:03:55 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/20 10:37:16 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void	tester(t_main_tools *tools, int signpost); // ZAKOMENTOVAT

/*

*/
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

/*

*/
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
	return (new_arg);
}

/*
	
*/
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
	// (*current_lexer)->flag = INVISIBLE;
	printf("**********\n");
	the_arg = append_redirection(cmd, the_arg);
	if (next_arg)
	{
		next_arg = append_redirection(cmd, next_arg);
		// (*current_lexer)->flag = INVISIBLE;
		printf("+++++++++++\n");
		*current_lexer = next_arg; // Move lexer pointer forward
		// arent we moving the pointer twice? OR isnt it unnecessary?
	}
}

/*
	@brief:
	if the token is a redirection, it calls the append_redirection function
	if the token is a pipe, it moves to the next node of the simple_cmd list
	if the token is anything else (word), it moves to the next node of the list
	of lexer_list
*/
void	check_redirection(t_simple_cmd **cmd, t_lexer *lexer_list)
{
	t_lexer	*tmp;

	tmp = lexer_list;
	while (tmp)
	{
		printf("tmp->token: %i tmp->sub_str: %s\n", tmp->token, tmp->sub_str);
		if (tmp->token && tmp->token != PIPE)
		{
			tmp->flag = INVISIBLE;
			// validate_and_append_redirection(cmd, &tmp);
		}
		if (tmp->token == PIPE)
			*cmd = (*cmd)->next;
		tmp = tmp->next;
	}
	printf("------------------\n");
}

/*
	@brief:
	simple function count_args function counts the number of arguments in the
	lexer_list. It is used to allocate the right amount of memory in the
	init_simple_cmd function. It ends when it reaches the end of the list or
	when it encounters a pipe.
*/
int	count_args(t_lexer *lexer_list)
{
	int		counter;

	counter = 0;
	while (lexer_list && lexer_list->token != PIPE)
	{
		if (lexer_list->index >= 0)
			counter++;
		lexer_list = lexer_list->next;
	}
	// printf("count_args output: %d\n", counter);
	return (counter);
}

/*
	@brief:
	get_last_cmd_node function returns the last node of the list of simple_cmd
	structures. It uses tmp variable to go through the list without changing
	the head of the list in the functions that call it.
*/
t_simple_cmd	*get_last_cmd_node(t_simple_cmd **lexer_list)
{
	t_simple_cmd	*tmp;

	tmp = *lexer_list;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

/*
	@brief:
	init_first_scmd function initializes the first node of the list of
	simple_cmd structures.
*/
void	init_first_scmd(t_simple_cmd **list, t_simple_cmd *new_node)
{
	*list = new_node;
	(*list)->prev = NULL;
}

/*
	@brief:
	connect_node_to_list function connects the new_node to the list of
	simple_cmd structures.
*/
void	connect_node_to_list(t_simple_cmd **list, t_simple_cmd *new_node)
{
	new_node->prev = get_last_cmd_node(list);
	new_node->prev->next = new_node;
}

/*
	@brief:
	init_one_simple_cmd function initializes the simple_cmd structure. It 
	allocates memory for the str member and sets the next and lexer_list
	members to NULL.
	
	'new_node' is a structure that is added to the list of simple_cmd
	structures. This list is used to store the simple commands that are
	separeted by pipes.
*/
void	init_one_simple_cmd(t_simple_cmd **cmd_list, t_lexer *lexer_list)
{
	t_simple_cmd	*new_node;
	int				i;

	new_node = malloc(sizeof(t_simple_cmd));
	if (!new_node)
		return ;
	new_node->arg_count = count_args(lexer_list);
	new_node->str = malloc((new_node->arg_count + 1) * sizeof(char *));
	if (!new_node->str)
	{
		free(new_node);
		return ;
	}
	i = -1;
	while (++i < new_node->arg_count)
		new_node->str[i] = NULL;
	i = -1;
	while (++i < new_node->arg_count)
	{
		new_node->str[i] = ft_strdup(lexer_list->sub_str);
		lexer_list = lexer_list->next;
	}
	if (*cmd_list == NULL)
		init_first_scmd(cmd_list, new_node);
	else
		connect_node_to_list(cmd_list, new_node);
	new_node->lexer_list = NULL;
	new_node->next = NULL;
}

/*
	@brief:
	init_simple_cmds function initializes the list of simple_cmd structures.
	It goes through the lexer_list and calls the init_one_simple_cmd function
	every time it encounters a pipe.
*/
void	init_simple_cmds(t_simple_cmd **cmd_list, t_lexer *lexer_list)
{
	t_lexer	*tmp;

	tmp = lexer_list;
	if (tmp)
		init_one_simple_cmd(cmd_list, tmp);
	while (tmp)
	{
		if (tmp->token == PIPE && tmp->next)
			init_one_simple_cmd(cmd_list, tmp->next);
		tmp = tmp->next;
	}
}

/*
	@brief:
	first_node_not_pipe function checks if the first node is a pipe. If it is,
	it prints an error message and exits the program.
*/
void	first_node_not_pipe(t_lexer *lex_head)
{
	if (lex_head->token == PIPE)
		ft_putstr_fd_exit("syntax error near unexpected token `|'\n",
		STDOUT, 0);
}

/*
	@brief:
	parser function is the main function that calls all the other functions
*/
void	parser(t_main_tools *tools)
{
	t_lexer			*lexer_list;
	t_simple_cmd	*s_cmd_list;

	lexer_list = tools->lexer_list;
	s_cmd_list = tools->simple_cmd_list;
	first_node_not_pipe(lexer_list);
	init_simple_cmds(&s_cmd_list, lexer_list);
	check_redirection(&s_cmd_list, lexer_list);
	tools->simple_cmd_list = s_cmd_list;
	tester(tools, CMD_LIST);
	
	// WIP:
	// check_cmds(&s_cmd_list, lexer_list);
}
