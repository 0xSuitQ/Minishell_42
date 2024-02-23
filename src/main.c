/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:19:18 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/22 13:40:36 by psimcak          ###   ########.fr       */
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
	minishell_loop(tools);
}

int	minishell_loop(t_main_tools *tools)
{
	tools->lexer_list = lexer(readline(READLINE_MSG));
	// tester(tools, LEXER_LIST); // ZAKOMENTOVAT
	parser(tools);
	tester(tools, CMD_LIST); // ZAKOMENTOVAT
	expander(tools);
	tools_to_default_setting(tools);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_main_tools	tools;

	if (argc != 1 || argv[1] || !envp[0])
		ft_putstr_fd_exit("Error: don't put any arguments", STDOUT, 0);
	tools_to_default_setting(&tools);
	minishell_loop(&tools);
	return (0);
}
