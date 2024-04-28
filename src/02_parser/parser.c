/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:03:55 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 21:10:33 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	If the next_arg dosn't exist || isn't a word, it Print&Error the
	program. If the redirection is a '<' and the file does not exist, it
	Print&Error. Otherwise, it appends the redirection to the lexer_list.
*/

int	val_red(t_simple_cmd **cmd, t_lexer **current_lexer, t_main_tools *tools)
{
	t_lexer	*the_arg;
	t_lexer	*next_arg;

	if (!(*current_lexer) || !(*cmd))
		return (EXIT_FAILURE);
	the_arg = *current_lexer;
	next_arg = the_arg->next;
	if ((!next_arg || next_arg->token != 0) && the_arg)
		unexpected_token_officer(next_arg, tools);
	if (the_arg->token == LESS)
	{
		if (access(next_arg->sub_str, F_OK) == -1)
			file_error(next_arg, tools);
	}
	append_redirection(cmd, the_arg);
	if (next_arg)
	{
		append_redirection(cmd, next_arg);
		if ((*current_lexer)->next->next)
			*current_lexer = (*current_lexer)->next->next;
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
void	i_cmd(t_simple_cmd **cmd_list, t_lexer *lexer_list, t_main_tools *tools)
{
	t_simple_cmd	*new_node;
	int				i;

	i = 0;
	new_node = malloc(sizeof(t_simple_cmd));
	if (!new_node)
		return ;
	new_node->arg_count = count_args(lexer_list);
	new_node->str = malloc((new_node->arg_count + 1) * sizeof(char *));
	memory_error(new_node->str, tools, 2, new_node);
	while (i <= new_node->arg_count)
		new_node->str[i++] = NULL;
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
	builtin_arr function is a 2D array of strings and function pointers
	It compares the string with the builtins and returns the function pointer
	of the builtin command.
*/
int	(*builtin_arr(char *str))(t_main_tools *tools, t_simple_cmd *cmd)
{
	int				i;
	static void		*builtins[7][2] = {
	{"echo", msh_echo}, {"cd", msh_cd},
	{"pwd", msh_pwd}, {"export", msh_export},
	{"unset", msh_unset}, {"env", msh_env},
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
	t_simple_cmd	*tmp;

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
	isc(&s_cmd_list, lexer_list, tools);
	tools->simple_cmd_list = s_cmd_list;
	r_p_word(&s_cmd_list, lexer_list, tools);
	s_cmd_list = tools->simple_cmd_list;
	check_cmds(&s_cmd_list, lexer_list);
	s_cmd_list = tools->simple_cmd_list;
	tools->pipes = count_pipes(lexer_list);
	fill_builtin(&s_cmd_list);
}
