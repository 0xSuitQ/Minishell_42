#include "../includes/lexer.h"
#include "../includes/parser.h"

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

void	*create_node(t_lexer *token, int index, t_token tok, char *str) {
    token->i = index;
	if (token)
		token->token = tok;
	else
		token->token = NULL;
	if (str)
    	token->str = ft_strdup(str); // TODO: mind to freeing it
	else
		token->str = NULL;
    token->next = NULL;
    token->prev = NULL;
}

t_lexer	*tokenize(char **words, char *str)
{
	t_lexer		*lexer_list;
	static void	*special_char[5][2] = {
		{"|", PIPE},
		{"<", LESS},
		{"<<", LESS_LESS},
		{">", GREAT},
		{">>", GREAT_GREAT}
	};
	static int	i = 0;

	lexer_list = malloc(sizeof(t_lexer) * (substring_counter(str) + 1));
	// TODO Error handling for malloc
	
	while 
}

t_lexer	*tokenize(char **words, char *str)
{
	t_lexer	*tokens;
	int		i;

	i = 0;
	tokens = malloc(sizeof(t_lexer) * (substring_counter(str) + 1));
	// TODO Error handling for malloc
	while (words[i])
	{
		if (strcmp(words[i], "|") == 0)
		{
			create_node(&tokens[i], i, PIPE, NULL); // Not sure if we have to send &tokens[i] in there
		}
		else if (strcmp(words[i], "<") == 0)
		{
			create_node(&tokens[i], i, LESS, NULL);
		}
		else if (strcmp(words[i], "<<") == 0)
		{
			create_node(&tokens[i], i, LESS_LESS, NULL);
		}
		else if (strcmp(words[i], ">") == 0)
		{
			create_node(&tokens[i], i, GREAT, NULL);
		}
		else if (strcmp(words[i], ">>") == 0)
		{
			create_node(&tokens[i], i, GREAT_GREAT, NULL);
		}
		if (i == 0)
			continue;
		else
			token_append(); // TODO
		i++;
	}
	return (tokens);
}

char	**split_by_whitespace(char *str)
{
	char	**words;
	int		i;
	int		j;

	i = 0;
	words = malloc(sizeof(char *) * substring_counter(str) + 1);
	while (*str)
	{
		while (*str && ((*str >= 9 && *str <= 13) || *str == 32))
			str++;
		if (*str)
			words[i++] = str_sepdup(str);
		while (*str && !((*str >= 9 && *str <= 13) || *str == 32))
			str++;
	}
	words[i] = 0;
	return (words);
}

t_lexer *lexer(char *str)
{
	t_lexer	*tokens;
	char	**words;
	int		i;

	i = 0;
	words = split_by_whitespace(str);
	//tokenizer
	
	return (tokens);
}

int	main()
{
	char	*str;

	str = "ls -l > file.txt";

	lexer(str);

	return 0;
}
