/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:36:14 by peta              #+#    #+#             */
/*   Updated: 2024/04/25 21:46:47 by psimcak          ###   ########.fr       */
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
	locate_and_execute_command is a function that will look for the path of the
	command and execute it. If the command is not found, it will print an error
	message and return EXIT_FAILURE.
	This is the function that will be called when the command is not a built-in
	command.
*/
int	locate_and_execute_command(t_simple_cmd *cmd, t_main_tools *tools)
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
	return (EXIT_FAILURE);
}

/*
	@brief:
	setup_fd is a function that will setup the file descriptors for the command.
	It will go through the lexer_list and check for the redirection tokens.
	- If the token is LESS or LESS_LESS, it will call the read_from function.
	- If the token is GREAT or GREAT_GREAT, it will call the write_to function.

*/
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
	printf("pid: %d\n", tools->pid[i]);
	if (tools->pid[i] == 0)
		pipe_dup(tools, cmd, fd, fd_in);
	i++;
	return (EXIT_SUCCESS);
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
 * @brief:
	check_builtin is a function that will check if the command is a built-in
	command.
	->	If it IS a built-in command, it will execute it and return the exit_
		status of the command (EXIT_SUCCESS (or - for msh_cd - EXIT_FAILURE))
	->	If it is NOT a built-in command, it will return EXIT_FAILURE.
*/
int	check_builtin(t_main_tools *tools, t_simple_cmd *cmd)
{
	if (cmd->builtin == msh_pwd || cmd->builtin == msh_export
		|| cmd->builtin == msh_cd || cmd->builtin == msh_env
		|| cmd->builtin == msh_exit || cmd->builtin == msh_unset) // echo should not be here 
	{
		tools->exit_status = cmd->builtin(tools, cmd);
		return (1);
	}
	return (0);
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
		if (!tools->pid)
		{
			ft_putstr_fd("memory error: unable to assign memory\n", STDERR);
			error_police(2, tools);
		}
		tools->pid[1] = 0;
		execute_no_pipes(tools);
	}
	else
	{
		tools->pid = malloc((tools->pipes + 2) * sizeof(int));
		if (!tools->pid)
		{
			ft_putstr_fd("memory error: unable to assign memory\n", STDERR);
			error_police(2, tools);
		}
		printf("pipes: %d\n", tools->pipes);
		tools->pid[tools->pipes + 1] = 0;
		execute_with_pipes(tools);
	}
	if (tools->pid) {
    	free(tools->pid);
   	 	tools->pid = NULL;
	}
	return (EXIT_SUCCESS);
}
