/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:01:08 by nandroso          #+#    #+#             */
/*   Updated: 2024/04/25 23:17:29 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief Function to find the PWD and OLDPWD from the original envp
*/
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

/**
	@brief Function to find the path from the origo envp
*/
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

/**
	@brief Function to parse the envp and store the paths in the tools struct
*/
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

/**
	@brief Function to change the path of the shell to the new path
*/
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
