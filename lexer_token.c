/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echrysta <echrysta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:26:48 by mbutter           #+#    #+#             */
/*   Updated: 2022/05/10 16:47:59 by echrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int lexer_token_pipe(char *input, int *i, t_token **list_token)
{
	char *token_str;
	t_token	*token;

	if (input[*i] == '|')
	{
		token_str = ft_substr(input, *i, 1);
		if (token_str == NULL)
			return (1);
		token = token_new(e_pipe, token_str);
		if (token == NULL)
			return (1);
		token_add_back(list_token, token);
		free(token_str);
		(*i)++;
	}
	return (0);
}

int lexer_token_bracket(char *input, int *i, t_token **list_token)
{
	char *token_str;
	t_token	*token;

	if (input[*i] == '(' || input[*i] == ')')
	{
		token_str = ft_substr(input, *i, 1);
		if (token_str == NULL)
			return(1);
		if (input[*i] == '(')
			token = token_new(e_left_bracket, token_str);
		else
			token = token_new(e_right_bracket, token_str);
		if (token == NULL)
			return (1);
		token_add_back(list_token, token);
		free(token_str);
		(*i)++;
	}
	return (0);
}

int lexer_token_redir(char *input, int *i, t_token **list_token)
{
	char *token_str;
	t_token	*token;
	int len;

	len = 0;
	/* while (ft_isdigit(input[*i + len]))
		len++; */
	if (input[*i] == '<' || input[*i] == '>')
	{
		len++;
		if (input[*i + len] == input[*i])
			len++;
		token_str = ft_substr(input, *i, len);
		if (token_str == NULL)
			return (1);
		token = token_new(e_redir, token_str);
		if (token == NULL)
			return (1);
		token_add_back(list_token, token);
		free(token_str);
		(*i) += len;
	}
	return (0);
}

int lexer_token_quote(char *input, int *i, t_token **list_token)
{
	char *token_str;
	t_token	*token;
	int len;

	len = ft_quotelen(&input[*i]);
	if (len == -1)
		return (1);
	if (len > 0)
	{
		token_str = ft_substr(input, *i + 1, len - 2);
		if (token_str == NULL)
			return (1);
		if (input[*i] == '\"')
			token = token_new(e_word | e_double_quote, token_str);
		else
			token = token_new(e_word | e_single_quote, token_str);
		if (token == NULL)
			return (1);
		token_add_back(list_token, token);
		free(token_str);
		(*i) += len;
		if (!ft_isspace(input[*i]) && !ft_strchr("()<>|", input[*i]))
			token->connect = 1;
	}
	return (0);
}

int lexer_token_word(char *input, int *i, t_token **list_token)
{
	char *token_str;
	t_token	*token;
	int len;

	len = ft_wordlen(&input[*i]);
	if (len == -1)
		return (1);
	if (len > 0)
	{
		token_str = ft_substr(input, *i, len);
		if (token_str == NULL)
			return (1);
		token = token_new(e_word, token_str);
		if (token == NULL)
			return (1);
		token_add_back(list_token, token);
		free(token_str);
		(*i) += len;
		if (!ft_isspace(input[*i]) && !ft_strchr("()<>|", input[*i]))
			token->connect = 1;
	}
	return (0);
}