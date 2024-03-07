/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:01:08 by nandroso          #+#    #+#             */
/*   Updated: 2024/03/07 15:27:32 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env(t_main_tools *tools, char *name, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (env == NULL)
        return ;
	env->name = ft_strdup(name);
	if (!env->name)
		write(1, "Error: env->name is NULL\n", 25);
	env->value = ft_strdup(value);
	if (!env->value)
		write(1, "Error: env->value is NULL\n", 26);
	if (tools->envp_cpy == NULL)
	{
		tools->envp_cpy = env;
		tools->envp_cpy->next = NULL;
	}
	else
		tools->envp_cpy->next = env;
}

void	copy_env(t_main_tools *tools, char **envp)
{
	char	**envp_cpy;

	while (*envp)
	{
		write(1, "we are here\n", 12);
		envp_cpy = ft_split(*envp, '=');
		if (!envp_cpy[0] || !envp_cpy[1])
			write(1, "Error: envp_cpy[0] or envp_cpy[1] is NULL\n", 41);
		add_env(tools, envp_cpy[0], envp_cpy[1]);
		// free(envp_cpy[0]);
		// free(envp_cpy[1]);
		// free(envp_cpy);
		envp++;
	}
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