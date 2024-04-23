/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:10:56 by nandroso          #+#    #+#             */
/*   Updated: 2024/04/23 17:46:17 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	Print the environment variables
	The logic is:
	1. Get the environment variables from the tools
	2. Iterate through the environment variables
	3. Print the environment variables
	4. Return EXIT_SUCCESS
*/
int msh_env(t_main_tools *tools, t_simple_cmd *cmd)
{
	int		i;

	(void) cmd;
	i = 0;
	while (tools->envp_cpy[i])
	{
		ft_putendl_fd(tools->envp_cpy[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);

}
