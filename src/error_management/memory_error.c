/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:55:00 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 19:15:34 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
    @brief:
    memory_error function is used to handle memory allocation errors
    and print an error message to the standard error output
*/
void	memory_error(void *ptr, t_main_tools *tls, int err, t_simple_cmd *cmd)
{
	if (!ptr && err == 1)
	{
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR);
		error_police(2, tls);
	}
	if (!ptr && err == 2)
	{
		free(cmd);
		ft_putstr_fd("memory error: unable to assign memory\n", STDERR);
		error_police(2, tls);
	}
	else
		return ;
}
