/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:23:21 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/25 20:23:40 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	// free(lexer_list);
}

void	free_envp(char **envp_cpy)
{
	free_arr(envp_cpy);
}

void	clear_simple_cmd(t_main_tools *tools)
{
	t_simple_cmd	*current;
	t_simple_cmd	*next;

	current = tools->simple_cmd_list;
	while (current)
	{
		next = current->next;
		free_arr(current->str);
		if (current->lexer_list && !current->heredoc_filename)
			clear_lexer(current->lexer_list);
		if (current->heredoc_filename)
			free(current->heredoc_filename);
		free(current);
		current = next;
	}
	tools->simple_cmd_list = NULL;
	// free(tools->simple_cmd_list);
}

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
		free_envp(tools->envp_cpy);
	if (tools->paths)
		free_arr(tools->paths);
	// tools_to_default_setting(tools);
}

void 	clear_for_continue(t_main_tools *tools)
{
	free(tools->args);
	if (tools->pid)
		free(tools->pid);
	// free(tools->paths);
	if (tools->lexer_list)
		clear_lexer(tools->lexer_list);
	if (tools->simple_cmd_list)
		clear_simple_cmd(tools);
	// if (tools->pwd)
	// 	free(tools->pwd);
	// if (tools->old_pwd)
	// 	free(tools->old_pwd);
	tools_to_default_setting(tools);
}

int	error_police(int err_code, t_main_tools *tools)
{
	if (err_code == 1)
	{
		clear_all(tools);
		exit (tools->exit_status);
	}
	else if (err_code == 2)
		clear_for_continue(tools);
	if (err_code == 3)
	{
		clear_all(tools);
		exit (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}