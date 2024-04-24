/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:19:08 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/24 13:32:37 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	@brief:
	- expand_dollar function expands the dollar sign and the env-variable
	- it take the string till the $ and join it with the environment variable
	- the power is, that it works only for one $, so if there are more $, which 
	have for exaple backslash before, it will not work for them
	- from handle_dollar we send the string beggining with $
	$USER\$USER		-> psimcak\$USER
*/
char	*expand_dollar(char *str)
{
	char	*env_expanded;
	char	*result;
	char	*after_pure;
	char	*pure;
	int		i;

	i = 0;
	if (!str[0])
		return (str);
	pure = clear_env_variable(&str[1]);
	after_pure = ft_strdup(&str[ft_strlen(pure) + 1]);
	env_expanded = getenv(pure);
	if (env_expanded)
	{
		result = ft_strjoin(env_expanded, after_pure);
		ft_str_replace(&str, result);
		// free(result);
	}
	if (pure[0] == '?')
	{
		// result = ft_itoa(g_exit_status);
		result = ft_strjoin(result, after_pure);
		ft_str_replace(&str, result);
		// free(result);
	}
	free(after_pure);
	free(pure);
	return (str);
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
	char	*result;

	i = -1;
	remove_quotes(str, '\"');
	result = ft_substr(str, 0, next_dollar(str));
	while (str[++i])
	{
		if (quotes_classifier(&str[i]) == SINGLE_Q)
		{
			remove_quotes(str, '\'');
			free(result);
			return (str);
		}
		if (str[i] == '$')
		{
			if (env_not_valid(&str[i]))
			{
				tmp = ft_substr(&str[i], 0, next_dollar(&str[i] + 1) + 1);
				result = ft_strjoin(result, tmp);
				continue ;
			}
			str = expand_dollar(&str[i]);
			tmp = ft_substr(str, 0, next_dollar(str + 1) + 1);
			result = ft_strjoin(result, tmp);
			i = -1;
		}
	}
	ft_str_replace(&str, result);
	free(result);
	return (str);
}

/**
	@brief:
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

	Example:
	echo $USER > "test.txt" | cat test.txt
*/
void	expander(t_simple_cmd *curr_simple_cmd)
{
	int		i;
	char	**expanded_str;
	char	**tmp;

	tmp = curr_simple_cmd->str;
	i = num_of_dollars_in_list(tmp);
	expanded_str = malloc((i + 1) * sizeof(char*));
	if (!expanded_str)
		exit(1);
	expanded_str[i] = NULL;
	i = -1;
	while (tmp[++i])
	{
		if (there_is_dollar_in_str(tmp[i]))
		{
			expanded_str[i] = handle_dollar(tmp[i]);
			ft_str_replace(&curr_simple_cmd->str[i], expanded_str[i]);
			free(expanded_str[i]);
		}
	}
	free(expanded_str);
}
