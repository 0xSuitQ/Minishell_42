/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:17:55 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 14:05:55 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	locate_and_execute_command is a function that will look for the path of the
	command and execute it. If the command is not found, it will print an error
	message and return EXIT_FAILURE.
	This is the function that will be called when the command is not a built-in
	command.
*/
static int	locate_and_execute_command(t_simple_cmd *cmd, t_main_tools *tools)
{
	char	*path;
	int		i;

	i = 0;
	if (!access(cmd->str[0], F_OK))
		execve(cmd->str[0], cmd->str, tools->envp_cpy);
	while (tools->paths[i])
	{
		path = ft_strjoin(tools->paths[i], cmd->str[0]);
		if (access(path, F_OK) == 0)
			execve(path, cmd->str, tools->envp_cpy);
		free(path);
		i++;
	}
	ft_putstr_fd(cmd->str[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	error_police(1, tools);
	return (EXIT_FAILURE);
}

/*
	@brief:
	setup_fd is a function that will setup the file descriptors for the command.
	It will go through the lexer_list and check for the redirection tokens.
	- If the token is LESS or LESS_LESS, it will call the read_from function.
	- If the token is GREAT or GREAT_GREAT, it will call the write_to function.

*/
static int	setup_fd(t_simple_cmd *cmd)
{
	t_lexer	*tmp;

	tmp = cmd->lexer_list;
	while (tmp)
	{
		if (tmp->token == LESS || tmp->token == LESS_LESS)
			if (read_from(cmd, tmp, tmp->token))
				return (EXIT_FAILURE);
		if (tmp->token == GREAT || tmp->token == GREAT_GREAT)
			if (write_to(tmp, tmp->token))
				return (EXIT_FAILURE);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

/**
	@brief:
	prepare_exec is a function that will prepare the execution of the command.
	It will check if the command is a built-in command and execute it.
	If it is not a built-in command, it will look for the path and execute
	the command.
	1st IF statement:
		- If the lexer_list is not NULL and the token is not NULL, it will
		setup the file descriptors for the command.
	2nd IF statement:
		- If the command is a built-in command, it will execute it and exit
		the process.
	3rd IF statement:
		- If the command is not a built-in command, it will look for the path
		and execute the external command.
*/
void	prepare_exec(t_main_tools *tools, t_simple_cmd *cmd)
{
	int	command_result;

	command_result = 0;
	if (cmd->lexer_list && cmd->lexer_list->token)
		if (setup_fd(cmd))
			exit(1);
	if (cmd->builtin)
	{
		command_result = cmd->builtin(tools, cmd);
		exit(command_result);
	}
	if (cmd->str[0] && cmd->str[0][0] != '\0')
		command_result = locate_and_execute_command(cmd, tools);
	exit(command_result);
}
