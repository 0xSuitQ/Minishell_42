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
	//char	*tmp;
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
	ft_putstr_fd("minishell: ", STDERR_FILENO);
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

void	check_builtin(t_main_tools *tools, t_simple_cmd *cmd)
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
	check_builtin(tools, cmd); // there look for the path and execute the command
}

int	forking(t_main_tools *tools, t_simple_cmd *cmd, int fd[2], int fd_in)
{
	//int	i;

	//i = 0;
	tools->pid = fork();
	if (tools->pid == 0)
	{
		pipe_dup(tools, cmd, fd, fd_in);
	}
	//i++;
	return (EXIT_SUCCESS);
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
		forking(tools, tools->simple_cmd_list, fd, fd_in); // it might be before all the fd shit
		close(fd[1]);

		fd_in = receive_heredoc(fd, tools->simple_cmd_list);
		if (tools->simple_cmd_list->next)
			tools->simple_cmd_list = tools->simple_cmd_list->next;
		else
			break ;
	}
	// wait 
	// reset simple_cmds to the head
	return (EXIT_SUCCESS);
}
