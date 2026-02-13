/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyuandu <weiyuandu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:30:00 by wedu              #+#    #+#             */
/*   Updated: 2026/02/12 23:18:03 by weiyuandu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int	handle_heredoc(char *delimiter) {
  int pipe_fd[2];
  char *line;
  pid_t pid;

  if (pipe(pipe_fd) == -1) {
    perror("pipe");
    return (-1);
  }
  pid = fork();
  if (pid == 0) {
    close(pipe_fd[0]);
    while (1) {
      line = readline("> ");
      if (!line || ft_strcmp(line, delimiter) == 0) {
        if (line)
          free(line);
        break ;
      }
      write(pipe_fd[1], line, ft_strlen(line));
      write(pipe_fd[1], "\n", 1);
      free(line);
    }
    close(pipe_fd[1]);
    exit(0);
  } else if (pid > 0) {
    close(pipe_fd[1]);
    waitpid(pid, NULL, 0);
    return (pipe_fd[0]);
  } else {
    perror("fork");
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    return (-1);
  }
}

int	setup_redirections(t_redir *redir) {
  t_redir *current;
  char *filename;
  int final_stdout_fd = -1;
  int final_stdin_fd = -1;
  int temp_fd;

  /* Process all redirections in order, stop at first error */
  current = redir;
  while (current) {
    filename = process_quotes_and_variables(current->file, NULL);

    if (current->type == TOKEN_REDIR_IN) {
      temp_fd = open(filename, O_RDONLY);
      if (temp_fd == -1) {
        if (errno == ENOENT) {
          ft_putstr_fd("minishell: ", STDERR_FILENO);
          ft_putstr_fd(filename, STDERR_FILENO);
          ft_putendl_fd(": No such file or directory", STDERR_FILENO);
        } else {
          ft_putstr_fd("minishell: ", STDERR_FILENO);
          ft_putstr_fd(filename, STDERR_FILENO);
          ft_putendl_fd(": Permission denied", STDERR_FILENO);
        }
        if (filename)
          free(filename);
        if (final_stdin_fd != -1)
          close(final_stdin_fd);
        if (final_stdout_fd != -1)
          close(final_stdout_fd);
        return (1);
      } else {
        if (final_stdin_fd != -1)
          close(final_stdin_fd);
        final_stdin_fd = temp_fd;
      }
    } else if (current->type == TOKEN_REDIR_OUT) {
      temp_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (temp_fd == -1) {
        if (errno == EACCES) {
          ft_putstr_fd("minishell: ", STDERR_FILENO);
          ft_putstr_fd(filename, STDERR_FILENO);
          ft_putendl_fd(": Permission denied", STDERR_FILENO);
        } else {
          ft_putstr_fd("minishell: ", STDERR_FILENO);
          ft_putstr_fd(filename, STDERR_FILENO);
          ft_putendl_fd(": No such file or directory", STDERR_FILENO);
        }
        if (filename)
          free(filename);
        if (final_stdin_fd != -1)
          close(final_stdin_fd);
        if (final_stdout_fd != -1)
          close(final_stdout_fd);
        return (1);
      } else {
        if (final_stdout_fd != -1)
          close(final_stdout_fd);
        final_stdout_fd = temp_fd;
      }
    } else if (current->type == TOKEN_REDIR_APPEND) {
      temp_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
      if (temp_fd == -1) {
        if (errno == EACCES) {
          ft_putstr_fd("minishell: ", STDERR_FILENO);
          ft_putstr_fd(filename, STDERR_FILENO);
          ft_putendl_fd(": Permission denied", STDERR_FILENO);
        } else {
          ft_putstr_fd("minishell: ", STDERR_FILENO);
          ft_putstr_fd(filename, STDERR_FILENO);
          ft_putendl_fd(": No such file or directory", STDERR_FILENO);
        }
        if (filename)
          free(filename);
        if (final_stdin_fd != -1)
          close(final_stdin_fd);
        if (final_stdout_fd != -1)
          close(final_stdout_fd);
        return (1);
      } else {
        if (final_stdout_fd != -1)
          close(final_stdout_fd);
        final_stdout_fd = temp_fd;
      }
    } else if (current->type == TOKEN_REDIR_HEREDOC) {
      temp_fd = handle_heredoc(filename);
      if (temp_fd == -1) {
        if (filename)
          free(filename);
        if (final_stdin_fd != -1)
          close(final_stdin_fd);
        if (final_stdout_fd != -1)
          close(final_stdout_fd);
        return (1);
      } else {
        if (final_stdin_fd != -1)
          close(final_stdin_fd);
        final_stdin_fd = temp_fd;
      }
    }

    if (filename)
      free(filename);
    current = current->next;
  }

  /* Apply the final redirections */
  if (final_stdin_fd != -1) {
    dup2(final_stdin_fd, STDIN_FILENO);
    close(final_stdin_fd);
  }
  if (final_stdout_fd != -1) {
    dup2(final_stdout_fd, STDOUT_FILENO);
    close(final_stdout_fd);
  }

  return (0);
}

void	restore_redirections(t_shell *shell) {
  dup2(shell->stdin_backup, STDIN_FILENO);
  dup2(shell->stdout_backup, STDOUT_FILENO);
}
