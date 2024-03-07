/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:01:08 by nandroso          #+#    #+#             */
/*   Updated: 2024/03/06 21:14:12 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	copy_env(t_main_tools *tools, char **envp)
{
	char	**envp_cpy;

	
}

// void	change_env(t_main_tools *tools, char *name, char *value)
// {
// 	t_env	*env;

// 	env = tools->env;
// 	while (env)
// 	{
// 		if (ft_strcmp(env->name, name) == 0)
// 		{
// 			free(env->value);
// 			env->value = ft_strdup(value);
// 			return ;
// 		}
// 		env = env->next;
// 	}
// }