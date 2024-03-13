/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:01:08 by nandroso          #+#    #+#             */
/*   Updated: 2024/03/12 18:20:00 by nandroso         ###   ########.fr       */
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
	tools->env_2d = NULL;
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
	convert_to_2d(tools);
}


/// @title Change environment variable
/// @notice Function changes the value of an environment variable by its name

void	change_env(t_main_tools *tools, char *name, char *value)
{
	t_env	*envp;

	envp = tools->envp_cpy;
	while (envp)
	{
		if (ft_strcmp(envp->name, name) == 0)
		{
			free(envp->value);
			envp->value = ft_strdup(value);
			return ; // THIS
		}
		envp = envp->next;
	}
}

void	add_slash(t_main_tools *tools)
{
	int		i;
	int		j;
	char	**iter;
	char	*temp;

	i = 0;
	j = 0;
	iter = tools->paths;
	while (iter[i])
	{
		if (iter[i][ft_strlen(iter[i]) - 1] != '/')
		{
			
			temp = ft_strjoin(tools->paths[i], "/");
			free(tools->paths[i]);
			tools->paths[i] = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
}

int	get_paths(t_main_tools *tools)
{
	t_env	*temp;

	temp = tools->envp_cpy;
	while (temp)
	{
		if (ft_strncmp(temp->name, "PATH", 4) == 0)
			tools->paths = ft_split(temp->value, ':');
		temp = temp->next;
	}
	if (tools->paths != NULL)
		add_slash(tools);
	return (EXIT_SUCCESS);
}

int	count_envp(t_env *envp_cpy)
{
	int		i;

	i = 0;
	while (envp_cpy)
	{
		i++;
		envp_cpy = envp_cpy->next;
	}
	return (i);
}

/// @title Convert environment linked list to 2D array 
/// @notice Function converts the environment linked list to a 2D array for execve format
/// @dev We use it in the beginning of main and everytime we change the environment (now just in cd)

void	convert_to_2d(t_main_tools *tools)
{
	int		i = 0;
	int		envp_counter;
	char	*temp;
	t_env	*envp_iter;

	if (tools->env_2d != NULL)
		free_arr(tools->env_2d);
	envp_iter = tools->envp_cpy;
	envp_counter = count_envp(tools->envp_cpy);
	tools->env_2d = malloc(sizeof(char *) * (envp_counter + 1));
	while (envp_iter)
	{
		temp = ft_strjoin(envp_iter->name, "=");
		temp = ft_strjoin(temp, envp_iter->value);
		tools->env_2d[i++] = ft_strdup(temp);
		free(temp);
		envp_iter = envp_iter->next;
	}
	tools->env_2d[i] = NULL;
}

// Example of static variable causing unexected behavior
// When we have testing printf in the end, it shows memory error
// When we change static int to normal, it works fine
/* 
void	convert_to_2d(t_main_tools *tools)
{
	static int		i = 0;
	int		envp_counter;
	char	*temp;
	t_env	*envp_iter;

	if (tools->env_2d != NULL)
		free_arr(tools->env_2d);
	envp_iter = tools->envp_cpy;
	envp_counter = count_envp(tools->envp_cpy);
	tools->env_2d = malloc(sizeof(char *) * (envp_counter + 1));
	while (envp_iter)
	{
		temp = ft_strjoin(envp_iter->name, "=");
		temp = ft_strjoin(temp, envp_iter->value);
		tools->env_2d[i++] = ft_strdup(temp);
		free(temp);
		envp_iter = envp_iter->next;
	}
	write(1, "!!!!!WE ARE HERE!!!!\n", 22);
	tools->env_2d[i] = NULL;
	int j = 0;
	while (tools->env_2d[j])
	{
		printf("%s\n", tools->env_2d[j++]);
	}
	printf("%d\n", j);
}
*/