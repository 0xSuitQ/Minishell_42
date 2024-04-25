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
	char 		*filename;
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
	delete_quotes is a function that will delete the quotes from the string
*/
char	*delete_quotes(char *str, char c)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], j + 1);
		}
	}
	return (str);
}

/**
	@brief:
	quote_check is a function that will check if the delimiter is a quote
	and delete the quotes from the delimiter
*/
void	quote_check(char **delimiter)
{
	if ((*delimiter)[0] == '\'' || (*delimiter)[0] == '\"')
	{
		delete_quotes((*delimiter), '\'');
		delete_quotes((*delimiter), '\"');
	}
}

// todo = add signal handling
// signal(SIGINT, handle_sigint_heredoc);
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
			create_heredoc(tmp, cmd->heredoc_filename);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
