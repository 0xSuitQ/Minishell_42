/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:09:11 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 13:09:17 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	free_list function frees the list
*/
void	free_list(t_list *exp_list)
{
	t_list	*tmp;

	while (exp_list)
	{
		tmp = exp_list;
		exp_list = exp_list->next;
		free(tmp->content);
		free(tmp);
	}
}
