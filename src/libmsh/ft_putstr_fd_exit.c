/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:38:48 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/25 23:17:37 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	ft_putstr_fd_exit is a function that will print a message to the specified
	file descriptor and exit the program with the specified exit number
*/
void	ft_putstr_fd_exit(char *message, int fd_num, int exit_num)
{
	ft_putstr_fd(message, fd_num);
	exit(exit_num);
}
