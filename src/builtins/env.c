/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:10:56 by nandroso          #+#    #+#             */
/*   Updated: 2024/03/07 15:28:33 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int msh_env(t_main_tools *tools, t_simple_cmd *cmd)
{
	t_env *envp;
	char *tmp;

	(void)cmd;
	envp = tools->envp_cpy;
	while (envp)
	{
		// printf("envp->name: %s\n", tools->envp_cpy->name);
		// printf("envp->value: %s\n", tools->envp_cpy->value);
		tmp = ft_strjoin(envp->name, "=");
		tmp = ft_strjoin(tmp, envp->value);
		ft_putstr_fd(tmp, STDOUT_FILENO);
		free(tmp);
		envp = envp->next;
	}
	return (EXIT_SUCCESS);
}