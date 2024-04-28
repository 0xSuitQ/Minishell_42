/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:59:20 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 19:15:36 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	set_pwd function is used to set the current working directory
	in the main_tools structure
*/
void	set_pwd(t_main_tools *tools)
{
	char	*pwd;
	size_t	buf_size;

	if (tools->pwd)
		free(tools->pwd);
	buf_size = 1024;
	pwd = malloc(sizeof(char) * buf_size);
	if (!pwd)
	{
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR_FILENO);
		error_police(2, tools);
	}
	while (getcwd(pwd, buf_size) == NULL)
	{
		free(pwd);
		buf_size *= 2;
		pwd = malloc(sizeof(char) * buf_size);
		if (!pwd)
		{
			ft_putstr_fd("memory error: unable to assign memory\n",
				STDERR_FILENO);
			error_police(2, tools);
		}
	}
	tools->pwd = pwd;
}
