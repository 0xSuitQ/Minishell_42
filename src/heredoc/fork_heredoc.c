/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:10 by peta              #+#    #+#             */
/*   Updated: 2024/04/30 11:46:50 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief	Prints an error message when a fork creation fails.
*/
void	fork_process(int *pid, t_main_tools *tools)
{
	*pid = fork();
	if (*pid == -1)
	{
		ft_putendl_fd("minishell: fork: Resource temporarily unavailable", 2);
		clear_for_continue(tools);
	}
}
