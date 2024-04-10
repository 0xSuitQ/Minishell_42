/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:19:08 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/10 20:19:31 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	int		pure_len;

	if (!str[0])
		return ;
	result = ft_substr(str, 0, 0);
	pure = clear_env_variable(&str[1]);
	pure_len = ft_strlen(pure);
	after_pure = ft_strdup(&str[pure_len + 1]);
	env_expanded = getenv(pure);
	if (env_expanded)
	{
		result = ft_strjoin(result, env_expanded);
		result = ft_strjoin(result, pure + ft_strlen(env_expanded));
		result = ft_strjoin(result, after_pure);
		ft_strlcpy(str, result, ft_strlen(result) + 1);
		free(result);
	}
	if (pure[0] == '?')
	{
		// result = ft_itoa(g_exit_status);
		result = ft_strjoin(result, pure + 1);
		result = ft_strjoin(result, after_pure);
		ft_strlcpy(str, result, ft_strlen(result) + 1);
		free(result);
	}
	if (env_expanded == NULL)
		ft_strlcpy(str, after_pure, ft_strlen(after_pure) + 1);
	free(after_pure);
}

/*
	@brief:
	handle_backslash function handles the backslash in the string
	- if there is a \ before the $, \ will be removed and $ skipped
	- if there is a \ after the $, $ will be skipped and \ will be removed
	- if there are two \, one will be removed
	- if there is only one \, it will be removed
*/
int	handle_backslash(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '\\' && str[i + 1] == '$')
	{
		ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
		i++;
	}
	if (str[i] == '$' && str[i + 1] == '\\')
	{
		i++;
		ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
	}
	if (str[i] == '\\' && str[i + 1] == '\\')
	{
		ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
		i++;
	}
	if (str[i] == '\\')
		ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
	return (i);
}

/**
	@brief:
	remove_quotes function removes the quotes from the string
	- it goes through the string and if there is a quote, it will be removed
	both: at the beggining and at the end
	@param:
	- str: string from which the quotes will be removed
	- quote_type: type of the quote, which will be removed
*/
void	remove_quotes(char *str, char quote_type)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == quote_type)
		{
			j = 1;
			while (str[i + j] != quote_type)
				j++;
			ft_strlcpy(&str[i], &str[i + 1], j);
			break;
		}
		i++;
	}
}

/**
	@brief:
	quotes_classifier function classifies the quotes in the string
	- if there is a single quote, it returns SINGLE_Q
	- if there is a double quote, it returns DOUBLE_Q
	- if there are no quotes, it returns NO_Q
*/
int	quotes_classifier(char *str)
{
	int		i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (SINGLE_Q);
		if (str[i] == '\"')
			return (DOUBLE_Q);
		i++;
	}
	return (NO_Q);
}

/**
	@brief:
	handle_dollar function handles the dollar sign in the string
	it goes through the string and if there is a $, it will be expanded
*/
char	*handle_dollar(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strdup(str);
	while (tmp[++i])
	{
		if (quotes_classifier(&tmp[i]) == SINGLE_Q)
		{
			remove_quotes(&tmp[i], '\'');
			break;
		}
		remove_quotes(&tmp[i], '\"');
		i += handle_backslash(&tmp[i]);
		while (tmp[i] == '$')
			expand_dollar(&tmp[i]);
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
		expanded_str[i] = handle_dollar(curr_simple_cmd->str[i]);
	free_arr(curr_simple_cmd->str);
	curr_simple_cmd->str = expanded_str;
}
