/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peta <peta@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:19:18 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/17 20:10:51 by peta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void	tester(t_main_tools *tools, int signpost); // ZAKOMENTOVAT
int		minishell_loop(t_main_tools *tools);

// Definition and initialization of the global variable
int	g_signal = 0;

/**
	@brief:
	Setting these members to NULL is a way to ensure that the structure starts
	in a known state, preventing undefined behavior from uninitialized pointers
	get_paths is used to get the paths from the environment variable, and
	adding them to the main_tools structure
*/
void	tools_to_default_setting(t_main_tools *tools)
{
	tools->lexer_list = NULL;
	tools->paths = NULL;
	tools->simple_cmd_list = NULL;
	tools->pipes = 0;
	tools->pid = NULL;
	get_paths(tools);
	minishell_loop(tools);
}

/**
	@brief:
	set_pwd function is used to set the current working directory
	in the main_tools structure
*/
void	set_pwd(t_main_tools *tools)
{
	char	*pwd;
	size_t	buf_size;

	buf_size = 1024;
	pwd = malloc(sizeof(char) * buf_size);
	if (!pwd)
		ft_putstr_fd_exit("Error: malloc failed", STDERR, 1);
	while(getcwd(pwd, buf_size) == NULL)
	{
		free(pwd);
		buf_size *= 2;
		pwd = malloc(sizeof(char) * buf_size);
		if (!pwd)
			ft_putstr_fd_exit("Error: malloc failed", STDERR, 1);
	}
	tools->pwd = pwd;
}

/**
	@brief:
	minishell_loop function is the main loop of the minishell program
	which is responsible for reading the input, parsing it, and executing it
	
	@param tools: pointer to the main_tools structure
	@return: 0
*/
int	minishell_loop(t_main_tools *tools)
{
	char	*tmp;

	tools->args = readline(READLINE_MSG);
	if (!tools->args)
		exit (0);
	tmp = ft_strtrim(tools->args, " ");
	free(tools->args);
	tools->args = tmp;
	if (ft_strlen(tools->args) == 0)
	{
		free(tools->args);
		return minishell_loop(tools);
	}
	lexer(tools);
	//tester(tools, LEXER_LIST); // ZAKOMENTOVAT
	parser(tools);
	//tester(tools, CMD_LIST); // ZAKOMENTOVAT
	// while(tools->simple_cmd_list)
	// {
	// 	heredoc(tools, tools->simple_cmd_list);
	// 	printf("simple_cmd_list->heredoc_filename: %s\n", tools->simple_cmd_list->heredoc_filename);
	// 	tools->simple_cmd_list = tools->simple_cmd_list->next;
	// }
	executor(tools);
	if (tools->pid)
	{
		free(tools->pid);
	}
	tools->finished = 1;
	/*
	while(tools->simple_cmd_list)
	{
		if (tools->simple_cmd_list->builtin)
			tools->simple_cmd_list->builtin(tools, tools->simple_cmd_list);
		tools->simple_cmd_list = tools->simple_cmd_list->next;
	} */

	tools_to_default_setting(tools);
	return (0);
}

/**
	@brief:
	main function is the entry point of the minishell program
	which is responsible for initializing the main_tools structure
	and starting the main loop of the program
	Steps:
	- Check if there are any arguments
	- Find the environment variable and add it to the main_tools structure
	- Set the current working directory
	- Set the main_tools structure to the default settings
	- Start the main loop of the program
	
*/
int	main(int argc, char **argv, char **envp)
{
	t_main_tools	tools;

	if (argc != 1 || argv[1] || !envp[0])
		ft_putstr_fd_exit("Error: don't put any arguments", STDOUT, 0);
	copy_env(&tools, envp);
	set_pwd(&tools);
	tools.finished = 0;
	tools_to_default_setting(&tools);
	minishell_loop(&tools);
	return (0);
}
