/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:01:08 by nandroso          #+#    #+#             */
/*   Updated: 2024/04/23 20:06:31 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	add_env(t_main_tools *tools, char *name, char *value)
// {
// 	t_env	*env;
// 	t_env	*last;

// 	env = malloc(sizeof(t_env));
// 	if (env == NULL)
// 		return ;
// 	env->name = ft_strdup(name);
// 	env->value = ft_strdup(value);
// 	if (tools->envp_cpy == NULL)
// 	{
// 		tools->envp_cpy = env;
// 		tools->envp_cpy->next = NULL;
// 	}
// 	else
// 	{
// 		last = tools->envp_cpy;
// 		if (last == NULL)
// 			write(1, "Error: last is NULL\n", 21);
// 		while (last->next)
// 			last = last->next;
// 		last->next = env;
// 		env->next = NULL;
// 	}
// }

// void	copy_env(t_main_tools *tools, char **envp)
// {
// 	char	**envp_cpy;
// 	int		i;

// 	tools->envp_cpy = NULL;
// 	tools->env_2d = NULL;
// 	while (*envp)
// 	{
// 		envp_cpy = ft_split(*envp, '=');
// 		add_env(tools, envp_cpy[0], envp_cpy[1]);
// 		i = -1;
// 		while (envp_cpy[++i] != NULL)
// 			free(envp_cpy[i]);
// 		free(envp_cpy);
// 		envp++;
// 	}
// 	convert_to_2d(tools);
// }

// /// @title Change environment variable
// /// @notice Function changes the value of an environment variable by its name

// void	change_env(t_main_tools *tools, char *name, char *value)
// {
// 	t_env	*envp;

// 	envp = tools->envp_cpy;
// 	while (envp)
// 	{
// 		if (ft_strcmp(envp->name, name) == 0)
// 		{
// 			free(envp->value);
// 			envp->value = ft_strdup(value);
// 			return ; // THIS
// 		}
// 		envp = envp->next;
// 	}
// }

// void	add_slash(t_main_tools *tools)
// {
// 	int		i;
// 	char	**iter;
// 	char	*temp;

// 	i = 0;
// 	iter = tools->paths;
// 	while (iter[i])
// 	{
// 		if (iter[i][ft_strlen(iter[i]) - 1] != '/')
// 		{
// 			temp = ft_strjoin(tools->paths[i], "/");
// 			free(tools->paths[i]);
// 			tools->paths[i] = ft_strdup(temp);
// 			free(temp);
// 		}
// 		i++;
// 	}
// }

// int	get_paths(t_main_tools *tools)
// {
// 	t_env	*temp;

// 	temp = tools->envp_cpy;
// 	while (temp)
// 	{
// 		if (ft_strncmp(temp->name, "PATH", 4) == 0)
// 			tools->paths = ft_split(temp->value, ':');
// 		temp = temp->next;
// 	}
// 	if (tools->paths != NULL)
// 		add_slash(tools);
// 	return (EXIT_SUCCESS);
// }

// int	count_envp(t_env *envp_cpy)
// {
// 	int		i;

// 	i = 0;
// 	while (envp_cpy)
// 	{
// 		i++;
// 		envp_cpy = envp_cpy->next;
// 	}
// 	return (i);
// }

// /// @title Convert environment linked list to 2D array 
// /// @notice Function converts the environment linked list to a 2D array for execve format
// /// @dev We use it in the beginning of main and everytime we change the environment (now just in cd)

// void	convert_to_2d(t_main_tools *tools)
// {
// 	int		i;
// 	int		envp_counter;
// 	char	*temp;
// 	char	*temp2;
// 	t_env	*envp_iter;

// 	i = 0;
// 	if (tools->env_2d != NULL)
// 		free_arr(tools->env_2d);
// 	envp_iter = tools->envp_cpy;
// 	envp_counter = count_envp(tools->envp_cpy);
// 	tools->env_2d = malloc(sizeof(char *) * (envp_counter + 1));
// 	while (envp_iter)
// 	{
// 		temp = ft_strjoin(envp_iter->name, "=");
// 		temp2 = ft_strjoin(temp, envp_iter->value);
// 		free(temp);
// 		tools->env_2d[i++] = ft_strdup(temp2);
// 		free(temp2);
// 		envp_iter = envp_iter->next;
// 	}
// 	tools->env_2d[i] = NULL;
// }

int	find_pwd(t_main_tools *tools)
{
	int	i;

	i = 0;
	while (tools->envp_cpy[i])
	{
		if (!ft_strncmp(tools->envp_cpy[i], "PWD=", 4))
			tools->pwd = ft_substr(tools->envp_cpy[i],
					4, ft_strlen(tools->envp_cpy[i]) - 4);
		if (!ft_strncmp(tools->envp_cpy[i], "OLDPWD=", 7))
			tools->old_pwd = ft_substr(tools->envp_cpy[i],
					7, ft_strlen(tools->envp_cpy[i]) - 7);
		i++;
	}
	return (1);
}

char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup("\0"));
}

int	parse_envp(t_main_tools *tools)
{
	char	*path_from_envp;
	int		i;
	char	*tmp;

	path_from_envp = find_path(tools->envp_cpy);
	tools->paths = ft_split(path_from_envp, ':');
	free(path_from_envp);
	i = 0;
	while (tools->paths[i])
	{
		if (ft_strncmp(&tools->paths[i][ft_strlen(tools->paths[i]) - 1],
			"/", 1) != 0)
		{
			tmp = ft_strjoin(tools->paths[i], "/");
			free(tools->paths[i]);
			tools->paths[i] = tmp;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	change_path(t_main_tools *tools)
{
	char	*tmp;
	size_t	buff_size;
	char	*pwd;

	buff_size = 1024;
	tmp = ft_strdup(tools->pwd);
	if (tools->old_pwd)
		free(tools->old_pwd);
	tools->old_pwd = tmp;
	if (tools->pwd)
		free(tools->pwd);
	pwd = malloc(buff_size * sizeof(char));
	tools->pwd = getcwd(pwd, buff_size);
}
