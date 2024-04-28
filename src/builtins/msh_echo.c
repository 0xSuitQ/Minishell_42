/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:10:42 by nandroso          #+#    #+#             */
/*   Updated: 2024/04/28 19:15:56 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	output_stuff(char **str, int n, int i)
{
	while (str[i])
	{
		ft_putstr_fd(str[i], STDOUT_FILENO);
		i++;
		if (str[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (n == 0)
		write(STDOUT_FILENO, "\n", 1);
}

int	msh_echo(t_main_tools *tools, t_simple_cmd *cmd)
{
	int	i;
	int	j;
	int	n;

	n = 0;
	i = 1;
	(void)tools;
	while (cmd->str[i] && cmd->str[i][0] == '-' && cmd->str[i][1] == 'n')
	{
		j = 1;
		while (cmd->str[i][j] == 'n')
			j++;
		if (cmd->str[i][j] == '\0')
			n = 1;
		else
			break ;
		i++;
	}
	output_stuff(cmd->str, n, i);
	return (EXIT_SUCCESS);
}
