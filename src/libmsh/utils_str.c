/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:54:47 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/07 17:50:21 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	ft_str_sep_len(char const *s)
{
	int	i;

	i = 0;
	while (s[i] && !((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
		i++;
	return (i);
}

int	substring_counter(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
			i++;
		if (str[i])
			counter++;
		while (str[i] && (!((str[i] >= 9 && str[i] <= 13) || str[i] == 32)))
			i++;
	}
	return (counter);
}

char	*ft_str_sepdup(char *s)
{
	char	*word;
	int		i;
	int		len;

	i = 0;
	len = ft_str_sep_len(s);
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*str;

	if (!src)
		return (NULL);
	len = 0;
	while (src[len])
		len++;
	str = (char *)malloc(sizeof(*str) * (len + 1));
	i = 0;
	while (i < len)
	{
		str[i] = src[i];
		i++;
	}
	return (str);
}
