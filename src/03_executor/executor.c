#include "../../includes/minishell.h"

int	receive_heredoc(t_main_tools *tools, int fd[2], t_simple_cmd *cmd)
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

void	pipe_dup(t_main_tools *tools, t_simple_cmd *cmd, int fd[2], int fd_in)
{
	if (cmd->prev)
		dup2(fd_in, STDIN_FILENO);
	close(fd[0]);
	if (cmd->next)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (cmd->prev)
		close(fd_in);
	exec_cmd(tools, cmd); // there look for the path and execute the command
}

int	forking(t_main_tools *tools, t_simple_cmd *cmd, int fd[2], int fd_in)
{
	int	i;

	i = 0;
	tools->pid = fork();
	if (tools->pid == 0)
	{
		pipe_dup(tools, cmd, fd, fd_in);
	}
	i++;
	return (EXIT_SUCCESS);
}

int	check_builtins(t_main_tools *tools, t_simple_cmd *cmd, int fd[2], int fd_in)
{
	if (tools->simple_cmd_list->builtin)
		return (tools->simple_cmd_list->builtin(tools, tools->simple_cmd_list));
	else
		return (forking(tools, tools->simple_cmd_list, fd, fd_in));
}

int	executor(t_main_tools *tools)
{
	int	fd[2];
	int	fd_in;

	fd_in = STDIN_FILENO;
	while (tools->simple_cmd_list)
	{
		// expander
		if (tools->simple_cmd_list->next)
			pipe(fd);
		heredoc(tools, tools->simple_cmd_list);
		check_builtins(tools, tools->simple_cmd_list, fd, fd_in); // it might be before all the fd shit
		close(fd[1]);

		fd_in = receive_heredoc(tools, fd, tools->simple_cmd_list);
		if (tools->simple_cmd_list->next)
			tools->simple_cmd_list = tools->simple_cmd_list->next;
		else
			break ;
	}
	// wait 
	// reset simple_cmds to the head
}
