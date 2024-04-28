/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:19:18 by psimcak           #+#    #+#             */
/*   Updated: 2024/04/28 22:28:52 by psimcak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//Definition and initialization of the global variable
int	g_signal = 0;

/**
	@brief:
	Exit the minishell with the given exit number and free all the data
*/
void	exit_minishell(t_main_tools *tools, int exit_num)
{
	if (tools)
		clear_all(tools);
	exit(exit_num);
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

	signal(SIGINT, handle_sigint);
	g_signal = 0;
	tools->args = readline(READLINE_MSG);
	if (!tools->args)
		ctrl_d();
	tmp = ft_strtrim(tools->args, " ");
	free(tools->args);
	tools->args = tmp;
	if (ft_strlen(tools->args) == 0)
	{
		free(tools->args);
		return (minishell_loop(tools));
	}
	validate_history(tools->args);
	lexer(tools);
	parser(tools);
	executor(tools);
	tools->finished = 1;
	clear_for_continue(tools);
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
	tools.envp_cpy = ft_arrdup(envp);
	tools.pwd = NULL;
	set_pwd(&tools);
	tools.old_pwd = ft_strdup(tools.pwd);
	tools.finished = 0;
	tools_to_default_setting(&tools);
	parse_envp(&tools);
	minishell_loop(&tools);
	return (0);
}
