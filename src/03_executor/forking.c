/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:52:40 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 19:15:35 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	pipe_dup is a function that will duplicate the file descriptors for the
	commands. It will close the file descriptors that are not needed and
	call the prepare_exec function. Which will look for the path and execute
	the command.
*/
void	pipe_dup(t_main_tools *tools, t_simple_cmd *cmd, int fd[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
		error_police(2, tools);
	}
	close(fd[0]);
	if (cmd->next && dup2(fd[1], STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("Failed to create pipe\n", STDERR_FILENO);
		error_police(2, tools);
	}
	close(fd[1]);
	if (cmd->prev)
		close(fd_in);
	prepare_exec(tools, cmd);
}

/**
	@brief:
	forking is a function that will fork a child process for every command
	in the simple_cmd_list. It will create a pipe for every command and
	call the pipe_dup function.
*/
int	forking(t_main_tools *tools, t_simple_cmd *cmd, int fd[2], int fd_in)
{
	static int	i = 0;

	if (tools->finished == 1)
	{
		tools->finished = 0;
		i = 0;
	}
	tools->pid[i] = fork();
	if (tools->pid[i] == 0)
		pipe_dup(tools, cmd, fd, fd_in);
	i++;
	return (EXIT_SUCCESS);
}
