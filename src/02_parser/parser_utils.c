#include "minishell.h"

/**
	@brief:
	token_to_str function returns the string representation of the token.
	It uses 2D array of strings and token_list enum to find the right string
	and macro to find the right token. If !token, it returns "newline".
*/
char	*token_to_str(t_lexer *token)
{
	int						i;
	static t_token_matrix	tokens[] = {
		{"|", PIPE},
		{"<", LESS},
		{">", GREAT},
		{"<<", LESS_LESS},
		{">>", GREAT_GREAT}};

	i = -1;
	while (++i < TOKEN_NUM)
	if (token && token->token == tokens[i].type)
		return (tokens[i].str_sym);
	return ("newline");
}

/*
	@brief:
	unexpected_token_officer is a member of the ERROR_POLICE. It prints an
	error message with the unexpected token and exits the program.
*/
void	unexpected_token_officer(t_lexer *head, t_main_tools *tools)
{
	ft_printf("syntax error near unexpected token `%s'",
		token_to_str(head));
	ft_putstr_fd("\n", STDOUT);
	error_police(2, tools);
}
