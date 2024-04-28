/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearing_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:17:27 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 19:15:35 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
    @brief:
    clear_lexer is a function that will clear all the allocated memory
    for the lexer_list
*/
void	clear_lexer(t_lexer *lexer_list)
{
	t_lexer	*current;
	t_lexer	*next;

	current = lexer_list;
	while (current)
	{
		next = current->next;
		free(current->sub_str);
		free(current);
		current = next;
	}
	lexer_list = NULL;
}

/**
    @brief:
    clear_simple_cmd is a function that will clear all the allocated memory
    for the simple_cmd_list
*/
void	clear_simple_cmd(t_main_tools *tools)
{
	t_simple_cmd	*current;
	t_simple_cmd	*next;

	current = tools->simple_cmd_list;
	while (current)
	{
		next = current->next;
		free_arr(current->str);
		if (current->heredoc_filename)
			free(current->heredoc_filename);
		free(current);
		current = next;
	}
	tools->simple_cmd_list = NULL;
}

/**
    @brief:
    clear_all is a function that will clear all the allocated memory
    and set the tools struct to the default settings.
    we use it if we want to exit the minishell
*/
void	clear_all(t_main_tools *tools)
{
	if (tools->args)
		free(tools->args);
	if (tools->pwd)
		free(tools->pwd);
	if (tools->old_pwd)
		free(tools->old_pwd);
	if (tools->pid)
		free(tools->pid);
	if (tools->lexer_list)
		clear_lexer(tools->lexer_list);
	if (tools->simple_cmd_list)
		clear_simple_cmd(tools);
	if (tools->envp_cpy)
		free_arr(tools->envp_cpy);
	if (tools->paths)
		free_arr(tools->paths);
}

/**
    @brief:
    clear_for_continue is a function that will clear all the allocated memory
    and set the tools struct to the default settings. It will then call the
    parse_envp function and minishell_loop function.
    we use it if we want to continue the minishell loop
*/
void	clear_for_continue(t_main_tools *tools)
{
	free(tools->args);
	if (tools->pid)
		free(tools->pid);
	if (tools->paths)
		free_arr(tools->paths);
	if (tools->lexer_list)
		clear_lexer(tools->lexer_list);
	if (tools->simple_cmd_list)
		clear_simple_cmd(tools);
	tools_to_default_setting(tools);
	parse_envp(tools);
	minishell_loop(tools);
}
