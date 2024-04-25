/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:46:13 by nandroso          #+#    #+#             */
/*   Updated: 2024/04/25 23:14:08 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief Export environment variables or display the current environment
	variables.
	This function is responsible for exporting environment variables to the
	environment variables list or displaying the current environment variables.
	
	- If no arguments are provided, it displays the current environment
	variables.
	- While arguments are provided, it validates each argument and adds it to
	the environment variables if it is valid.
	- If the argument contains an '=', it splits the argument into name and
	value and adds || modifies the env variable. Then free the split array.
	- If an argument is not a valid identifier, it displays an error message and
	returns an error status.
 */

char static	**helper(char **arr, char **mem, char *str)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i + 1] == NULL)
		{
			mem[i] = ft_strdup(str);
			mem[i + 1] = ft_strdup(arr[i]);
		}
		else
			mem[i] = ft_strdup(arr[i]);
		if (mem[i] == NULL)
		{
			free_arr(mem);
			return (mem);
		}
		i++;
	}
	return (mem);
}


char	**rewrite_envp(char **arr, char *str)
{
	char	**mem;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	mem = ft_calloc(sizeof(char *), i + 2);
	if (!mem)
		return (NULL);
	mem = helper(arr, mem, str);
	return (mem);
}

int	msh_export(t_main_tools *tools, t_simple_cmd *cmd)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!cmd->str[1])
		msh_env(tools, cmd);
	while (cmd->str[++i])
	{
		printf("cmd->str[%d]: %s\n", i, cmd->str[i]);
		if (ft_strchr(cmd->str[i], '='))
		{
			tmp = rewrite_envp(tools->envp_cpy, cmd->str[i]);
			free_arr(tools->envp_cpy);
			if (tools->envp_cpy)
				write(2, "we are here\n", 12);
			tools->envp_cpy = tmp;
		}
		else
			ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
	}
	int j = 0;
	write(2, "still here\n", 12);
	while (tools->envp_cpy[j])
	{
		write(2, tools->envp_cpy[j], ft_strlen(tools->envp_cpy[j]));
		write(2, "\n", 1);
		j++;
	}
	return (EXIT_SUCCESS);
}
