/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandroso <nandroso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:44:39 by peta              #+#    #+#             */
/*   Updated: 2024/04/30 18:33:41 by nandroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	- equal_sign function finds the index of the equal sign in the string
	- if the equal sign is found, it returns the index of the equal sign
	- if the equal sign is not found, it returns 0
*/
size_t	equal_sign(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			if (str[i + 1] == '\0')
				return (i + 1);
			else
				return (i);
		}
	}
	return (0);
}

/**
	@brief:
	- whileloop_del_var function goes through the array and if the variable is
	found, it is deleted
	- the new array is returned
*/
char	**whileloop_del_var(char **arr, char **rtn, char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (arr[++i] != NULL)
	{
		if (!(ft_strncmp(arr[i], str, equal_sign(arr[i]) - 1) == 0
				&& str[equal_sign(arr[i])] == '\0'
				&& arr[i][ft_strlen(str)] == '='))
		{
			rtn[j] = ft_strdup(arr[i]);
			if (rtn[j] == NULL)
			{
				free_arr(rtn);
				return (rtn);
			}
			j++;
		}
	}
	return (rtn);
}

/**
	@brief:
	- del_var function deletes the environment variable
	- it goes through the array and if the variable is found, it is deleted
	- the new array is returned
*/
char	**del_var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	rtn = whileloop_del_var(arr, rtn, str);
	return (rtn);
}

/**
	@brief:
	- unset_error function checks if the unset command has the correct number of
	arguments
	- if the number of arguments is correct, it returns 0 = EXIT_SUCCESS
	- if the number of arguments is incorrect, it returns 1 = EXIT_FAILURE
*/
int	unset_error(t_simple_cmd *simple_cmd)
{
	int		i;

	i = 0;
	if (!simple_cmd->str[1])
	{
		ft_putendl_fd("minishell: unset: not enough arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (simple_cmd->str[1][i])
	{
		if (simple_cmd->str[1][i++] == '/')
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(simple_cmd->str[1], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	if (equal_sign(simple_cmd->str[1]) != 0)
	{
		ft_putendl_fd("minishell: unset: not a valid identifier",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
	@brief:
	Unset the environment variable
*/
int	msh_unset(t_main_tools *tools, t_simple_cmd *simple_cmd)
{
	char	**tmp;

	if (unset_error(simple_cmd) == 1)
		return (EXIT_FAILURE);
	else
	{
		tmp = del_var(tools->envp_cpy, simple_cmd->str[1]);
		free_arr(tools->envp_cpy);
		tools->envp_cpy = tmp;
	}
	return (EXIT_SUCCESS);
}
