/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:19:18 by psimcak           #+#    #+#             */
/*   Updated: 2024/03/04 14:42:06 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void	tester(t_main_tools *tools, int signpost); // ZAKOMENTOVAT
int		minishell_loop(t_main_tools *tools);

// Definition and initialization of the global variable
int	g_signal = 0;

/*
	@brief:
	Setting these members to NULL is a way to ensure that the structure starts
	in a known state, preventing undefined behavior from uninitialized pointers
*/

void	tools_to_default_setting(t_main_tools *tools)
{
	tools->envp = NULL;
	tools->lexer_list = NULL;
	tools->paths = NULL;
	tools->simple_cmd_list = NULL;
	tools->pipes = 0;
	minishell_loop(tools);
}

void	set_pwd(t_main_tools *tools)
{
	char	*pwd;
	size_t	buf_size;

	buf_size = 1024;
	pwd = malloc(sizeof(char) * buf_size);
	if (!pwd)
		ft_putstr_fd_exit("Error: malloc failed", STDERR, 1);
	while(getcwd(pwd, buf_size) == NULL)
	{
		free(pwd);
		buf_size *= 2;
		pwd = malloc(sizeof(char) * buf_size);
		if (!pwd)
			ft_putstr_fd_exit("Error: malloc failed", STDERR, 1);
	}
	tools->pwd = pwd;
}

int	minishell_loop(t_main_tools *tools)
{
	char	*tmp;

	tools->args = readline(READLINE_MSG);
	tmp = ft_strtrim(tools->args, " ");
	free(tools->args);
	tools->args = tmp;
	token_reader(tools);
	tester(tools, LEXER_LIST); // ZAKOMENTOVAT
	parser(tools);
	tester(tools, CMD_LIST); // ZAKOMENTOVAT
	while(tools->simple_cmd_list)
	{
		heredoc(tools, tools->simple_cmd_list);
		printf("simple_cmd_list->heredoc_filename: %s\n", tools->simple_cmd_list->heredoc_filename);
		tools->simple_cmd_list = tools->simple_cmd_list->next;
	}
	tools_to_default_setting(tools);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_main_tools	tools;

	if (argc != 1 || argv[1] || !envp[0])
		ft_putstr_fd_exit("Error: don't put any arguments", STDOUT, 0);
	set_pwd(&tools);
	tools_to_default_setting(&tools);
	minishell_loop(&tools);
	return (0);
}
