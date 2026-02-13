/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyuandu <weiyuandu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:30:00 by wedu              #+#    #+#             */
/*   Updated: 2026/02/12 22:35:32 by weiyuandu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//这部分就是新建一个token节点
static t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = ft_malloc(sizeof(t_token));
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}
//这部分就是将token加到对应的链表里面
static void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

static int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static char	*extract_word(char *line, int *i)
{
	int		start;
	int		len;
	char	*word;
	char	quote_char;
	int		in_quotes;

	start = *i; //记录单词开始位置
	in_quotes = 0; //记录是否在引号内
	quote_char = 0; //引号类型是单引号还是双引号
	while (line[*i])
	{
		if (!in_quotes && (line[*i] == '\'' || line[*i] == '"'))
		{
			in_quotes = 1; //进入引号
			quote_char = line[*i]; //引号类型是
		}
		else if (in_quotes && line[*i] == quote_char) //如果引号类型匹配
			in_quotes = 0; //退出引号
		else if (!in_quotes && (is_whitespace(line[*i])
				|| is_special_char(line[*i]))) //只在引号外遇到空白符或者特殊字符才停止
			break ;
		(*i)++;
	}
	len = *i - start;
	word = malloc(sizeof(char) * (len + 1)); // 记录下单词
	if (!word)
		return (NULL);
	ft_strlcpy(word, line + start, len + 1);
	word[len] = '\0';
	return (word);
}
//这部分就是判断每个token的类型，然后将其加到tokens链表里
t_token	*tokenize(char *line)
{
	t_token	*tokens;
	t_token	*token;
	char	*word;
	int		i;

	tokens = NULL;
	i = 0;
	while (line[i])
	{
		while (is_whitespace(line[i])) //跳过所有的空格
			i++;
		if (!line[i])
			break ;
		if (line[i] == '|')
		{
			token = create_token("|", TOKEN_PIPE);
			add_token(&tokens, token);
			i++;
		}
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			token = create_token("<<", TOKEN_REDIR_HEREDOC);
			add_token(&tokens, token);
			i += 2;
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			token = create_token(">>", TOKEN_REDIR_APPEND);
			add_token(&tokens, token);
			i += 2;
		}
		else if (line[i] == '<')
		{
			token = create_token("<", TOKEN_REDIR_IN);
			add_token(&tokens, token);
			i++;
		}
		else if (line[i] == '>')
		{
			token = create_token(">", TOKEN_REDIR_OUT);
			add_token(&tokens, token);
			i++;
		}
		else
		{
			word = extract_word(line, &i);
			if (word)
			{
				token = create_token(word, TOKEN_WORD);
				add_token(&tokens, token);
				free(word);
			}
		}
	}
	return (tokens);
}


//释放所有的tokens
void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
