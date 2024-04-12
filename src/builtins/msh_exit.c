/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:49:16 by peta              #+#    #+#             */
/*   Updated: 2024/04/12 19:40:29 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_minishell(t_data *data, int exit_num)
{
	static t_data	*static_data;
	int				exit_status;

	if (!static_data)
		static_data = data;
	else
	{
		static_data->exit_status = exit_num;
		exit_status = static_data->exit_status;
		free_data(static_data);
		exit(exit_status);
	}
}

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

void	ft_exit(t_simple_cmd *s_cmd)
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
		data->exit_status = 1;
		return ;
	}
	else if (arg_count >= 2 && is_num(args[1]) == FALSE)
	{
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putstr_fd(": numeric argument required\n", STDERR);
		exit_status = 2;
	}
	else if (arg_count == 2)
		exit_status = ft_atoi(args[1]) % 256;
	exit_minishell(data, exit_status);
}
