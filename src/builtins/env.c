/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:10:56 by nandroso          #+#    #+#             */
/*   Updated: 2024/03/05 12:52:32 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int msh_env(t_main_tools *tools, t_simple_cmd *cmd)
{
	char **envp;
	char *tmp;

	(void)cmd;
	envp = tools->envp;
	while (envp && *envp)
	{
		tmp = *envp;
		ft_putstr_fd(tmp, STDOUT_FILENO);
		envp++;
	}
	return (EXIT_SUCCESS);
}