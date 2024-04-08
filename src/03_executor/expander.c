/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:19:08 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/07 18:53:00 by psimcak          ###   ########.fr       */
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

/**
	@brief:
	Checks if there is a dollar sign in the string
*/
int	there_is_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
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
		if (TRUE == there_is_dollar(curr_simple_cmd))
		{
			handle_backslash_dollar(curr_simple_cmd);
			// expnad_dollar(curr_simple_cmd);
		}
		// else if (FALSE == there_is_dollar(curr_simple_cmd))
		// {
		// 	handle_backslashes(curr_simple_cmd);
		// }
	}
}
