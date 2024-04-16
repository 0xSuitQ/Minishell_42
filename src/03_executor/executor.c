/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:36:14 by peta              #+#    #+#             */
/*   Updated: 2024/04/15 15:39:27 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	receive_heredoc(int fd[2], t_simple_cmd *cmd)
{
	int	fd_in;

	if (cmd->heredoc_filename)
	{
		close(fd[0]);
		fd_in = open(cmd->heredoc_filename, O_RDONLY);
	}
	else
		fd_in = fd[0];
	return (fd_in);
}

int	locate_and_execute_command(t_simple_cmd *cmd, t_main_tools *tools)
{
	char	*path;
	int		i;

	i = 0;
	while (tools->paths[i])
	{
		path = ft_strjoin(tools->paths[i], cmd->str[0]);
		if (access(path, F_OK) == 0)
			execve(path, cmd->str, tools->env_2d);
		free(path);
		i++;
	}
	ft_putstr_fd(cmd->str[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	setup_fd(t_simple_cmd *cmd)
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

void	prepare_exec(t_main_tools *tools, t_simple_cmd *cmd)
{
	int command_result = 0;
	
	if (cmd->lexer_list && cmd->lexer_list->token)
	{
		if (setup_fd(cmd))
			exit(1);
	}
	// Attempt to execute built-in command first
	if (cmd->builtin)
	{
		command_result = cmd->builtin(tools, cmd);
		exit(command_result);
	}

	// If not a built-in, try finding an external command
	if (cmd->str[0][0] != '\0')
		command_result = locate_and_execute_command(cmd, tools);

	exit(command_result);
}

void	pipe_dup(t_main_tools *tools, t_simple_cmd *cmd, int fd[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		write(2, "OOPS\n", 5); //ft_error(4, tools);
	close(fd[0]);
	if (cmd->next && dup2(fd[1], STDOUT_FILENO) < 0)
		write(2, "OOPS\n", 5);//ft_error(4, tools);
	close(fd[1]);
	if (cmd->prev)
		close(fd_in);
	prepare_exec(tools, cmd); // there look for the path and execute the command
}

int	forking(t_main_tools *tools, t_simple_cmd *cmd, int fd[2], int fd_in)
{
	static int	i = 0;

	if (tools->finished == 1)
	{
		// write(2, "finished\n", 9);
		tools->finished = 0;
		i = 0;
	}
	tools->pid[i] = fork();
	if (tools->pid[i] == 0)
	{
		pipe_dup(tools, cmd, fd, fd_in);
	}
	i++;
	return (EXIT_SUCCESS);
}

int wait_pids(t_main_tools *tools)
{
	int	i;
	int	status;

	i = 0;
	while (tools->pid[i])
	{
		waitpid(tools->pid[i], &status, 0);
		if (WIFEXITED(status))
			tools->exit_status = WEXITSTATUS(status);
		i++;
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
	int	fd[2];
	int	fd_in;
	t_simple_cmd	*cmd;

	cmd = tools->simple_cmd_list;
	fd_in = STDIN_FILENO;
	while (cmd)
	{
		expander(cmd);
		if (cmd->next)
			pipe(fd);
		heredoc(tools, cmd);
		forking(tools, cmd, fd, fd_in);
		close(fd[1]);

		fd_in = receive_heredoc(fd, cmd);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	wait_pids(tools);
	return (EXIT_SUCCESS);
}

/**
 * @brief:
	check_builtin is a function that will check if the command is a built-in
	command.
	->	If it IS a built-in command, it will execute it and return the exit_
		status of the command (EXIT_SUCCESS (or - for msh_cd - EXIT_FAILURE))
	->	If it is NOT a built-in command, it will return EXIT_FAILURE.
*/
int	check_builtin(t_main_tools *tools, t_simple_cmd *cmd)
{
	int	exit_status;

	exit_status = EXIT_FAILURE;
	if (cmd->builtin == msh_echo || cmd->builtin == msh_pwd
		|| cmd->builtin == msh_cd || cmd->builtin == msh_env)
	{
		exit_status = cmd->builtin(tools, cmd);
		return (exit_status);
	}
	return (exit_status);
}

/**
 * @brief:
	Execute_no_pipes is a function that will be called when there are no pipes
	in the command. It will check if the command is a built-in command and
	execute it. If it is not a built-in command, it will execute the command
	by calling the run_cmd function.
*/
void	execute_no_pipes(t_main_tools *tools)
{
	// int	pid;
	t_simple_cmd	*cmd;

	cmd = tools->simple_cmd_list;
	expander(cmd);
	heredoc(tools, cmd);
	tools->pid[0] = fork();
	if (tools->pid[0] == 0)
	{
		prepare_exec(tools, cmd);
		if (!check_builtin(tools, cmd))
			return ;
	}
	wait_pids(tools);
	// exitstatus
}

/**
 * @brief:
	Executor is the main function here. It will call the appropriate function:
	either execute_no_pipes or execute_with_pipes. It just a crossroad for
	the two functions.
	The executor is the component responsible for actually running the commands
	entered by the user. Its main tasks include:
	- 
*/
int	executor(t_main_tools *tools)
{
	if (tools->pipes == 0)
	{
		tools->pid = malloc(1 * sizeof(int));
		if (!tools->pid)
			return (EXIT_FAILURE); // TODO memory error
		execute_no_pipes(tools);
	}
	else
	{
		tools->pid = malloc((tools->pipes + 2) * sizeof(int));
		if (!tools->pid)
			return (EXIT_FAILURE); // TODO memory error 
		tools->pid[tools->pipes + 2] = 0;
		execute_with_pipes(tools);
	}
	return (EXIT_SUCCESS);
}
