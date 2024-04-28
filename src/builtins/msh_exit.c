/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:49:16 by peta              #+#    #+#             */
/*   Updated: 2024/04/28 19:15:35 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	check if the string is a number and return TRUE or FALSE
*/
static int	is_num(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
		if (str[i] >= '0' && str[i] <= '9')
			return (TRUE);
	return (FALSE);
}

int	error_in_msh_exit(char **args)
{
	ft_putstr_fd("minishell: exit: ", STDERR);
	ft_putstr_fd(args[1], STDERR);
	ft_putstr_fd(": numeric argument required\n", STDERR);
	return (2);
}

/**
	@brief:
	Exit the minishell, but before that, check if the argument is a number
	and if it is, convert it to an integer and exit with that number
*/
int	msh_exit(t_main_tools *tools, t_simple_cmd *cmd)
{
	char	**args;
	int		exit_status;
	int		arg_count;

	args = cmd->str;
	exit_status = 0;
	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	ft_putstr_fd("exit\n", STDOUT);
	if (arg_count > 2 && is_num(args[1]) == TRUE)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		tools->exit_status = 1;
		return (exit_status);
	}
	else if (arg_count >= 2 && is_num(args[1]) == FALSE)
		exit_status = error_in_msh_exit(args);
	else if (arg_count == 2 && is_num(args[1]) == TRUE)
		exit_status = ft_atoi(args[1]) % 256;
	exit_minishell(tools, exit_status);
	return (exit_status);
}
