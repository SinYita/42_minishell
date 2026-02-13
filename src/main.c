/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyuandu <weiyuandu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:14:12 by wedu              #+#    #+#             */
/*   Updated: 2026/02/12 22:15:03 by weiyuandu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//dup函数的作用是为了复制文件描述符，创建同一个文件的新文件描述符
//dup2函数的作用：让 newfd 指向和 oldfd 相同的文件
//备份stdin和stdout是因为中间可能会重定向，但是之后需要恢复

// STDIN_FILENO = 0 (标准输入，通常是键盘)
// STDOUT_FILENO = 1 (标准输出，通常是终端)
// STDERR_FILENO = 2 (标准错误，通常是终端)
static void	init_shell(t_shell *shell, char **envp)
{
	shell->env = init_env(envp);
	shell->commands = NULL;
	shell->envp = envp;
	shell->exit_status = 0;
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
}
static void	handle_empty_line(void)
{
	/* Do nothing for empty lines */
}

static int	is_only_spaces(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		shell;
	char		*line;
	t_token		*tokens;
	t_command	*commands;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	setup_signals();
	while (1)
	{
		line = readline(PROMPT); //这里解释下readline的逻辑
		if (!line) //如果用户按下ctrl+D，这个时候readline返回EOF
		{
			if (isatty(STDIN_FILENO)) //判断一个文件描述符是否连接到 终端（terminal, tty）
				printf("exit\n");
			break ;
		}
		if (g_signal_received == SIGINT) //如果接收到ctrl+C，就重新刷新
		{
			shell.exit_status = 130;
			g_signal_received = 0;
		}
		if (is_only_spaces(line))
		{
			handle_empty_line(); //如果输入全是space等，什么都不做
			free(line);
			continue ;
		}
		add_history(line);//这个是readline的库，用来记录历史命令
		tokens = tokenize(line);
		free(line);
		if (!tokens)
			continue ;
		commands = parse_commands(tokens);
		free_tokens(tokens);
		if (!commands)
			continue ;
		shell.exit_status = execute_commands(commands, &shell);
		free_commands(commands);
	}
	free_env(shell.env);
	close(shell.stdin_backup);
	close(shell.stdout_backup);
	return (shell.exit_status);
}
