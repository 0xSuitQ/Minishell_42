/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:10:32 by nandroso          #+#    #+#             */
/*   Updated: 2024/04/23 18:36:51 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// /**
// 	@brief:
// 	handle_empty_cd function is used to handle the cd command when the user
// 	does not specify any directory. It changes the current working directory
// 	to the user's home directory.
// */
// int	handle_empty_cd(t_main_tools *tools, t_simple_cmd *cmd)
// {
// 	char	*home_dir;

// 	(void)cmd;
// 	home_dir = getenv("HOME");
// 	if (home_dir == NULL)
// 	{
// 		ft_putstr_fd("Error: HOME not set", STDERR_FILENO);
// 		return (EXIT_FAILURE);
// 	}
// 	if (chdir(home_dir) == -1)
// 		return (EXIT_FAILURE);
// 	set_pwd(tools);
// 	return (EXIT_SUCCESS);
// }

// /**
// 	@brief:
// 	Handle the cd command when the user specifies the home directory.
// */
// int	handle_tild_cd(t_main_tools *tools, t_simple_cmd *cmd)
// {
// 	char	*home_dir;
// 	char 	*new_path;

// 	home_dir = getenv("HOME");
// 	if (home_dir == NULL)
// 	{
// 		ft_putstr_fd("Error: HOME not set", STDERR_FILENO);
// 		return (EXIT_FAILURE);
// 	}
// 	new_path = ft_strjoin(home_dir, cmd->str[1] + 1);
// 	if (chdir(new_path) == -1)
// 	{
// 		free(new_path);
// 		return (EXIT_FAILURE);
// 	}
// 	set_pwd(tools);
// 	free(new_path);
// 	return (EXIT_SUCCESS);
// }

// /**
// 	@brief:
// 	cd is a built-in command that changes the current working directory.
// 	If no directory is specified, the command changes to the user's home directory.
// 	If the directory does not exist, the command returns an error message.
// */
// int	msh_cd(t_main_tools *tools, t_simple_cmd *cmd)
// {
// 	char	*error_msg;

// 	error_msg = "cd: no such file or directory: ";
// 	ft_strcpy(tools->old_pwd, tools->pwd);
// 	if (cmd->str[1] == NULL)
// 		handle_empty_cd(tools, cmd);
// 	else if (cmd->str[1][0] == '~')
// 		handle_tild_cd(tools, cmd);
// 	else
// 	{
// 		if(chdir(cmd->str[1]) == -1)
// 		{
// 			write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
// 			write(STDERR_FILENO, cmd->str[1], ft_strlen(cmd->str[1]));
// 			write(STDERR_FILENO, "\n", 1);
// 			return (EXIT_FAILURE);
// 		}
// 		set_pwd(tools);
// 	}
// 	change_env(tools, "OLDPWD", tools->old_pwd);
// 	change_env(tools, "PWD", tools->pwd);
	
// 	convert_to_2d(tools);
// 	return (EXIT_SUCCESS);
// }


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
