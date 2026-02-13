/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyuandu <weiyuandu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:30:00 by wedu              #+#    #+#             */
/*   Updated: 2026/02/12 23:17:32 by weiyuandu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//同样是链表结构，创建一个新的node
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
//创建一个重定向节点
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
//将一个重定向节点连接到指定命令的重定向链表尾部
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
//这里可以考虑使用栈空间存储参数
static void	add_arg_to_command(t_command *cmd, char *arg)
{
	char	**new_args;
	int		count;
	int		i;

	//计算当前的参数数量
	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	//分配更大的参数空间
	new_args = ft_malloc(sizeof(char *) * (count + 2));
	i = 0;
	//复制所有的参数进去
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	//复制新参数进去
	new_args[count] = ft_strdup(arg);
	new_args[count + 1] = NULL;
	//更新command的参数
	free(cmd->args);
	cmd->args = new_args;
}

static t_command	*parse_single_command(t_token **tokens)
{
	t_command	*cmd;
	t_redir		*redir;
	int			redir_type;

	cmd = create_command();
	while (*tokens && (*tokens)->type != TOKEN_PIPE)
	{
		if ((*tokens)->type == TOKEN_WORD)
		{
			add_arg_to_command(cmd, (*tokens)->value);
			*tokens = (*tokens)->next;
		}
		else if ((*tokens)->type >= TOKEN_REDIR_IN
			&& (*tokens)->type <= TOKEN_REDIR_HEREDOC)
		{
			redir_type = (*tokens)->type; //记录重定向的类型
			*tokens = (*tokens)->next; //移动到下一个token
			if (*tokens && (*tokens)->type == TOKEN_WORD) //成功找到文件名
			{
				redir = create_redirection(redir_type, (*tokens)->value);
				add_redirection(cmd, redir);
				*tokens = (*tokens)->next;
			}
			else //没有找到文件名
			{
				printf("minishell: syntax error near unexpected token\n");
				free_commands(cmd);
				return (NULL);
			}
		}
		else //这里存疑？？需不需要保留
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
		cmd = parse_single_command(&tokens); //会停留在管道符或者EOF
		if (!cmd) //如果解析失败就清理所有的commands
		{
			free_commands(commands);
			return (NULL);
		}
		if (tokens && tokens->type == TOKEN_PIPE)//如果停留在管道符的话
		{
			separator_type = tokens->type; //用来指示执行器
			tokens = tokens->next;
		}
		else
			separator_type = TOKEN_EOF; //告诉执行器后面没有管道了
		cmd->separator = separator_type; //执行器看cmd的指示器来执行命令
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

//释放所有command节点
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
