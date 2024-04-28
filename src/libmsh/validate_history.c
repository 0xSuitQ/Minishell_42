/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:02:21 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 15:04:50 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	validates the history of the commands
*/
void	validate_history(char *args)
{
	int		flag;

	flag = 0;
	if (ft_strstr(args, "<<") != NULL)
		flag = 1;
	if (flag == 0)
		add_history(args);
}
