#include "minishell.h"

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

void	free_envp(t_env *envp_cpy, char **env_2d)
{
	t_env	*current;
	t_env	*next;

	current = envp_cpy;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	envp_cpy = NULL;
	free_arr(env_2d);
	// free(envp_cpy);
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
		if (current->heredoc_filename)
			free(current->heredoc_filename);
		if (current->lexer_list)
			clear_lexer(current->lexer_list);
		free(current);
		current = next;
	}
	tools->simple_cmd_list = NULL;
	// free(tools->simple_cmd_list);
}

void	clear_all(t_main_tools *tools, int exit_status)
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
	if (tools->envp_cpy || tools->env_2d)
		free_envp(tools->envp_cpy, tools->env_2d);
	if (tools->paths)
		free_arr(tools->paths);
	exit(exit_status);
}

void 	clear_for_continue(t_main_tools *tools)
{
	if (tools->args)
		free(tools->args);
	if (tools->pid)
		free(tools->pid);
	if (tools->lexer_list)
		clear_lexer(tools->lexer_list);
	if (tools->simple_cmd_list)
		clear_simple_cmd(tools);
	tools_to_default_setting(tools);
}

void	error_police(int err_code, t_main_tools *tools)
{
	if (err_code == 1)
		clear_all(tools, tools->exit_status);
	else if (err_code == 2)
		clear_for_continue(tools);
}