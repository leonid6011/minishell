#include "minishell.h"

int	print_exit(void)
{
	write(2, "exit\n", 5);
	return (1);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
    (void)argv;
    (void)env;
	char	*str; 
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_prog);
	if (argc != 1)
		return (1);
	while (1)
	{
		str = readline("minishell$>");
		add_history(str);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_prog);
		if (!str)
		{
			return (print_exit());
		}
        free(str);
    }
}