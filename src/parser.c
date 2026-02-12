/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedu <wedu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:30:00 by wedu              #+#    #+#             */
/*   Updated: 2026/02/12 17:36:14 by wedu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = ft_malloc(sizeof(t_command));
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->separator = TOKEN_EOF;
	cmd->next = NULL;
	return (cmd);
}

static t_redir	*create_redirection(int type, char *file)
{
	t_redir	*redir;

	redir = ft_malloc(sizeof(t_redir));
	redir->type = type;
	redir->file = ft_strdup(file);
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

static void	add_redirection(t_command *cmd, t_redir *redir)
{
	t_redir	*current;

	if (!cmd->redirections)
	{
		cmd->redirections = redir;
		return ;
	}
	current = cmd->redirections;
	while (current->next)
		current = current->next;
	current->next = redir;
}

static void	add_arg_to_command(t_command *cmd, char *arg)
{
	char	**new_args;
	int		count;
	int		i;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_args = ft_malloc(sizeof(char *) * (count + 2));
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[count] = ft_strdup(arg);
	new_args[count + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
}

static t_command	*parse_single_command(t_token **tokens)
{
	t_command	*cmd;
	t_redir		*redir;
	int			redir_type;

	cmd = create_command();
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_SEMICOLON)
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			add_arg_to_command(cmd, (*tokens)->value);
			*tokens = (*tokens)->next;
		}
		else if ((*tokens)->type >= TOKEN_REDIR_IN
			&& (*tokens)->type <= TOKEN_REDIR_HEREDOC)
		{
			redir_type = (*tokens)->type;
			*tokens = (*tokens)->next;
			if (*tokens && (*tokens)->type == TOKEN_WORD)
			{
				redir = create_redirection(redir_type, (*tokens)->value);
				add_redirection(cmd, redir);
				*tokens = (*tokens)->next;
			}
			else
			{
				printf("minishell: syntax error near unexpected token\n");
				free_commands(cmd);
				return (NULL);
			}
		}
		else
			*tokens = (*tokens)->next;
	}
	return (cmd);
}

t_command	*parse_commands(t_token *tokens)
{
	t_command	*commands;
	t_command	*cmd;
	t_command	*current;
	int			separator_type;

	commands = NULL;
	current = NULL;
	while (tokens)
	{
		cmd = parse_single_command(&tokens);
		if (!cmd)
		{
			free_commands(commands);
			return (NULL);
		}
		if (tokens && (tokens->type == TOKEN_PIPE
				|| tokens->type == TOKEN_SEMICOLON))
		{
			separator_type = tokens->type;
			tokens = tokens->next;
		}
		else
			separator_type = TOKEN_EOF;
		cmd->separator = separator_type;
		if (!commands)
		{
			commands = cmd;
			current = cmd;
		}
		else
		{
			current->next = cmd;
			current = cmd;
		}
	}
	return (commands);
}

void	free_commands(t_command *commands)
{
	t_command	*current;
	t_command	*next;
	t_redir		*redir;
	t_redir		*redir_next;
	int			i;

	current = commands;
	while (current)
	{
		next = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i])
				free(current->args[i++]);
			free(current->args);
		}
		redir = current->redirections;
		while (redir)
		{
			redir_next = redir->next;
			free(redir->file);
			free(redir);
			redir = redir_next;
		}
		free(current);
		current = next;
	}
}
