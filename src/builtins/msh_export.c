/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:46:13 by nandroso          #+#    #+#             */
/*   Updated: 2024/03/08 14:30:57 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	msh_export(t_main_tools *tools, t_simple_cmd *cmd)
// {
// 	int	i;

// 	i = 1;
// 	if (cmd->str[1] == NULL)
// 		msh_env(tools, cmd);
// 	else
// 	{
// 		while (cmd->str[i])
// 		{
// 			if (ft_strchr(cmd->str[i], '='))
// 				change_env();
// 			else
// 				ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
// 		}
// 	}
// }