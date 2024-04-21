/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:19:08 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/21 15:40:27 by peta             ###   ########.fr       */
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

/**
	@brief:
	- ft_str_replace function replaces the string with the new string
	- it allocates memory for the new string, copies the new string into it
	and frees the old string
*/
void	ft_str_replace(char **str, char *result)
{
	char *new_str;

	if (str == NULL || *str == NULL || result == NULL)
		return ;
	new_str = (char *)malloc(sizeof(char) * ft_strlen(result) + 1);
	if (new_str == NULL)
		return ;
	ft_strcpy(new_str, result);
	free(*str);
	*str = new_str;
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
int	expand_dollar(char *str)
{
	char	*env_expanded;
	char	*result;
	char	*after_pure;
	char	*pure;
	int		i;

	i = 0;
	if (!str[0])
		return (i);
	pure = clear_env_variable(&str[1]);
	after_pure = ft_strdup(&str[ft_strlen(pure) + 1]);
	env_expanded = getenv(pure);
	if (env_expanded)
	{
		result = ft_strjoin(env_expanded, after_pure);
		ft_str_replace(&str, result);
		// free(result);
	}
	else
		i++;
	if (pure[0] == '?')
	{
		// result = ft_itoa(g_exit_status);
		result = ft_strjoin(result, after_pure);
		ft_str_replace(&str, result);
		// free(result);
	}
	printf("1 - str: %s\n", str);
	free(after_pure);
	printf("2 - str: %s\n", str);
	free(pure);
	printf("3 - str: %s\n", str);
	return (i);
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

/**
	@brief:
	handle_dollar function handles the dollar sign in the string
	it goes through the string and if there is a $, it will be expanded
*/
char	*handle_dollar(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		printf("str[i]: %c\n", str[i]);
		if (quotes_classifier(&str[i]) == SINGLE_Q)
		{
			remove_quotes(&str[i], '\'');
			break;
		}
		remove_quotes(&str[i], '\"');
		i += handle_backslash(&str[i]);
		while (str[i] == '$')
		{
			if (env_not_valid(&str[i]))
				i++;
			printf("1 str[i]: %s\n", str);
			i += expand_dollar(&str[i]);
			printf("2 str[i]: %s\n", str);
		}
	}
	return (str);
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
	char	**tmp;

	i = 0;
	tmp = curr_simple_cmd->str;
	while (tmp[i])
		i++;
	expanded_str = malloc((i + 1) * sizeof(char*));
	if (!expanded_str)
		exit(1);
	expanded_str[i] = NULL;
	i = -1;
	while (tmp[++i])
	{
		printf("--------------------\n");
		printf("%i - tmp: %s\n", i, tmp[i]);
		expanded_str[i] = handle_dollar(tmp[i]);
		printf("%i - expanded_str: %s\n", i, tmp[i]);
	}
	free_arr(curr_simple_cmd->str);
	curr_simple_cmd->str = expanded_str;
}
