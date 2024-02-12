/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:19:18 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/12 07:43:38 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	minishell_loop(t_main_tools *tools);

// Definition and initialization of the global variable
int	g_signal = 0;

void	reset_loop(t_main_tools *tools)
{
	minishell_loop(tools);
}

// /*
// signal = "If this signal happens, do this instead of what you'd normally do."
// 				(SIGINT)		(handle_sigint)
// SIGINT
// signal that is typically sent to a program when the interrupt key (Ctrl + C) 
// is pressed. By default, this signal terminates a program.
// */
int	minishell_loop(t_main_tools *tools)
{
	t_lexer		*lexer_list;

	tools->envp = "hehe";
	lexer_list = lexer(readline("temp >_ "));
	// reset_loop(tools);

	// TEST
	while (lexer_list)
	{
		printf("str of the lexer list number\t %d: %s\n", lexer_list->index, lexer_list->sub_str);
		printf("token of the lexer list number\t %d: %d\n", lexer_list->index, lexer_list->token);
		printf("------------------\n");
		lexer_list = lexer_list->next;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_main_tools	tools;

	if (argc != 1 || argv[1] || !envp[0])
	{
		ft_putstr_fd("Error: Minishell doesn't take any arguments.\n", 2);
		return (0);
	}
	minishell_loop(&tools);
	return (0);
}
