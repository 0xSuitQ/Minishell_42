/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:03:51 by nandroso          #+#    #+#             */
/*   Updated: 2024/04/28 19:13:08 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			(*cmd)->str[i] = ft_strdup(tmp->sub_str);
			tmp = tmp->next;
			i++;
		}
	}
	(*cmd)->str[i] = NULL;
}

void	file_error(t_lexer *next_arg, t_main_tools *tools)
{
	ft_putstr_fd("no such file or directory:", STDERR_FILENO);
	ft_putendl_fd(next_arg->sub_str, STDERR_FILENO);
	error_police(2, tools);
}
