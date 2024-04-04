/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:19:08 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/04 20:38:25 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	@brief:
	Removes quotes and backslashes from the string
	
	Examples:
	\$USER -> $USER 
	$\USER -> $USER 
	"$\USER" -> $SER 
	'$\USER' -> $SER 
	"\$USER" -> $USER 
	'\$USER' -> \$USER
*/
void	remove_quotes_and_backslashes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '$')
		{
			str[j] = '$';
			i++;
		}
		else if (str[i] == '\\' && str[i + 1] == '\\')
		{
			str[j] = '\\';
			i++;
		}
		else if (str[i] == '\\' && str[i + 1] == '\'')
		{
			str[j] = '\'';
			i++;
		}
		else if (str[i] == '\\' && str[i + 1] == '\"')
		{
			str[j] = '\"';
			i++;
		}
		else
			str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
}

/**
 * @brief:
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
void	expander(t_main_tools *tools)
{
	t_simple_cmd	*curr_simple_cmd;
	t_lexer			*curr_sub_lexer;
	int				i;

	curr_simple_cmd = tools->simple_cmd_list;
	while (curr_simple_cmd)
	{
		i = -1;
		curr_sub_lexer = curr_simple_cmd->lexer_list;
		while (curr_sub_lexer)
		{
			if (TRUE == there_is_dollar(curr_sub_lexer->sub_str))
			{
				// TODO
			}
			else if (FALSE == there_is_dollar(curr_sub_lexer->sub_str))
			{
				remove_quotes_and_backslashes(curr_sub_lexer->sub_str);
			}
			curr_sub_lexer = curr_sub_lexer->next;
		}
		curr_simple_cmd = curr_simple_cmd->next;
	}
}
