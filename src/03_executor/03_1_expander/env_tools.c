/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:54:39 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/22 18:54:41 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
	@brief:
	- clear_env_variable function prepare the pure env-variable
	- $CONDA_EXE$USER		-> CONDA_EXE
	- $USER\$USER			-> USER
	only first env-variable is returned, rest is solved in other iterations
*/
char	*clear_env_variable(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] && ((str[i] >= 'A' && str[i] <= 'Z') ||
		(str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9') ||
		str[i] == '_' || str[i] == '?'))
		i++;
	tmp = ft_substr(str, 0, i);
	return (tmp);
}

/**
	@brief:
	env_not_valid function checks if the env-variable is valid
	- if the env-variable is not valid, it returns 1
	- if the env-variable is valid, it returns 0
*/
int	env_not_valid(char *str)
{
	char	*pure;

	pure = clear_env_variable(&str[1]);
	if (!getenv(pure))
		return (TRUE);
	return (FALSE);
}
