/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:03:55 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/20 18:06:50 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*gen_filename()
{
	char 		*filename;
	static int 	i = 0;
	char		*number;

	number = ft_itoa(i++);
	filename = ft_strjoin("/tmp/msh_heredoc_", number);
	free(number);
	return (filename);
}

char	*delete_quotes(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], ft_strlen(str) - i);
		}
		i++;
	}
	return (str);
}

int	quote_check(char **delimiter)
{
	int		flag;

	flag = 0;
	if ((*delimiter)[0] == '\'' || (*delimiter)[0] == '\"')
	{
		if ((*delimiter)[0] == '\'')
			flag = 1;
		else if ((*delimiter)[0] == '\"')
			flag = 2;
		delete_quotes((*delimiter), '\'');
		delete_quotes((*delimiter), '\"');
	}
	return (flag);
}

void	create_heredoc(t_lexer *lexer_list, char *filename)
{
	int		fd;
	char	*line;
	char 	*delimiter;

	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	delimiter = lexer_list->next->sub_str;
	printf("delimiter: %s\n", delimiter);
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

int	heredoc(t_main_tools *tools, t_simple_cmd *cmd)
{
	int				fd;
	t_lexer			*lexer_list;
	t_simple_cmd	*simple_cmd_list;

	(void)tools;
	(void)fd;
	simple_cmd_list = cmd;
	lexer_list = simple_cmd_list->lexer_list;
	while(lexer_list)
	{
		if (lexer_list->token == LESS_LESS)
		{
			if (cmd->heredoc_filename)
				free(cmd->heredoc_filename);
			cmd->heredoc_filename = gen_filename();
			create_heredoc(lexer_list, cmd->heredoc_filename);
		}
		lexer_list = lexer_list->next;
	}
	return (0);
}