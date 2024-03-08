/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:10:32 by nandroso          #+#    #+#             */
/*   Updated: 2024/03/08 11:49:14 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_empty_cd(t_main_tools *tools, t_simple_cmd *cmd)
{
	char	*home_dir;

	(void)cmd;
	home_dir = getenv("HOME");
	if (home_dir == NULL)
	{
		ft_putstr_fd("Error: HOME not set", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (chdir(home_dir) == -1)
		return (EXIT_FAILURE);
	set_pwd(tools);
	return (EXIT_SUCCESS);
}

int	handle_tild_cd(t_main_tools *tools, t_simple_cmd *cmd)
{
	char	*home_dir;
	char 	*new_path;

	home_dir = getenv("HOME");
	if (home_dir == NULL)
	{
		ft_putstr_fd("Error: HOME not set", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	new_path = ft_strjoin(home_dir, cmd->str[1] + 1);
	if (chdir(new_path) == -1)
	{
		free(new_path);
		return (EXIT_FAILURE);
	}
	set_pwd(tools);
	free(new_path);
	return (EXIT_SUCCESS);
}

int	msh_cd(t_main_tools *tools, t_simple_cmd *cmd)
{
	char	*error_msg;

	error_msg = "cd: no such file or directory: ";
	tools->old_pwd = tools->pwd;
	if (cmd->str[1] == NULL)
		handle_empty_cd(tools, cmd);
	else if (cmd->str[1][0] == '~')
		handle_tild_cd(tools, cmd);
	else
	{
		if(chdir(cmd->str[1]) == -1)
		{
			write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
			write(STDERR_FILENO, cmd->str[1], ft_strlen(cmd->str[1]));
			write(STDERR_FILENO, "\n", 1);
			return (EXIT_FAILURE);
		}
		set_pwd(tools);
	}
	change_env(tools, "OLDPWD", tools->old_pwd);
	change_env(tools, "PWD", tools->pwd);
	return (EXIT_SUCCESS);
}
