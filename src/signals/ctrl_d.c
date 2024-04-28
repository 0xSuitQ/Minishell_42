/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 14:57:11 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 15:01:14 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	Ctrl + D signal handler
*/
void	ctrl_d(void)
{
	ft_putstr_fd("exit\n", STDOUT);
	exit_minishell(NULL, 2);
}
