/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbutter <mbutter@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:54:32 by echrysta          #+#    #+#             */
/*   Updated: 2022/05/14 18:06:30 by mbutter          ###   ########.fr       */
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
	i = 1;
	if (n_flag == 1)
		i = 2;
	// if (!table->arguments[i])
	// 	ft_putstr_fd("\n", STDOUT_FILENO);
	while (table->arguments[i])
	{
		ft_putstr_fd(table->arguments[i], STDOUT_FILENO);
		nbr_arguments--;
		if (nbr_arguments != 0)
			ft_putchar_fd(' ', STDOUT_FILENO);
		if (nbr_arguments == 0)
		{
			if (n_flag == 0)
				ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

// static int	is_valid_option_n(char *str)
// {
// 	if (!*str || *str != '-')
// 		return (0);
// 	str++;
// 	if (!*str || *str != 'n')
// 		return (0);
// 	while (*str)
// 	{
// 		if (*str != 'n')
// 			return (0);
// 		str++;
// 	}
// 	return (1);
// }

// void	skip_n_options(t_token *tokens, int *i, int *n_option)
// {
// 	while (tokens[*i].word && tokens[*i].type == WORD
// 		&& is_valid_option_n(tokens[*i].word))
// 	{
// 		*n_option = 1;
// 		(*i)++;
// 	}
// }


// static void	skip_non_words(t_token *tokens, int *i)
// {
// 	while (tokens[*i].word && tokens[*i].type != WORD)
// 		(*i)++;
// }

// static void	print_one_word(t_token *tokens, int *i)
// {
// 	ft_putstr_fd(tokens[*i].word, STDOUT_FILENO);
// 	(*i)++;
// }

// static void	print_next_wds(t_token *tokens, int *i)
// {
// 	while (tokens[*i].word)
// 	{
// 		if (tokens[*i].type == WORD)
// 		{
// 			ft_putstr_fd(" ", STDOUT_FILENO);
// 			ft_putstr_fd(tokens[*i].word, STDOUT_FILENO);
// 		}
// 		(*i)++;
// 	}
// }

// int	builtin_echo(t_table_cmd *table)
// {
// 	int	i;
// 	int	n_option;

// 	// if (!proc)
// 	// 	return ;
// 	n_option = 0;
// 	i = 0;
// 	while (proc->tokens[i].word && proc->tokens[i].type != WORD)
// 		i++;
// 	if (proc->tokens[i].word)
// 	{
// 		skip_n_options(proc->tokens, &i, &n_option);
// 		skip_non_words(proc->tokens, &i);
// 		print_one_word(proc->tokens, &i);
// 		print_next_wds(proc->tokens, &i);
// 	}
// 	if (!n_option)
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// 	return (EXIT_SUCCESS);
// }
