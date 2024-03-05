/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:10:32 by nandroso          #+#    #+#             */
/*   Updated: 2024/03/05 10:10:35 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_cd(t_main_tools *tools, t_simple_cmd *cmd)
{
	char *home_dir;
	char *error_msg;

	error_msg = "cd: no such file or directory: ";
	tools->old_pwd = tools->pwd;
	if (cmd->str[1] == NULL)
	{
		write(1, "we are in the cd\n", 17);
		if ((home_dir = getenv("HOME")) == NULL)
			return (EXIT_FAILURE);
        if (chdir(home_dir) == -1)
			return (EXIT_FAILURE);
		tools->pwd = home_dir;
	}
	else
	{
		if(chdir(cmd->str[1]) == -1)
		{
			write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
			write(STDERR_FILENO, cmd->str[1], ft_strlen(cmd->str[1]));
			write(STDERR_FILENO, "\n", 1);
			return (EXIT_FAILURE);
		}
		tools->pwd = cmd->str[1];
	}
	return (EXIT_SUCCESS);
}
