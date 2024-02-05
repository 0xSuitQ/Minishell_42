/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:33:02 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/05 20:31:55 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	tokenize(char **words, t_lexer	**lexer_list)
{
	static int				i = -1;
	static int				j;
	static int				found;
	static t_token_matrix	tokens[] = {
	{"|", PIPE},
	{"<", LESS}, {"<<", LESS_LESS},
	{">", GREAT}, {">>", GREAT_GREAT}
	};

	while (words[++i])
	{
		j = -1;
		found = 0;
		while (++j < TOKEN_NUM)
		{
			if (ft_strcmp(words[i], tokens[j].str_symbol) == 0)
			{
				create_list(lexer_list, i, tokens[j].type, NULL);
				found = 1;
			}
		}
		if (!found)
			create_list(lexer_list, i, 0, words[i]);
	}
}

static char	**split_by_whitespace(char *input)
{
	char	**words;
	int		i;

	i = 0;
	words = malloc(sizeof(char *) * substring_counter(input) + 1);
	if (!words)
		return (NULL);
	while (*input)
	{
		while (*input && ((*input >= 9 && *input <= 13) || *input == 32))
			input++;
		if (*input)
			words[i++] = ft_str_sepdup(input);
		while (*input && !((*input >= 9 && *input <= 13) || *input == 32))
			input++;
	}
	words[i] = 0;
	return (words);
}

t_lexer	*lexer(char *input)
{
	char		**words;
	int			i;
	t_lexer		*lexer_list;

	i = 0;
	lexer_list = NULL;
	words = split_by_whitespace(input);
	tokenize(words, &lexer_list); // TODO free

	// TEST
	while (lexer_list)
	{
		ft_printf("str of the lexer list number %d: %s\n", lexer_list->index, lexer_list->sub_str);
		ft_printf("token of the lexer list number %d: %d\n", lexer_list->index, lexer_list->token);
		//if (lexer_list[i].token == GREAT)
		//	write(1, "TEST CHECK\n", 12);
		ft_printf("------------------\n");
		lexer_list = lexer_list->next;
	}
	return (lexer_list);
}
