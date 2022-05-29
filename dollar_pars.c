/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:33:40 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/29 13:19:52 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_str(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0); //не совпали
		i++;
	}
	return (1); //совпали
}

int	check_str_n(char *str1, char *str2, int n)
{
	int i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && n != i)
	{
		if (str1[i] != str2[i])
			return (0); //не совпали
		i++;
	}
	return (1); //совпали
}

t_token	*del_elem_list(t_token *del, t_token *head)
{
	t_token	*tmp;

	tmp = head;
	//print_list_token(head);
	if (head == del)
	{
		if (tmp->next)
		{
			tmp = tmp->next;
			head->value = tmp->value;
			head->key = tmp->key;
			head->next = tmp->next;
			free(tmp);
			return (head);
		}
		else
		{
			free(tmp->value);
			free(tmp->next);
			free(tmp);
			return (head);
		}
	}
	while (tmp->next != del)
		tmp = tmp->next;
	tmp->next = del->next;
	free (del);
	return (tmp);
}

int	correct_count(char *elem_split_value)
{
	int i;

	i = 0;
	while (elem_split_value[i] && elem_split_value[i] != '\'' && elem_split_value[i] != '$' && elem_split_value[i] != ' ' && elem_split_value[i] != '\"' && elem_split_value[i] != '/' && elem_split_value[i] != '=')
	{
		i++;
	}
	return (i);
}

char	*change_value(char *value, char *old_value, int len_sp_val, char *env_value)
{
	char	*new_value;
	int		c_new_val;
	int		i;

	//printf("do change val = %s\n", old_value);
	env_value++;
	c_new_val = 0;
	while (old_value[c_new_val] != '$')
	{
		c_new_val++;
	}
	//printf("split\n");
	//print_list_arguments(split_value);
	i = 0;
	while (env_value[i])
	{
		i++;
	}
	c_new_val = c_new_val + i;
	i = 0;
	while (i != len_sp_val)
	{
		//printf("loo\n");
		value++;
		i++;
	}
	c_new_val = c_new_val + i;
	new_value = (char *)malloc(sizeof(char) * c_new_val + 1);
	i = 0;
	while (old_value[i] != '$')
	{
		new_value[i] = old_value[i];
		i++;
	}
	new_value[i] = '\0';
	new_value = ft_strjoin(new_value, env_value);
	new_value = ft_strjoin(new_value, value);
	//printf("NEW VAL = %s\n", new_value);
	// printf("c_new_val = %d\n", c_new_val);
	return (new_value);
}

char	*digit_arg_dol(char *value, char *old_value)
{
	char	*new_val;
	int		i;
	int		count;
	int		all_len;
	
	all_len = ft_strlen(old_value);
	count = all_len - correct_count(value) - 1;
	new_val = (char *)malloc(sizeof(char) * count);
	i = 0;
	while (old_value[i] != '$')
	{
		new_val[i] = old_value[i];
		i++;
	}
	new_val[i] = '\0';
	value++;
	new_val = ft_strjoin(new_val, value);
	//printf("str = %s\n", new_val);
	return(new_val);
}

char *del_posle_dol(char *old_value, char *value)
{
	char	*new_val;
	int		i;
	int		count;
	int		all_len;
	char	*ost;
	
	all_len = ft_strlen(old_value);
	count = all_len - correct_count(value) - 1;
	new_val = (char *)malloc(sizeof(char) * count);
	i = 0;
	while (old_value[i] != '$')
	{
		new_val[i] = old_value[i];
		i++;
	}
	new_val[i] = '\0';
	ost = value;
	i = 0;
	while (i != correct_count(value))
	{
		ost++;
		i++;
	}
	//printf("str do = %s\n", ost);
	new_val = ft_strjoin(new_val, ost);
	//printf("str = %s\n", new_val);
	return(new_val);
}

char	*change_in_env(char *value)
{
	int			i;
	char		*old_value;
	t_env_var	*env;
	int			len_env;
	int			len_sp_val;
	int			yes_flag;
	char		*new_value;

	i = 0;
	yes_flag = 0;
	old_value = value;
	if (value[0] == '\"')
		return(old_value);
	while (value[0] != '$')
	{
		value++;
		i++;
	}
	value++;
	//printf("value++ = %s\n", value);
	env = g_envp.env_list;
	//printf("value = %s\n", value);
	//printf("old value = %s\n", old_value);
	if (ft_isdigit(value[0]))
	{
		return(digit_arg_dol(value, old_value));
	}
	while (env)
	{
		len_env = ft_strlen(env->key);
		len_sp_val = correct_count(value);
		//printf("len_env = %d\n", len_env);
		//printf("len_sp_val = %d\n", len_sp_val);
		if (check_str_n(env->key, value, len_sp_val) && len_env == len_sp_val)
		{
			new_value = change_value(value, old_value, len_sp_val, env->value);
			//printf("NEW = %s\n", new_value);
			return (new_value);
		}
	env = env->next;
	}
	if (ft_isalpha(value[0]))
	{
		new_value = del_posle_dol(old_value, value);
		return (new_value);
	}
	//printf("NEW2 = %s\n", new_value);
	//printf("old_val  = %s\n", old_value);
	return (old_value);
}

int	check_asc(char *change_value)
{
	int	i;
	int	flag;

	flag = 0;
	if (ft_strlen(change_value) == 1)
		return (0); // не удалять
	change_value++;
	i = 0;
	while (change_value[i])
	{
		//printf("%c - %d\n", change_value[i], ft_isalpha(change_value[i]));
		if (ft_isalpha(change_value[i]))
			flag = 1;
		i++;
	}
	if (!flag)
		return (0);
	else
		return (1);
}

int	alone_dollar(char *str)
{
	printf("str = %s\n", str);
	return (1);
}

t_token	*dollar_pars(t_token *list_token)
{
	t_token	*tmp;
	char	*change_value;
	int		i;

	//print_list_token(list_token);
	tmp = list_token;
	while (tmp)
	{
		i = 0;
		//printf("tmp = %s\n", tmp->value);
		if (tmp->key != e_single_quote)
		{
			while (tmp->value[i])
			{
				if (tmp->value[i] == '$')
				{
					//printf(" do change_value = %s\n", tmp->value);
					change_value = change_in_env(tmp->value);
					//printf("posle change_value = %s\n", change_value);
					if (change_value[0] == '\0')
					{
						//printf("NUZNO UDALIT\n");
						tmp = del_elem_list(tmp, list_token);
					}
					else
					{
							tmp->value = change_value;
					}
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
	//print_list_token(list_token);
	return(list_token);
}