/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:29:37 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/22 13:29:22 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
	
void	tester(t_main_tools *tools, int signpost);

int		there_is_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (1);
	}
	return (0);
}

/*

*/
void	expander(t_main_tools *tools)
{
	t_simple_cmd	*current_cmd;
	int				i;

	current_cmd = tools->simple_cmd_list;
	while (current_cmd)
	{
		i = -1;
		while(current_cmd->str[++i])
		{
			if (there_is_dollar(current_cmd->str[i]))
			{
				tester(tools, EXPANDER);
			}
		}
		current_cmd = current_cmd->next;
	}
}
