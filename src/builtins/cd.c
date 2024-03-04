
#include "../../includes/minishell.h"

int	msh_cd(t_main_tools *tools, t_simple_cmd *cmd)
{
	char *home_dir;

	tools->old_pwd = tools->pwd;
	if (cmd->str[1] == NULL)
	{
		if (home_dir = getenv("HOME") == NULL)
			return (EXIT_FAILURE);
        if (chdir(home_dir) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if(chdir(cmd->str[1]) == -1)
		{
			ft_putstr_fd("cd: no such file or directory: ", STDERR_FILENO);
    	    ft_putstr_fd(cmd->str[1], STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
    	        return (EXIT_FAILURE);
		}
	}
}