/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:33:02 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/15 16:20:09 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>
/*
tokienize() is a function that takes a list of words and creates a lexer list.
It iterates through the words and checks if the word is a token. If it is, it
creates a new node in the lexer list with the token type and the word. If it is
not, it creates a new node with the token type 0 and the word.
*/
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
			if (strcmp(words[i], tokens[j].str_sym) == 0)
			{
				create_list(lexer_list, i, tokens[j].type, tokens[j].str_sym);
				found = 1;
			}
		}
		if (!found)
			create_list(lexer_list, i, 0, words[i]);
	}
}

/*
split_by_whitespace() is a function that takes a string and splits it into words
by whitespace. It returns a list of words.
*/

static int count_string_length(char *input, char delimiter)
{
    int length;
	
	length = 0;
    while (*input && *input != delimiter)
	{
        length++;
        input++;
    }
	if (*input == '\0')
			ft_putstr_fd_exit("Error: unclosed quote\n", STDERR, EXIT_FAILURE);
    return (length);
}

void handle_quotes(char **input, char ***words, int i)
{
	char *word;
	char delimiter;
	int len;
	int iter;
	
	delimiter = **input;
	(*input)++;
	iter = 0;
	len = count_string_length(*input, delimiter);
	word = malloc(sizeof(char) * (len + 3)); // +3 for the quotes and null terminator
	word[iter++] = delimiter; // add opening quote
	while (**input && **input != delimiter)
		word[iter++] = *(*input)++;
	word[iter++] = delimiter; // add closing quote
	word[iter] = '\0';
	(*words)[i] = word;
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
		{
			if (*input == 34 || *input == 39)
				handle_quotes(&input, &words, i);
			else
				words[i] = ft_str_sepdup(input);
			i++;
		}
		while (*input && !((*input >= 9 && *input <= 13) || *input == 32))
			input++;
	}
	words[i] = 0;
	return (words);
}

/*
lexer() is a function that takes a string and returns a lexer list. It first
splits the string into words, then tokenizes the words and creates a lexer list.
It is the hub of all lexer functions.
*/
t_lexer	*lexer(char *input)
{
	char		**words;
	t_lexer		*lexer_list;

	if (input == NULL)
		ft_putstr_fd_exit("exit", STDOUT, EXIT_SUCCESS);
	lexer_list = NULL;
	words = split_by_whitespace(input);
	tokenize(words, &lexer_list); // TODO free
	write(1, "lexer.c\n", 8);
	return (lexer_list);
}
