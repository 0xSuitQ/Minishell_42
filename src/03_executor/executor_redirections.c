#include "../../includes/minishell.h"

int	read_from(t_simple_cmd *cmd, t_lexer *tmp, t_token_list redirection)
{
	int	fd;

	if (redirection == LESS)
			fd = open(tmp->next->sub_str, O_RDONLY);
	else
		fd = open(cmd->heredoc_filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("outfile: Error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (EXIT_SUCCESS);
}

int	write_to(t_lexer *tmp, t_token_list redirection)
{
	int	fd;

	if (redirection == GREAT)
		fd = open(tmp->next->sub_str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(tmp->next->sub_str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("infile: Error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (EXIT_SUCCESS);
}