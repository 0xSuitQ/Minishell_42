/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_buildin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:14:46 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 13:14:57 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief:
	check_builtin is a function that will check if the command is a built-in
	command.
	->	If it IS a built-in command, it will execute it and return the exit_
		status of the command (EXIT_SUCCESS (or - for msh_cd - EXIT_FAILURE))
	->	If it is NOT a built-in command, it will return EXIT_FAILURE.
*/
int	check_builtin(t_main_tools *tools, t_simple_cmd *cmd)
{
	if (cmd->builtin == msh_pwd || cmd->builtin == msh_export
		|| cmd->builtin == msh_cd || cmd->builtin == msh_env
		|| cmd->builtin == msh_exit || cmd->builtin == msh_unset)
	{
		tools->exit_status = cmd->builtin(tools, cmd);
		return (1);
	}
	return (0);
}
