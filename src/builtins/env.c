/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:10:56 by nandroso          #+#    #+#             */
/*   Updated: 2024/03/05 11:00:27 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int msh_env(t_main_tools *tools, t_simple_cmd *cmd)
{
	char	*this_env;

	(void)cmd;
	this_env = tools->envp;
	while (this_env)
	{
		ft_putstr_fd(this_env, STDOUT_FILENO);
		// write(STDOUT_FILENO, "\n", 1);
	}
	return (EXIT_SUCCESS);
}