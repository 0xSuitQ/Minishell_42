/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:19:18 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/09 14:48:45 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Definition and initialization
int	g_signal = 0;

int	minishell_loop()
{
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	input = "ls -l > file.txt";
	if (argc != 1 || argv[1])
	{
		ft_putstr_fd("Error: Minishell doesn't take any arguments.\n", 2);
		return (0);
	}
	lexer(input);
	return (0);
}
