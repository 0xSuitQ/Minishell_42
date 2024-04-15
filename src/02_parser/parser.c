/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:03:55 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/15 13:11:38 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// ZAKOMENTOVAT
void tester(t_main_tools *tools, int signpost);

/**
	@brief:
	token_to_str function returns the string representation of the token.
	It uses 2D array of strings and token_list enum to find the right string
	and macro to find the right token. If !token, it returns "newline".
*/
char	*token_to_str(t_lexer *token)
{
	int						i;
	static t_token_matrix	tokens[] = {{"|", PIPE},
									{"<", LESS},
									{"<<", LESS_LESS},
									{">", GREAT},
									{">>", GREAT_GREAT}};

	i = -1;
	while (++i < TOKEN_NUM)
	if (token && token->token == tokens[i].type)
		return (tokens[i].str_sym);
	return ("newline");
}

/*
	@brief:
	unexpected_token_officer is a member of the ERROR_POLICE. It prints an
	error message with the unexpected token and exits the program.
*/
void	unexpected_token_officer(t_lexer *head)
{
	ft_printf("syntax error near unexpected token `%s'",
		token_to_str(head)); // TODO
	ft_putstr_fd_exit("\n", STDOUT, 0);
}

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
int	validate_redirection(t_simple_cmd **cmd, t_lexer **current_lexer)
{
	t_lexer	*the_arg;
	t_lexer	*next_arg;

	if (!(*current_lexer) || !(*cmd))
		return (EXIT_FAILURE);
	the_arg = *current_lexer;
	next_arg = the_arg->next;

	if ((!next_arg || next_arg->token != 0) && the_arg)
	{
		unexpected_token_officer(next_arg);
		return (EXIT_FAILURE);
	}
	if (the_arg->token == LESS)
	{
		if (access(next_arg->sub_str, F_OK) == -1)
		{
			ft_putstr_fd("no such file or directory:", STDERR_FILENO);
			ft_putstr_fd(next_arg->sub_str, STDERR_FILENO); // TODO
			ft_putstr_fd("\n", STDERR_FILENO);
			return (EXIT_FAILURE); // Exit on error for non-existing file
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
void	redirection_pipe_word(t_simple_cmd **cmd, t_lexer *lexer_list)
{
	t_lexer *tmp;

	tmp = lexer_list;
	while (tmp)
	{
		if (tmp->token && tmp->token != PIPE)
			validate_redirection(cmd, &tmp);
		if (tmp->token == PIPE)
		{
			if (!tmp->next || tmp->next->token == PIPE)
				unexpected_token_officer(tmp);
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
void	init_one_simple_cmd(t_simple_cmd **cmd_list, t_lexer *lexer_list)
{
	t_simple_cmd	*new_node;

	new_node = malloc(sizeof(t_simple_cmd));
	if (!new_node)
		return;
	new_node->arg_count = count_args(lexer_list);
	new_node->str = malloc((new_node->arg_count + 1) * sizeof(char *));
	if (!new_node->str)
	{
		free(new_node); // TODO
		return;
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

/**
	@brief:
	first_node_not_pipe function checks if the first node is a pipe. If it
	is, it prints an error message and exits the program.
*/
void	first_node_not_pipe(t_lexer *lex_head)
{
	if (lex_head->token == PIPE)
		unexpected_token_officer(lex_head);
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
	// write(2, "we are in count_pipes\n", 23);
	while (tmp)
	{
		if (tmp->token == PIPE)
			count++;
		tmp = tmp->next;
	}
	// ft_printf("pipes in count_pipes: %d\n", count);
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
		{"pwd", msh_pwd}, {"export", msh_echo},
		{"unset", msh_echo}, {"env", msh_env},
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
	first_node_not_pipe(lexer_list);
	init_simple_cmds(&s_cmd_list, lexer_list);
	tools->simple_cmd_list = s_cmd_list;
	redirection_pipe_word(&s_cmd_list, lexer_list);
	s_cmd_list = tools->simple_cmd_list;
	check_cmds(&s_cmd_list, lexer_list);
	s_cmd_list = tools->simple_cmd_list;
	tools->pipes = count_pipes(lexer_list);
	fill_builtin(&s_cmd_list);
	// while (s_cmd_list) {
	//   if (s_cmd_list->builtin)
	//     printf("builtin: %p\n", (void*)s_cmd_list->builtin);
	//   s_cmd_list = s_cmd_list->next;
	// }
}
