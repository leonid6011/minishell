#include "minishell.h"

int	check_argc_exit(char *str)
{
	//printf("str = %s\n", str);
	if ((ft_atoi(str) == 0 && str[0] != '0'))
	{
		if (check_str("+0", str))
			return (0);
		//printf("str = %s\n", str);
		//printf("ya tut\n");
		//printf("str = %s, ft_atoi = %d\n", str, ft_atoi(str));
		return (2);
	}
	else
	{
	//	printf("str = %s, ft_atoi = %d\n", str, ft_atoi(str));
		//printf("LOL\n");
		return (ft_atoi(str)); //good
	}
}

void	exit_prog(t_table_cmd *table)
{
	print_list_arguments(table->arguments);
	if (table->arguments[1])
	{
		g_envp.status_exit = check_argc_exit(table->arguments[1]);
		if (g_envp.status_exit > 0 && ft_strlen(table->arguments[1]) >= 18 && ft_isdigit(table->arguments[1][0]))
			g_envp.status_exit = 2;
		if (g_envp.status_exit < 0 && ft_strlen(table->arguments[1]) >= 18 && !ft_isdigit(table->arguments[1][0]))
			g_envp.status_exit = 2;
		printf("g_envp.status_exit = %d\n", g_envp.status_exit);
	}
	if (table->arguments[2])
	{
		//printf("table->arguments[2] = %s\n", table->arguments[2]);
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("zhs: exit: too many arguments\n", 2);
		g_envp.status_exit = EXIT_FAILURE;
		return ;
	}
	ft_putstr_fd("exit\n", 2);
	exit(g_envp.status_exit);
}
