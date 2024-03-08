/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:11:03 by nandroso          #+#    #+#             */
/*   Updated: 2024/03/05 10:11:05 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int msh_pwd(t_main_tools *tools, t_simple_cmd *cmd)
{
	(void)cmd;
	ft_putstr_fd(tools->pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
