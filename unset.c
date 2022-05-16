#include "minishell.h"

t_env_var	*del_elem_env(t_env_var *del, t_env_var *head)
{
	t_env_var	*tmp;

	tmp = head;
	if (head == del)
	{
		tmp = tmp->next;
		head->value = tmp->value;
		head->key = tmp->key;
		head->next = tmp->next;
		free(tmp);
		return (head);
	}
	while (tmp->next != del)
		tmp = tmp->next;
	tmp->next = del->next;
	free (del);
	return (tmp);
}

void	del_add_elem_env(char	*str, t_env_var	*env_list)
{
	t_env_var	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (check_str(tmp->key, str))
		{
			env_list = del_elem_env(tmp, env_list);
		}
		tmp = tmp->next;
	}
}

int	unset_fun(t_table_cmd *table)
{
	t_env_var	*env_list;
	int			i;
	
	env_list = g_envp.env_list;
	i = 1;
	while (table->arguments[i])
	{
		del_add_elem_env(table->arguments[i], env_list);
		i++;
	}
    return (EXIT_SUCCESS);
}