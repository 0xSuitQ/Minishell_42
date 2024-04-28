/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:36:14 by peta              #+#    #+#             */
/*   Updated: 2024/04/28 19:16:22 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	receive_heredoc is a function that will receive the heredoc input from
	the file descriptor. If the heredoc_filename is not NULL, it will open
	the file and return the file descriptor. If the heredoc_filename is NULL,
	it will return the file descriptor.
*/
int	receive_heredoc(int fd[2], t_simple_cmd *cmd)
{
	int	fd_in;

	if (cmd->heredoc_filename)
	{
		if (fd)
			close(fd[0]);
		fd_in = open(cmd->heredoc_filename, O_RDONLY);
	}
	else if (fd != NULL)
		fd_in = fd[0];
	else
		fd_in = STDIN_FILENO;
	return (fd_in);
}

/**
	@brief:
	wait_pids is a function that will wait for the child processes to finish.
	For every child process, it will wait for the process to finish and then
	check the exit status of the process.
*/
int	wait_pids(t_main_tools *tools, int flag)
{
	int	i;
	int	status;

	i = 0;
	if (flag == 1)
	{
		while (tools->pid[i] != 0)
		{
			waitpid(tools->pid[i], &status, 0);
			if (WIFEXITED(status))
				tools->exit_status = WEXITSTATUS(status);
			i++;
		}
	}
	else
	{
		waitpid(tools->pid[0], &status, 0);
		if (WIFEXITED(status))
			tools->exit_status = WEXITSTATUS(status);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief:
	If there pipes in the command, call this function.
	Function goes through the simple_cmd_list and executes the commands.
	For every command it will create a pipe and fork a child process.
*/
int	execute_with_pipes(t_main_tools *tools)
{
	t_simple_cmd	*cmd;
	int				fd[2];
	int				fd_in;

	cmd = tools->simple_cmd_list;
	fd_in = STDIN_FILENO;
	while (cmd)
	{
		if (there_is_dollar_in_list(cmd->str))
			expander(cmd);
		if (cmd->next)
			pipe(fd);
		heredoc(tools, cmd);
		forking(tools, cmd, fd, fd_in);
		signal(SIGINT, handle_sigint_when_child_running);
		close(fd[1]);
		fd_in = receive_heredoc(fd, cmd);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	wait_pids(tools, 1);
	return (EXIT_SUCCESS);
}

/**
	@brief:
	Execute_no_pipes is a function that will be called when there are no pipes
	in the command. It will check if the command is a built-in command and
	execute it. If it is not a built-in command, it will execute the command
	by calling the run_cmd function.
	cmd->builtin is a function pointer to the built-in command.
*/
void	execute_no_pipes(t_main_tools *tools)
{
	t_simple_cmd	*cmd;
	int				fd_in;

	cmd = tools->simple_cmd_list;
	if (there_is_dollar_in_list(cmd->str))
		expander(cmd);
	if (check_builtin(tools, cmd) == 1)
		return ;
	heredoc(tools, cmd);
	fd_in = receive_heredoc(NULL, cmd);
	tools->pid[0] = fork();
	if (tools->pid[0] == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		prepare_exec(tools, cmd);
	}
	wait_pids(tools, 0);
}

/**
	@brief:
	Executor is the main function here. It will call the appropriate function:
	either execute_no_pipes or execute_with_pipes. It just a crossroad for
	the two functions.
	The executor is the component responsible for actually running the commands
	entered by the user. Its main tasks include:
	- Executing the command without pipes.
	- Executing the command with pipes.
	STDERR_FILENO = STDERR = 2 = Standard error output
	@returns:
	EXIT_SUCCESS if the command was executed successfully or EXIT_FAILURE if
	there was an error.
*/
int	executor(t_main_tools *tools)
{
	if (tools->pipes == 0)
	{
		if (tools->pid)
			free(tools->pid);
		tools->pid = malloc(2 * sizeof(int));
		memory_error(tools->pid, tools, 1, NULL);
		tools->pid[1] = 0;
		execute_no_pipes(tools);
	}
	else
	{
		tools->pid = malloc((tools->pipes + 2) * sizeof(int));
		memory_error(tools->pid, tools, 1, NULL);
		tools->pid[tools->pipes + 1] = 0;
		execute_with_pipes(tools);
	}
	if (tools->pid)
	{
		free(tools->pid);
		tools->pid = NULL;
	}
	return (EXIT_SUCCESS);
}
