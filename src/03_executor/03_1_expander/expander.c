/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:19:08 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/27 00:01:09 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	@brief:
	- expand_dollar function expands the dollar sign in the string
	- if the string is empty, it returns the string
	- if the string is not empty, it expands the dollar sign
	- if the string is a question mark, it returns the signal
*/
char	*expand_dollar(char *str)
{
	char	*env_expanded;

	if (!str[0])
		return (str);
	env_expanded = getenv(str + 1);
	if (env_expanded)
	{
		free(str);
		str = ft_strdup(env_expanded);
	}
	if (str[0] == '?')
	{
		free(str);
		str = ft_itoa(g_signal);
	}
	return (str);
}

/**
	@brief:
	handle_dollar function handles the dollar sign in the string
	it goes through the string and if there is a $, it will be expanded
*/
int	there_is_single_quote(char *str)
{
	if (quotes_classifier(str) == SINGLE_Q)
	{
		remove_quotes(str, '\'');
		return (TRUE);
	}
	return (FALSE);
}

/**
	@brief:
	impossible_to_expand function adds the unedited string to the list
*/
void	impossible_to_expand(t_expander *exp, char *str)
{
	char	*sub_str;

	sub_str = ft_substr(str, 0, next_dollar(str + 1) + 1);
	ft_lstadd_back(&exp->exp_list, ft_lstnew(sub_str));
}

/**
	@brief:
	possible_to_expand function expands the string and adds it to the list
*/
void	possible_to_expand(t_expander *exp, char *str)
{
	char	*sub_str;
	char	*expanded;

	sub_str = ft_substr(str, 0, next_dollar(&str[1]) + 1);
	expanded = expand_dollar(sub_str);
	ft_lstadd_back(&exp->exp_list, ft_lstnew(expanded));
}

/**
	@brief:
	free_list function frees the list
*/
void	free_list(t_list *exp_list)
{
	t_list	*tmp;

	while (exp_list)
	{
		tmp = exp_list;
		exp_list = exp_list->next;
		free(tmp->content);
		free(tmp);
	}
}

/**
	@brief:
	list_to_array function converts the list to an array
*/
char	*list_to_array(t_list *exp_list)
{
	t_list	*tmp;
	char	*result;
	char	*joined_result;

	tmp = exp_list;
	result = ft_strdup(tmp->content);
	tmp = tmp->next;
	while (tmp)
	{
		joined_result = ft_strjoin(result, tmp->content);
		free(result);
		result = joined_result;
		tmp = tmp->next;
	}
	free_list(exp_list);
	return (result);
}

/**
	@brief:
	first_char_not_dollar function checks if the first character is not a 
	dollar sign
*/
int	first_char_not_dollar(char *str)
{
	if (str[0] != '$')
		return (TRUE);
	return (FALSE);
}

/**
	@brief:
	handle_dollar function handles the dollar sign in the string
	- it removes the quotes
	- if there is a single quote, it returns the string
	- if the first character is not a dollar sign, it adds the string to the
	list
	- if the it is not possible to expand, it adds the string to the list
	- if it is possible to expand, it expands the string and adds it to the list
	- it converts the list to an array and returns the result
*/
char	*handle_dollar(char *str)
{
	t_expander	exp;

	remove_quotes(str, '\"');
	if (there_is_single_quote(str))
		return (str);
	exp.exp_list = NULL;
	if (first_char_not_dollar(str))
	{
		exp.first = ft_substr(str, 0, next_dollar(str));
		exp.exp_list = ft_lstnew(exp.first);
	}
	exp.i = -1;
	while (str[++exp.i])
	{
		if (str[exp.i] == '$')
		{
			if (env_not_valid(&str[exp.i]) && str[exp.i + 1] != '?')
			{
				impossible_to_expand(&exp, &str[exp.i]);
				continue ;
			}
			possible_to_expand(&exp, &str[exp.i]);
		}
	}
	free(str);
	str = list_to_array(exp.exp_list);
	return (str);
}
/**
	@brief:
	The expander is responsible for expanding special characters and variables
	within the user's command input. Its primary purpose is to handle the
	expansion of dollar signs ($) and their associated environment variables or
	special symbols (e.g., $? for the exit status of the last command).
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
