/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedu <wedu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:14:12 by wedu              #+#    #+#             */
/*   Updated: 2026/02/12 17:36:18 by wedu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell(t_shell *shell, char **envp)
{
	shell->env = init_env(envp);
	shell->commands = NULL;
	shell->envp = envp;
	shell->exit_status = 0;
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
}

static char	*process_input(char *line, t_shell *shell)
{
	(void)shell;
	if (!line)
		return (NULL);
	return (ft_strdup(line));
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
	char		*processed_line;
	t_token		*tokens;
	t_command	*commands;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	setup_signals();
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			break ;
		}
		if (g_signal_received == SIGINT)
		{
			shell.exit_status = 130;
			g_signal_received = 0;
		}
		if (is_only_spaces(line))
		{
			handle_empty_line();
			free(line);
			continue ;
		}
		add_history(line);
		processed_line = process_input(line, &shell);
		free(line);
		if (!processed_line)
			continue ;
		tokens = tokenize(processed_line);
		free(processed_line);
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
