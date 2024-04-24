/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:03:55 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/24 16:37:41 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// ZAKOMENTOVAT
void tester(t_main_tools *tools, int signpost);

/**
	@brief:
	append_redirection function appends the redirection to the lexer_list.
*/
t_lexer	*append_redirection(t_simple_cmd **cmd, t_lexer *arg)
{
	t_lexer	*new_arg;
	t_lexer	*last;

	new_arg = malloc(sizeof(t_lexer));
	if (!new_arg)
		return (NULL);
	arg->flag = INVISIBLE;
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

/**
	@brief:
	If the next_arg dosn't exist || isn't a word, it Print&Error the
	program. If the redirection is a '<' and the file does not exist, it
	Print&Error. Otherwise, it appends the redirection to the lexer_list.
*/
int	validate_redirection(t_simple_cmd **cmd, t_lexer **current_lexer, t_main_tools *tools)
{
	t_lexer	*the_arg;
	t_lexer	*next_arg;

	if (!(*current_lexer) || !(*cmd))
		return (EXIT_FAILURE);
	the_arg = *current_lexer;
	next_arg = the_arg->next;

	if ((!next_arg || next_arg->token != 0) && the_arg)
	{
		unexpected_token_officer(next_arg, tools);
		return (EXIT_FAILURE);
	}
	if (the_arg->token == LESS)
	{
		if (access(next_arg->sub_str, F_OK) == -1)
		{
			ft_putstr_fd("no such file or directory:", STDERR_FILENO);
			ft_putstr_fd(next_arg->sub_str, STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			error_police(2, tools);
		}
	}
	the_arg = append_redirection(cmd, the_arg);
	if (next_arg)
	{
		next_arg = append_redirection(cmd, next_arg);
		if ((*current_lexer)->next->next)
			*current_lexer = (*current_lexer)->next->next;
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
	@brief:
	if the token is a redirection, it calls the append_redirection function
	if the token is a pipe, it moves to the next node of the simple_cmd list
	if the token is anything else (word), it moves to the next node of the
	list of lexer_list
*/
void	redirection_pipe_word(t_simple_cmd **cmd, t_lexer *lexer_list, t_main_tools *tools)
{
	t_lexer *tmp;

	tmp = lexer_list;
	while (tmp)
	{
		if (tmp->token && tmp->token != PIPE)
			validate_redirection(cmd, &tmp, tools);
		if (tmp->token == PIPE)
		{
			if (!tmp->next || tmp->next->token == PIPE)
				unexpected_token_officer(tmp, tools);
			*cmd = (*cmd)->next;
		}
		tmp = tmp->next;
	}
}

/**
	@brief:
	simple function count_args function counts the number of arguments in
	the lexer_list. It is used to allocate the right amount of memory in the
	init_simple_cmd function. It ends when it reaches the end of the list or
	when it encounters a pipe.
*/
int	count_args(t_lexer *lexer_list)
{
	int	counter;

	counter = 0;
	while (lexer_list && lexer_list->token != PIPE)
	{
		if (lexer_list->index >= 0)
			counter++;
		lexer_list = lexer_list->next;
	}
	return (counter);
}

/**
	@brief:
	get_last_cmd_node function returns the last node of the list of
	simple_cmd structures. It uses tmp variable to go through the list without
	changing the head of the list in the functions that call it.
*/
t_simple_cmd	*get_last_cmd_node(t_simple_cmd **lexer_list)
{
	t_simple_cmd *tmp;

	tmp = *lexer_list;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

/**
	@brief:
	init_first_scmd function initializes the first node of the list of
	simple_cmd structures.
*/
void	init_first_scmd(t_simple_cmd **list, t_simple_cmd *new_node)
{
	*list = new_node;
	(*list)->prev = NULL;
}

/**
	@brief:
	connect_node_to_list function connects the new_node to the list of
	simple_cmd structures.
*/
void	connect_node_to_list(t_simple_cmd **list, t_simple_cmd *new_node)
{
	new_node->prev = get_last_cmd_node(list);
	new_node->prev->next = new_node;
}

/**
	@brief:
	init_one_simple_cmd function initializes the simple_cmd structure. It
	allocates memory for the str member and sets the next and lexer_list
	members to NULL.
	'new_node' is a structure that is added to the list of simple_cmd
	structures. This list is used to store the simple commands that are
	separeted by pipes.
*/
void	init_one_simple_cmd(t_simple_cmd **cmd_list, t_lexer *lexer_list, t_main_tools *tools)
{
	t_simple_cmd	*new_node;
	int i;

	i = 0;
	new_node = malloc(sizeof(t_simple_cmd));
	if (!new_node)
		return ;
	new_node->arg_count = count_args(lexer_list);
	new_node->str = malloc((new_node->arg_count + 1) * sizeof(char *));
	if (!new_node->str)
	{
		free(new_node);
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
		error_police(2, tools);
	}
	while (i <= new_node->arg_count)
	{
		new_node->str[i] = NULL;
		i++;
	}
	if (*cmd_list == NULL)
		init_first_scmd(cmd_list, new_node);
	else
		connect_node_to_list(cmd_list, new_node);
	new_node->lexer_list = NULL;
	new_node->next = NULL;
	new_node->heredoc_filename = NULL;
	new_node->builtin = NULL;
}

/**
	@brief:
	init_simple_cmds function initializes the list of simple_cmd structures.
	It goes through the lexer_list and calls the init_one_simple_cmd
	function every time it encounters a pipe.
*/
void	init_simple_cmds(t_simple_cmd **cmd_list, t_lexer *lexer_list, t_main_tools *tools)
{
	t_lexer	*tmp;

	tmp = lexer_list;
	if (tmp)
		init_one_simple_cmd(cmd_list, tmp, tools);
	while (tmp)
	{
		if (tmp->token == PIPE && tmp->next)
			init_one_simple_cmd(cmd_list, tmp->next, tools);
		tmp = tmp->next;
	}
}

/**
	@brief:
	first_node_not_pipe function checks if the first node is a pipe. If it
	is, it prints an error message and exits the program.
*/
void	first_node_not_pipe(t_lexer *lex_head, t_main_tools *tools)
{
	if (!lex_head)
		return ;
	if (lex_head->token == PIPE)
		unexpected_token_officer(lex_head, tools);
}

/**
	@brief:
	parser function is the main function that calls all the other functions
*/
void	check_cmds(t_simple_cmd **cmd, t_lexer *lexer_list)
{
	int		i;
	t_lexer	*tmp;

	tmp = lexer_list;
	i = 0;
	while (tmp)
	{
		if ((tmp)->token == PIPE) 
		{
			*cmd = (*cmd)->next;
			tmp = tmp->next;
			i = 0;
		} 
		else if (tmp->flag == 0)
			tmp = tmp->next;
		else
		{
			(*cmd)->str[i++] = ft_strdup(tmp->sub_str);
			tmp = tmp->next;
		}
	}
	(*cmd)->str[i] = NULL;
}

/**
	@brief:
	count_pipes function counts the number of pipes in the lexer_list. And
	returns the number (count) of pipes.
*/
int	count_pipes(t_lexer *lexer_list)
{
	int		count;
	t_lexer	*tmp;

	count = 0;
	tmp = lexer_list;
	while (tmp)
	{
		if (tmp->token == PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

/**
	@brief:
	builtin_arr function is a 2D array of strings and function pointers
	It compares the string with the builtins and returns the function pointer
	of the builtin command.
*/
int	(*builtin_arr(char *str))(t_main_tools *tools, t_simple_cmd *cmd)
{
	int			i;
	static void *builtins[7][2] = {
		{"echo", msh_echo}, {"cd", msh_cd},
		{"pwd", msh_pwd}, {"export", msh_export},
		{"unset", msh_pwd}, {"env", msh_env},
		{"exit", msh_exit}};

	i = 0;
	while (i < 7)
	{
		if (str)
		{
			if (!ft_strncmp(builtins[i][0], str, ft_strlen((builtins[i][0]))))
			return (builtins[i][1]);
		}
		i++;
	}
	return (NULL);
}

/**
	@brief:
	fill_builtin function fills the builtin member in the simple_cmd structure
	with the right function pointer.
*/
void	fill_builtin(t_simple_cmd **cmd)
{
	t_simple_cmd *tmp;

	tmp = *cmd;
	while (tmp)
	{
		tmp->builtin = builtin_arr(tmp->str[0]);
		tmp = tmp->next;
	}
}

/**
	@brief:
	parser function is the main function that calls all the other functions.
	It handles the parsing of the lexer list & converts it into more structured
	representation = into a list of simple commands (simple_cmds).
*/
void	parser(t_main_tools *tools)
{
	t_lexer			*lexer_list;
	t_simple_cmd	*s_cmd_list;

	lexer_list = tools->lexer_list;
	s_cmd_list = tools->simple_cmd_list;
	first_node_not_pipe(lexer_list, tools);
	init_simple_cmds(&s_cmd_list, lexer_list, tools);
	tools->simple_cmd_list = s_cmd_list;
	redirection_pipe_word(&s_cmd_list, lexer_list, tools);
	s_cmd_list = tools->simple_cmd_list;
	check_cmds(&s_cmd_list, lexer_list);
	s_cmd_list = tools->simple_cmd_list;
	tools->pipes = count_pipes(lexer_list);
	fill_builtin(&s_cmd_list);
}
