#include "../../includes/minishell.h"

int msh_pwd(t_main_tools *tools, t_simple_cmd *cmd)
{
	(void)cmd;
	ft_putstr_fd(tools->pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}