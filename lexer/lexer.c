/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:33:02 by psimcak           #+#    #+#             */
/*   Updated: 2024/02/05 18:20:29 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*get_last_node(t_lexer *list_head)
{
	if (list_head == NULL)
		return (NULL);
	while (list_head->next)
		list_head = list_head->next;
	return (list_head);
}

int	substring_counter(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while(str[i])
	{
		while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
			i++;
		if (str[i])
			counter++;
		while(str[i] && (!((str[i] >= 9 && str[i] <= 13) || str[i] == 32)))
			i++;
	}
	return (counter);
}

void	create_node(t_lexer **list, int index, t_token_list tok, char *str)
{
	t_lexer	*new_node;
	
	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return ;
	printf("test: %d\n", index);
	new_node->i = index;
	new_node->token = tok;
	if (str)
		new_node->str = ft_strdup(str); // TODO: mind to freeing it
	else
		new_node->str = NULL;
	if (index == 0)
	{
		*list = new_node;
		(*list)->next = NULL;
		(*list)->prev = NULL;
	}
	else
	{
		new_node->prev = get_last_node(*list);
		new_node->prev->next = new_node;
		new_node->next = NULL;
	}
}

void	tokenize(char **words, t_lexer	**lexer_list)
{
	static t_token_matrix tokens[] = {
		{"|", PIPE},	
		{"<", LESS},
		{"<<", LESS_LESS},
		{">", GREAT},
		{">>", GREAT_GREAT}
	};
	static int	i = -1;
	static int	j;
	static int	found;

	while (words[++i])
	{
		j = -1;
		found = 0;
		while(++j < TOKEN_NUM)
		{
			if (ft_strcmp(words[i], tokens[j].str_symbol) == 0)
			{
				create_node(lexer_list, i, tokens[j].type, NULL);
				found = 1;

			}
		}
		if (!found)
			create_node(lexer_list, i, 0, words[i]);
	}
}

/*t_lexer	*tokenize(char **words, char *str)
{
	t_lexer	*lexer_list;
	int		i;

	i = 0;
	
	while (words[i])
	{
		if (strcmp(words[i], "|") == 0)
		{
			create_node(&lexer_list, i, PIPE, NULL); // Not sure if we have to send &tokens[i] in there
		}
		else if (strcmp(words[i], "<") == 0)
		{
			create_node(&lexer_list, i, LESS, NULL);
		}
		else if (strcmp(words[i], "<<") == 0)
		{
			create_node(&lexer_list, i, LESS_LESS, NULL);
		}
		else if (strcmp(words[i], ">") == 0)
		{
			create_node(&lexer_list, i, GREAT, NULL);
		}
		else if (strcmp(words[i], ">>") == 0)
		{
			create_node(&lexer_list, i, GREAT_GREAT, NULL);
		}
		if (i == 0)
			continue;
		else
			create_node(lexer_list, i, NULL, words[i]); // TODO
		i++;
	}
	return (lexer_list);
}*/

char	**split_by_whitespace(char *input)
{
	char	**words;
	int		i;
	int		j;

	i = 0;
	words = malloc(sizeof(char *) * substring_counter(input) + 1);
  if (!words)
    return (NULL);
	while (*input)
	{
		while (*input && ((*input >= 9 && *input <= 13) || *input == 32))
			input++;
		if (*input)
			words[i++] = str_sepdup(input);
		while (*input && !((*input >= 9 && *input <= 13) || *input == 32))
			input++;
	}
	words[i] = 0;
	return (words);
}

int	size_of_2d(char **words)
{
	static int	count = 0;

	while (words[count])
		count++;
	return (count);
}

t_lexer *lexer(char *input)
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
		printf("str of the lexer list number %d: %s\n", lexer_list->i, lexer_list->str);
		printf("token of the lexer list number %d: %u\n", lexer_list->i, lexer_list->token);
		//if (lexer_list[i].token == GREAT)
		//	write(1, "TEST CHECK\n", 12);
		printf("------------------\n");
		lexer_list = lexer_list->next;
	}
	return (lexer_list);
}

int	main()
{
	char	*input;

	input = "ls -l > file.txt";

	lexer(input);

	return 0;
}
