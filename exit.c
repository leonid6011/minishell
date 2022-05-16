#include "minishell.h"

int exit_prog(void)
{
    exit (g_envp.status_exit);
}