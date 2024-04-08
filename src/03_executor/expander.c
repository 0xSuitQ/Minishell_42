/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:19:08 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/08 18:44:16 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	Handles quotes and backslashes from the string
	
	Examples:
	$USER		-> psimcak
	'$USER'		-> $USER
	"$USER"		-> psimcak
	$NONEXIST	-> [empty]
	backslash part:
	\$USER		-> $USER
	$\USER		-> $USER 
	"$\USER"	-> $SER 
	'$\USER'	-> $SER 
	"\$USER"	-> $USER
	'\$USER'	-> \$USER
	special symbol:
	$?			-> exit status of the most recently executed foreground pipeline
*/

/**
	@brief:
	handle_backslash_dollar function handles the backslash and dollar sign only
	\$USER			-> $USER
	\$USER$USER		-> $USERpsimcak
*/
void	handle_backslash_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\\' && str[i + 1] == '$')
		{
			ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
		}
		if (str[i] == '$')
		{
			expand_dollar(str);
		}
	}
}

/*
	@brief:
	- expand_dollar function expands the dollar sign and the env-variable
	- it take the string till the $ and join it with the environment variable
	- the power is, that it works only for one $, so if there are more $, which 
	have for exaple backslash before, it will not work for them
	- from handle_dollar we send the string beggining with $
	$USER\$USER		-> psimcak\$USER
*/
void	expand_dollar(char *str)
{
	int		i;
	char	*env_var;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return ;
	tmp = ft_substr(str, 0, i);
	tmp2 = ft_strdup(&str[i + 1]);
	env_var = getenv(tmp2);
	if (env_var)
	{
		tmp = ft_strjoin(tmp, env_var);
		tmp = ft_strjoin(tmp, tmp2 + ft_strlen(env_var));
		ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
		free(tmp);
	}
	else
		ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
	free(tmp2);
}

void	handle_dollar(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strdup(str);
	while (tmp[++i])
	{
		// ************************************************************
		printf("EXECUTER - string is: %s\n", tmp);
		printf("EXECUTER - iteration: %s\n", &tmp[i]);
		// ************************************************************
		if (tmp[i] == '\\' && tmp[i + 1] == '$')
		{
			ft_strlcpy(&tmp[i], &tmp[i + 1], ft_strlen(&tmp[i + 1]) + 1);
			i++;
		}
		if (tmp[i] == '$')
		{
			expand_dollar(tmp);
		}
	}
}

/**
 * @brief:
	The expander is responsible for expanding special characters and variables
	within the user's command input. Its primary purpose is to handle the
	expansion of dollar signs ($) and their associated environment variables or
	special symbols (e.g., $? for the exit status of the last command).

	When a user enters a command like echo $USER, the expander's job is to
	replace $USER with the actual value of the USER environment variable before
	executing the command

	Main tasks:
	- expands environment variables (e.g., $USER)
	- removes quotes (single or double)
	- removes backslashes (\)

	Example:
	echo $USER > "test.txt" | cat test.txt
*/
void	expander(t_simple_cmd *curr_simple_cmd)
{
	int	i;

	i = -1;
	while (curr_simple_cmd->str[++i])
	{
		handle_dollar(curr_simple_cmd->str[i]);
		// handle_single_quotes(curr_simple_cmd->str[i]);
	}
}
