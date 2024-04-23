// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   msh_export.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/08 12:46:13 by nandroso          #+#    #+#             */
// /*   Updated: 2024/04/23 19:53:07 by nandroso         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/minishell.h"

// /**
// 	@brief Export environment variables or display the current environment
// 	variables.
// 	This function is responsible for exporting environment variables to the
// 	environment variables list or displaying the current environment variables.
	
// 	- If no arguments are provided, it displays the current environment
// 	variables.
// 	- While arguments are provided, it validates each argument and adds it to
// 	the environment variables if it is valid.
// 	- If the argument contains an '=', it splits the argument into name and
// 	value and adds || modifies the env variable. Then free the split array.
// 	- If an argument is not a valid identifier, it displays an error message and
// 	returns an error status.
//  */

// int	msh_export(t_main_tools *tools, t_simple_cmd *cmd)
// {
// 	int		i;
// 	char	**split;

// 	i = 0;
// 	if (!cmd->str[1])
// 		msh_env(tools, cmd);
// 	else
// 	{
// 		while (cmd->str[++i])
// 		{
// 			if (ft_strchr(cmd->str[i], '='))
// 			{
// 				split = ft_split(cmd->str[i], '=');
// 				tools->envp_cpy->name = ft_strdup(split[0]);
// 				change_env(tools, split[0], split[1]);
// 				free(split[0]);
// 				free(split[1]);
// 				free(split);
// 			}
// 			else
// 				ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
// 		}
// 	}
// 	return (EXIT_SUCCESS);
// }
