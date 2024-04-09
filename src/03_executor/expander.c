/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:19:08 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/09 20:22:10 by peta             ###   ########.fr       */
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
	- clear_env_variable function prepare the pure env-variable
	- $USER$USER		-> USER
	- $USER\$USER		-> USER
	only first env-variable is returned, rest is solved in other iterations
*/
char	*clear_env_variable(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] > 'A' && str[i] < 'Z')
		i++;
	tmp = ft_substr(str, 0, i);
	return (tmp);
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
	char	*env_expanded;
	char	*result;
	char	*after_pure;
	char	*pure;

	if (!str[0])
		return ;
	result = ft_substr(str, 0, 0);
	pure = clear_env_variable(&str[1]);
	after_pure = ft_strdup(&str[1]);
	env_expanded = getenv(pure);
	if (env_expanded)
	{
		result = ft_strjoin(result, env_expanded);
		result = ft_strjoin(result, after_pure + ft_strlen(env_expanded));
		ft_strlcpy(str, result, ft_strlen(result) + 1);
		free(result);
	}
	if (pure[0] == '?')
	{
		// result = ft_itoa(g_exit_status);
		result = ft_strjoin(result, after_pure + 1);
		ft_strlcpy(str, result, ft_strlen(result) + 1);
		free(result);
	}
	free(after_pure);
}

/*
	@brief:
	handle_dollar function handles the dollar sign in the string
	- if there is a \ before the $, \ will be removed and $ skipped
	- if there is a \ after the $, $ will be skipped and \ will be removed
	- if there is a $, it will be expanded
*/
char	*handle_dollar(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strdup(str);
	while (tmp[++i])
	{
		if (tmp[i] == '\\' && tmp[i + 1] == '$')
		{
			ft_strlcpy(&tmp[i], &tmp[i + 1], ft_strlen(&tmp[i + 1]) + 1);
			i++;
		}
		if (tmp[i] == '$' && tmp[i + 1] == '\\')
		{
			i++;
			ft_strlcpy(&tmp[i], &tmp[i + 1], ft_strlen(&tmp[i + 1]) + 1);
		}
		if (tmp[i] == '$')
		{
			expand_dollar(&tmp[i]);
		}
	}
	return (tmp);
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
	int		i;
	char	**expanded_str;

	i = 0;
	while (curr_simple_cmd->str[i])
		i++;
	expanded_str = malloc((i + 1) * sizeof(char*));
	if (!expanded_str)
		exit(1);
    expanded_str[i] = NULL;
	i = -1;
	while (curr_simple_cmd->str[++i])
	{
		expanded_str[i] = handle_dollar(curr_simple_cmd->str[i]);
		// handle_single_quotes(curr_simple_cmd->str[i]);
	}
	free_arr(curr_simple_cmd->str);
	curr_simple_cmd->str = expanded_str;

	// int j = -1;
	// printf("final: ");
	// while (++j < i)
	// 	printf("%s ", curr_simple_cmd->str[j]);
	// printf("\n");
}
