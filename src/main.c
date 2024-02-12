/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:19:18 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/12 10:00:00 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void	tester(t_lexer	*lexer_list);	// ZAKOMENTOVAT
int	minishell_loop(t_main_tools *tools);

// Definition and initialization of the global variable
int	g_signal = 0;

void	reset_loop(t_main_tools *tools)
{
	minishell_loop(tools);
}

int	minishell_loop(t_main_tools *tools)
{
	t_lexer		*lexer_list;

	tools->envp = "hehe";
	lexer_list = lexer(readline("temp >_ "));
	// reset_loop(tools);

	// TESTER
	tester(lexer_list);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_main_tools	tools;

	if (argc != 1 || argv[1] || !envp[0])
		ft_putstr_fd_exit("Error: don't put any arguments", STDOUT, 0);
	minishell_loop(&tools);
	return (0);
}
