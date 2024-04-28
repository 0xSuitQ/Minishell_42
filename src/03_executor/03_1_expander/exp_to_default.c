/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_to_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 13:11:31 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 13:12:25 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
	@brief:
	exp_to_default function sets the expander structure to default vlalues
	its called ones before the expansion starts
*/
void	exp_to_default(t_expander *exp)
{
	exp->first = NULL;
	exp->second = NULL;
	exp->tmp_1 = NULL;
	exp->tmp_2 = NULL;
	exp->final = NULL;
	exp->exp_list = NULL;
	exp->i = -1;
}
