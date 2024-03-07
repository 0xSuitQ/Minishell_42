/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:01:08 by nandroso          #+#    #+#             */
/*   Updated: 2024/03/07 18:37:15 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env(t_main_tools *tools, char *name, char *value)
{
	t_env	*env;
	t_env	*last;

	env = malloc(sizeof(t_env));
	if (env == NULL)
        return ;
	env->name = ft_strdup(name);
	env->value = ft_strdup(value);
	if (tools->envp_cpy == NULL)
	{
		tools->envp_cpy = env;
		tools->envp_cpy->next = NULL;
	}
	else
	{
		last = tools->envp_cpy;
		if (last == NULL)
			write(1, "Error: last is NULL\n", 21);
		while (last->next)
			last = last->next;
		last->next = env;
		env->next = NULL;
	}
}

void	copy_env(t_main_tools *tools, char **envp)
{
	char	**envp_cpy;

	tools->envp_cpy = NULL;
	while (*envp)
	{
		envp_cpy = ft_split(*envp, '=');
		if (!envp_cpy[0] || !envp_cpy[1])
			write(1, "Error: envp_cpy[0] or envp_cpy[1] is NULL\n", 41);
		add_env(tools, envp_cpy[0], envp_cpy[1]);
		free(envp_cpy[0]);
		free(envp_cpy[1]);
		free(envp_cpy);
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