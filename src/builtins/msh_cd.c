/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:10:32 by nandroso          #+#    #+#             */
/*   Updated: 2024/04/25 23:13:28 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path_ret(char *str, t_main_tools *tools)
{
	int	i;

	i = 0;
	while (tools->envp_cpy[i])
	{
		if (!ft_strncmp(tools->envp_cpy[i], str, ft_strlen(str)))
			return (ft_substr(tools->envp_cpy[i], ft_strlen(str),
					ft_strlen(tools->envp_cpy[i]) - ft_strlen(str)));
		i++;
	}
	return (NULL);
}

int	specific_path(t_main_tools *tools, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path_ret(str, tools);
	ret = chdir(tmp);
	free(tmp);
	if (ret != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}

void	add_path_to_env(t_main_tools *tools)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tools->envp_cpy[i])
	{
		if (!ft_strncmp(tools->envp_cpy[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", tools->pwd);
			free(tools->envp_cpy[i]);
			tools->envp_cpy[i] = tmp;
		}
		else if (!ft_strncmp(tools->envp_cpy[i], "OLDPWD=", 7)
			&& tools->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", tools->old_pwd);
			free(tools->envp_cpy[i]);
			tools->envp_cpy[i] = tmp;
		}
		i++;
	}
}

int	msh_cd(t_main_tools *tools, t_simple_cmd *simple_cmd)
{
	int		ret;

	if (!simple_cmd->str[1])
		ret = specific_path(tools, "HOME=");
	else if (ft_strncmp(simple_cmd->str[1], "-", 1) == 0)
		ret = specific_path(tools, "OLDPWD=");
	else
	{
		ret = chdir(simple_cmd->str[1]);
		if (ret != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(simple_cmd->str[1], STDERR_FILENO);
			perror(" ");
		}
	}
	if (ret != 0)
		return (EXIT_FAILURE);
	change_path(tools);
	add_path_to_env(tools);
	return (EXIT_SUCCESS);
}
