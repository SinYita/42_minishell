/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyuandu <weiyuandu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:30:00 by wedu              #+#    #+#             */
/*   Updated: 2026/02/13 00:34:29 by weiyuandu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static int	is_alpha_char(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

static int	is_alnum_char(char c)
{
	return (is_alpha_char(c) || (c >= '0' && c <= '9'));
}

char	*find_command_path(char *cmd, t_shell *shell)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	char	*temp;
	int		i;

	if (!cmd)
		return (NULL);
	/* Don't check local files for commands without slash - only PATH lookup */
	path_env = get_env_value(shell, "PATH");
	if (!path_env)
		return (NULL);
	paths = split_string(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK) == 0)
		{
			i = 0;
			while (paths[i])
				free(paths[i++]);
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (NULL);
}

static int	check_file_accessibility(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) != 0)
	{
		if (errno == ENOENT)
			return (127); /* No such file or directory */
		else
			return (127); /* Other stat errors */
	}
	if (S_ISDIR(file_stat.st_mode))
		return (126); /* Is a directory */
	if (access(path, X_OK) != 0)
		return (126); /* Permission denied */
	return (0);       /* Executable file */
}

static int	execute_external_command(t_command *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;
	char	**envp;
	int		error_type;
			struct stat file_stat;

	/* Handle empty command */
	if (!cmd->args[0] || !cmd->args[0][0])
		return (0);
	/* Check if command contains a slash (absolute or relative path) */
	if (ft_strchr(cmd->args[0], '/'))
	{
		error_type = check_file_accessibility(cmd->args[0]);
		if (error_type == 126)
		{
			if (stat(cmd->args[0], &file_stat) == 0
				&& S_ISDIR(file_stat.st_mode))
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(cmd->args[0], STDERR_FILENO);
				ft_putendl_fd(": Is a directory", STDERR_FILENO);
			}
			else
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd(cmd->args[0], STDERR_FILENO);
				ft_putendl_fd(": Permission denied", STDERR_FILENO);
			}
			return (126);
		}
		else if (error_type == 127)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
			return (127);
		}
		cmd_path = ft_strdup(cmd->args[0]);
	}
	else
	{
		cmd_path = find_command_path(cmd->args[0], shell);
		if (!cmd_path)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
			return (127);
		}
	}
	pid = fork();
	if (pid == 0)
	{
		envp = env_to_array(shell);
		execve(cmd_path, cmd->args, envp);
		perror("execve");
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		free(cmd_path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	else
	{
		perror("fork");
		free(cmd_path);
		return (1);
	}
	return (0);
}

//是变量赋值
static int	is_variable_assignment(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	/* First character must be a letter or underscore */
	if (!is_alpha_char(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	/* Find the equals sign */
	while (arg[i] && arg[i] != '=')
	{
		if (!is_alnum_char(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (arg[i] == '=');
}
//执行变量赋值
static int	execute_variable_assignment(char *assignment, t_shell *shell)
{
	char	*equals;
	char	*key;
	char	*value;

	equals = ft_strchr(assignment, '=');
	if (!equals)
		return (1);
	key = ft_malloc(equals - assignment + 1);
	ft_strlcpy(key, assignment, (equals - assignment) + 1);
	value = equals + 1;
	set_env_value(shell, key, value);
	free(key);
	return (0);
}

static int	execute_command_no_redirections(t_command *cmd, t_shell *shell)
{
	int		exit_status;
	int		i;
	int		j;
	char	**expanded_args;
	char	**original_args;

	if (!cmd || !cmd->args)
		return (0);
	if (!cmd->args[0] || !cmd->args[0][0])
		return (0);
	//处理VAR = value
	if (cmd->args[0] && is_variable_assignment(cmd->args[0]) && !cmd->args[1])
		return (execute_variable_assignment(cmd->args[0], shell));
	//进行变量展开
	i = 0;
	while (cmd->args[i])
		i++;
	expanded_args = ft_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (cmd->args[i])
	{
		expanded_args[i] = process_quotes_and_variables(cmd->args[i], shell);
		i++;
	}
	expanded_args[i] = NULL;
	//移除所有的空变量
	j = 0;
	i = 0;
	while (expanded_args[i])
	{
		if (expanded_args[i][0] != '\0')
		{
			if (j != i)
			{
				expanded_args[j] = expanded_args[i];
				expanded_args[i] = NULL;
			}
			j++;
		}
		else
		{
			free(expanded_args[i]);
			expanded_args[i] = NULL;
		}
		i++;
	}
	expanded_args[j] = NULL;
	/* If no command after expansion, return success */
	if (j == 0 || !expanded_args[0])
	{
		i = 0;
		while (expanded_args[i])
			free(expanded_args[i++]);
		free(expanded_args);
		return (0);
	}
	/* Temporarily replace args for execution */
	original_args = cmd->args;
	cmd->args = expanded_args;
	if (is_builtin(cmd->args[0]))
		exit_status = execute_builtin(cmd, shell);
	else
		exit_status = execute_external_command(cmd, shell);
	/* Restore original args and free expanded ones */
	cmd->args = original_args;
	i = 0;
	while (expanded_args[i])
		free(expanded_args[i++]);
	free(expanded_args);
	return (exit_status);
}

int	execute_command(t_command *cmd, t_shell *shell)
{
	int		exit_status;
	int		i;
	int		j;
	char	**expanded_args;
	char	**original_args;

	if (!cmd || !cmd->args)
		return (0);
	/* Check if first argument is empty or null */
	if (!cmd->args[0] || !cmd->args[0][0])
		return (0);
	/* Check if it's a variable assignment without command */
	if (cmd->args[0] && is_variable_assignment(cmd->args[0]) && !cmd->args[1])
		return (execute_variable_assignment(cmd->args[0], shell));
	/* Expand variables in arguments */
	i = 0;
	while (cmd->args[i])
		i++;
	expanded_args = ft_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (cmd->args[i])
	{
		expanded_args[i] = process_quotes_and_variables(cmd->args[i], shell);
		i++;
	}
	expanded_args[i] = NULL;
	/* Remove empty arguments and shift remaining ones */
	j = 0;
	i = 0;
	while (expanded_args[i])
	{
		if (expanded_args[i][0] != '\0')
		{
			if (j != i)
			{
				expanded_args[j] = expanded_args[i];
				expanded_args[i] = NULL;
			}
			j++;
		}
		else
		{
			free(expanded_args[i]);
			expanded_args[i] = NULL;
		}
		i++;
	}
	expanded_args[j] = NULL;
	/* If no command after expansion, return success */
	if (j == 0 || !expanded_args[0])
	{
		i = 0;
		while (expanded_args[i])
			free(expanded_args[i++]);
		free(expanded_args);
		return (0);
	}
	/* Temporarily replace args for execution */
	original_args = cmd->args;
	cmd->args = expanded_args;
	if (setup_redirections(cmd->redirections) != 0)
	{
		cmd->args = original_args;
		i = 0;
		while (expanded_args[i])
			free(expanded_args[i++]);
		free(expanded_args);
		return (1);
	}
	if (is_builtin(cmd->args[0]))
		exit_status = execute_builtin(cmd, shell);
	else
		exit_status = execute_external_command(cmd, shell);
	restore_redirections(shell);
	/* Restore original args and free expanded ones */
	cmd->args = original_args;
	i = 0;
	while (expanded_args[i])
		free(expanded_args[i++]);
	free(expanded_args);
	return (exit_status);
}

//处理管道然后执行对应的命令
int	execute_commands(t_command *commands, t_shell *shell)
{
	t_command	*current;
	t_command	*pipeline_start;
	t_command	*pipeline_end;
	int			exit_status;
	t_command	*next_sequence;

	exit_status = 0;
	current = commands;
	while (current)
	{
		pipeline_start = current;
		pipeline_end = current;
		/* Find the end of the current pipeline */
		while (pipeline_end && pipeline_end->separator == TOKEN_PIPE)
			pipeline_end = pipeline_end->next;
		/* Execute this pipeline or single command */
		if (pipeline_start == pipeline_end) //如果是单个命令，就直接执行
		{
			/* Single command - execute directly */
			exit_status = execute_command(current, shell);
			shell->exit_status = exit_status;
			current = current->next;
		}
		else
		{
			/* Pipeline - temporarily terminate and execute */
			next_sequence = pipeline_end->next;
			pipeline_end->next = NULL;
			exit_status = execute_pipeline(pipeline_start, shell);
			shell->exit_status = exit_status;
			pipeline_end->next = next_sequence;
			current = next_sequence;
		}
	}
	return (exit_status);
}

//执行对应的管道
int	execute_pipeline(t_command *commands, t_shell *shell)
{
	t_command	*current;
	int			pipe_fd[2];
	int			prev_fd;
	pid_t		*pids;
	int			status;
	int			last_exit_status;
	int			cmd_count;
	int			i;

	if (!commands)
		return (0);
	if (!commands->next)
		return (execute_command(commands, shell));
	/* Count commands */
	cmd_count = 0;
	current = commands; //统计命令总数
	while (current)
	{
		cmd_count++;
		current = current->next;
	}
	pids = ft_malloc(sizeof(pid_t) * cmd_count);//需要分配对应数量的进程
	prev_fd = -1;
	last_exit_status = 0;
	current = commands;
	i = 0;
	while (current)
	{
		if (current->next && pipe(pipe_fd) == -1) //只有非最后一个命令才创建管道
		{
			perror("pipe");
			free(pids);
			return (1);
		}
		pids[i] = fork(); 
		if (pids[i] == 0) //当前是子进程
		{
			//设置输入重定向
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			//设置输出重定向
			if (current->next)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
				close(pipe_fd[0]);
			}
			//处理本身的重定向
			if (current->redirections
				&& setup_redirections(current->redirections) != 0)
			{
				free(pids);
				exit(1);
			}
			free(pids);//子进程不需要这个数组
			exit(execute_command_no_redirections(current, shell)); //这部分什么意思？
		}
		else if (pids[i] > 0)//父进程
		{
			if (prev_fd != -1)
				close(prev_fd); //关闭上一个管道的读端
			if (current->next)
			{
				close(pipe_fd[1]); //关闭写端口
				prev_fd = pipe_fd[0]; //保存读端口给下一个命令
			}
		}
		else
		{
			perror("fork");
			free(pids);
			return (1);
		}
		current = current->next;
		i++;
	}
	/* Wait for all processes, capture last one's exit status */
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1) //如果是最后一个进程，捕获它的退出状态
		{
			if (WIFEXITED(status))
				last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	free(pids);
	return (last_exit_status);
}
