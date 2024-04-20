/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:49:16 by peta              #+#    #+#             */
/*   Updated: 2024/04/17 17:01:35 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// TODO
void	set_to_null(t_main_tools *data)
{
	data->lexer_list = NULL;
	data->simple_cmd_list = NULL;
	data->pid = NULL;
}

// TODO
void	free_data(t_main_tools *tools)
{
	if (tools->pid)
		free(tools->pid);
	set_to_null(tools);
	// clear_all(tools);
}

/**
	@brief:
	Exit the minishell with the given exit number and free all the data
*/
void	exit_minishell(t_main_tools *tools, int exit_num)
{
	static t_main_tools	*static_tools;

	if (!static_tools)
		static_tools = tools;
	// else
	// {
	// 	static_tools->exit_status = exit_num;
	// 	free_data(static_tools);
	// 	exit(static_tools->exit_status);
	// }
	static_tools->exit_status = exit_num;
	free_data(static_tools);
	exit(static_tools->exit_status);
}

/**
	@brief:
	check if the string is a number and return TRUE or FALSE
*/
static int	is_num(char *str)
{
	int		i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
		if (str[i] >= '0' && str[i] <= '9')
			return (TRUE);
	return (FALSE);
}

/**
	@brief:
	Exit the minishell, but before that, check if the argument is a number
	and if it is, convert it to an integer and exit with that number
*/
int	msh_exit(t_main_tools *tools, t_simple_cmd *s_cmd)
{
	char	**args;
	int		exit_status;
	int		arg_count;

	args = s_cmd->str;
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
	{
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putstr_fd(": numeric argument required\n", STDERR);
		exit_status = 2;
	}
	else if (arg_count == 2 && is_num(args[1]) == TRUE)
		exit_status = ft_atoi(args[1]) % 256;
	exit_minishell(tools, exit_status);
	return (exit_status);
}
