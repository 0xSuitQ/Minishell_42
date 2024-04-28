/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:30:14 by nandroso          #+#    #+#             */
/*   Updated: 2024/04/28 15:30:17 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	token_to_str function returns the string representation of the token.
	It uses 2D array of strings and token_list enum to find the right string
	and macro to find the right token. If !token, it returns "newline".
*/
char	*token_to_str(t_lexer *token)
{
	int						i;
	static t_token_matrix	tokens[] = {
	{"|", PIPE},
	{"<", LESS},
	{">", GREAT},
	{"<<", LESS_LESS},
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
void	unexpected_token_officer(t_lexer *head, t_main_tools *tools)
{
	ft_printf("syntax error near unexpected token `%s'",
		token_to_str(head));
	ft_putstr_fd("\n", STDOUT);
	error_police(2, tools);
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
	init_simple_cmds function initializes the list of simple_cmd structures.
	It goes through the lexer_list and calls the init_one_simple_cmd
	function every time it encounters a pipe.
*/
void	isc(t_simple_cmd **cmd_list, t_lexer *lexer_list, t_main_tools *tools)
{
	t_lexer	*tmp;

	tmp = lexer_list;
	if (tmp)
		i_cmd(cmd_list, tmp, tools);
	while (tmp)
	{
		if (tmp->token == PIPE && tmp->next)
			i_cmd(cmd_list, tmp->next, tools);
		tmp = tmp->next;
	}
}

/**
	@brief:
	if the token is a redirection, it calls the append_redirection function
	if the token is a pipe, it moves to the next node of the simple_cmd list
	if the token is anything else (word), it moves to the next node of the
	list of lexer_list
*/
void	r_p_word(t_simple_cmd **cmd, t_lexer *lexer_list, t_main_tools *tools)
{
	t_lexer	*tmp;

	tmp = lexer_list;
	while (tmp)
	{
		if (tmp->token && tmp->token != PIPE)
			val_red(cmd, &tmp, tools);
		if (tmp->token == PIPE)
		{
			if (!tmp->next || tmp->next->token == PIPE)
				unexpected_token_officer(tmp, tools);
			*cmd = (*cmd)->next;
		}
		tmp = tmp->next;
	}
}
