/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                           :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:03:55 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/20 18:06:50 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	gen_filename is a function that will generate a filename for the heredoc
*/
char	*gen_filename(void)
{
	char		*filename;
	char		*number;
	static int	i;

	i = 0;
	number = ft_itoa(i++);
	filename = ft_strjoin("/tmp/msh_heredoc_", number);
	free(number);
	return (filename);
}

/**
	@brief:
	create_heredoc is a function that will create a heredoc file
*/
void	create_heredoc(t_lexer *lexer_list, char *filename)
{
	int		fd;
	char	*line;
	char	*delimiter;

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	delimiter = lexer_list->next->sub_str;
	quote_check(&delimiter);
	signal(SIGINT, handle_sigint_heredoc);
	line = readline("heredoc> ");
	while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter)) != 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	close(fd);
}

/**
	@brief:
	fork_heredoc is a function that will fork a child process for the heredoc
	and wait for the child process to finish.
*/
void	fork_heredoc(t_main_tools *tools, t_lexer *lexer_list, char *filename)
{
	int	pid;
	int	status;

	fork_process(&pid, tools);
	if (pid == 0)
	{
		signal(SIGINT, handle_sigint_heredoc);
		create_heredoc(lexer_list, filename);
		exit_minishell(NULL, 0);
	}
	else
	{
		signal(SIGINT, handle_sigint_when_child_running);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			tools->exit_status = WEXITSTATUS(status);
	}
}

/**
	@brief:
	heredoc is a function that will go through the lexer_list and check for the
	heredoc token. If the token is found, it will create a heredoc file.
*/
int	heredoc(t_main_tools *tools, t_simple_cmd *cmd)
{
	int				fd;
	t_lexer			*tmp;
	t_simple_cmd	*simple_cmd_list;

	(void)tools;
	(void)fd;
	simple_cmd_list = cmd;
	tmp = simple_cmd_list->lexer_list;
	while (tmp)
	{
		if (tmp->token == LESS_LESS)
		{
			if (cmd->heredoc_filename)
				free(cmd->heredoc_filename);
			cmd->heredoc_filename = gen_filename();
			fork_heredoc(tools, tmp, cmd->heredoc_filename);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
