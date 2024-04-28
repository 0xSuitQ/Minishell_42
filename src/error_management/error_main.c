/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:23:21 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 21:57:37 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	Setting these members to NULL is a way to ensure that the structure starts
	in a known state, preventing undefined behavior from uninitialized pointers
	get_paths is used to get the paths from the environment variable, and
	adding them to the main_tools structure
*/
void	tools_to_default_setting(t_main_tools *tools)
{
	tools->lexer_list = NULL;
	tools->paths = NULL;
	tools->simple_cmd_list = NULL;
	tools->pipes = 0;
	tools->pid = NULL;
	tools->exit_status = 0;
	tools->error_type = 0;
}

int	error_police(int err_code, t_main_tools *tools)
{
	if (err_code == 1)
	{
		clear_all(tools);
		exit (EXIT_SUCCESS);
	}
	else if (err_code == 2)
		clear_for_continue(tools);
	if (err_code == 3)
	{
		clear_all(tools);
		exit (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
