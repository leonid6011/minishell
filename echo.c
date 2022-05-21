/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:54:32 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/21 20:27:01 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nbr_argc(t_table_cmd *table, int n_flag)
{
	int nbr;

	nbr = 0;
	while(table->arguments[nbr])
		nbr++;
	if (n_flag == 1)
		nbr--;
	nbr--;
	return (nbr);
}

int	all_n(char *argm)
{
	int i;

	i = 0;
	if (argm[0] == '-' && ft_strlen(argm) == 1)
		return (0);
	argm++;
	while (argm[i])
	{
		if (argm[i] != 'n')
			return (0); //плохо
		i++;
	}
	return (1); //хоррошо
}

int	echo(t_table_cmd *table)
{
	int	n_flag;
	int	nbr_arguments;
	int	i;

	//print_list_arguments(table->arguments);
	if (!table->arguments[1])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	n_flag = 0;
	if (check_str(table->arguments[1], "-n") && all_n(table->arguments[1]))
		n_flag = 1;
	
	nbr_arguments = nbr_argc(table, n_flag);
	printf("NBR = %d\n", nbr_arguments);
	i = 1;
	while (table->arguments[i])
	{
		if (!check_str(table->arguments[i], "-n"))
			break;
		printf("table->arguments[i] = %s\n", table->arguments[i]);
		i++;
	}
	i--;
	printf("i = %d\n", i);
	// i = 1;
	// if (n_flag == 1)
	// 	i = 2;
	// if (!table->arguments[i])
	// 	ft_putstr_fd("\n", STDOUT_FILENO);
	nbr_arguments = nbr_arguments - i;
	printf("nbr_arguments = %d\n", nbr_arguments);
	printf("table->arguments[i] = %s\n", table->arguments[i]);
	printf("flag = %d\n", n_flag);
	while (table->arguments[i])
	{
		ft_putstr_fd(table->arguments[i], STDOUT_FILENO);
		nbr_arguments--;
		if (nbr_arguments != 0)
		{
			ft_putchar_fd(' ', STDOUT_FILENO);
			printf("lol\n");
		}
		if (nbr_arguments == 0)
		{
			if (n_flag == 0)
				ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
