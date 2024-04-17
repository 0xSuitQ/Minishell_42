/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:10:56 by nandroso          #+#    #+#             */
/*   Updated: 2024/04/17 20:05:42 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	Print the environment variables
	The logic is:
	1. Get the environment variables from the tools
	2. Iterate through the environment variables
	3. Print the environment variables
	4. Return EXIT_SUCCESS
*/
int msh_env(t_main_tools *tools, t_simple_cmd *cmd)
{
	t_env	*envp;
	char	*tmp;

	(void)cmd;
	envp = tools->envp_cpy;
	while (envp)
	{
		tmp = ft_strjoin(envp->name, "=");
		tmp = ft_strjoin(tmp, envp->value);
		ft_putstr_fd(tmp, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(tmp);
		envp = envp->next;
	}
	return (EXIT_SUCCESS);
}
