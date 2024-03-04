// #include "../../includes/minishell.h"
// #include <unistd.h>

// int	executor(t_main_tools *tools)
// {
// 	int	fd[2];
// 	int	fd_in;

// 	fd_in = STDIN_FILENO;
// 	while (tools->simple_cmd_list)
// 	{
// 		// expander
// 		if (tools->simple_cmd_list->next)
// 			pipe(fd);
// 		heredoc(tools, tools->simple_cmd_list);
// 		// create fork function
// 		close(fd[1]);

// 		if (tools->simple_cmd_list->heredoc_filename)
// 			fd_in = fd[0];
// 		if (tools->simple_cmds->next)
// 			tools->simple_cmds = tools->simple_cmds->next;

// 	}
// }
