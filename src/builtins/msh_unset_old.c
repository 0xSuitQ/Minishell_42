// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   msh_unset.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/04/17 19:44:39 by peta              #+#    #+#             */
// /*   Updated: 2024/04/25 21:49:04 by psimcak          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// void	env_remove(t_env **envp, char *name)
// {
// 	t_env	*tmp;
// 	t_env	*prev;

// 	tmp = *envp;
// 	prev = NULL;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(tmp->name, name) == 0)
// 		{
// 			if (prev == NULL)
// 				*envp = tmp->next;
// 			else
// 				prev->next = tmp->next;
// 			free(tmp->name);
// 			free(tmp->value);
// 			free(tmp);
// 			return ;
// 		}
// 		prev = tmp;
// 		tmp = tmp->next;
// 	}
// }

// /**
// 	@brief Removes a variable from the environment variable linked list.
// 	This function removes one or more variables from the linked list of
// 	environment variables.
// 	If no variables are provided, the function exits
// 	with a status of 0. Otherwise, it iterates through the provided variable
// 	names and removes them from the environment variable list.
//  */

// int	msh_unset(t_main_tools *tools, t_simple_cmd *s_cmd)
// {
// 	t_env	*envp;
// 	int		counter;

// 	envp = tools->envp_cpy;
// 	counter = 0;
// 	while (s_cmd->str[counter])
// 		counter++;
// 	if (counter == 1)
// 	{
// 		tools->exit_status = 0;
// 		return (EXIT_SUCCESS);
// 	}
// 	counter = 0;
// 	while (s_cmd->str[++counter])
// 		env_remove(&envp, s_cmd->str[counter]);
// 	tools->exit_status = 0;
// 	return (EXIT_SUCCESS);
// }
