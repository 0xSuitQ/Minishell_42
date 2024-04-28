/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:07:25 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 13:07:33 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	list_to_array function converts the list to an array
*/
char	*list_to_array(t_list *exp_list)
{
	t_list	*tmp;
	char	*result;
	char	*joined_result;

	tmp = exp_list;
	result = ft_strdup(tmp->content);
	tmp = tmp->next;
	while (tmp)
	{
		joined_result = ft_strjoin(result, tmp->content);
		free(result);
		result = joined_result;
		tmp = tmp->next;
	}
	free_list(exp_list);
	return (result);
}
