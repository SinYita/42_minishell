/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedu <wedu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:24:07 by wedu              #+#    #+#             */
/*   Updated: 2026/02/12 17:36:16 by wedu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "minishell$ "
# define MAX_ARGS 1024
# define MAX_PIPES 100

extern int				g_signal_received;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_SEMICOLON,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_EOF
}						t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef struct s_redir
{
	int					type;
	char				*file;
	int					fd;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**args;
	t_redir				*redirections;
	int					separator;
	struct s_command	*next;
}						t_command;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	t_env				*env;
	t_command			*commands;
	char				**envp;
	int					exit_status;
	int					stdin_backup;
	int					stdout_backup;
}						t_shell;

/* Parsing functions */
t_token					*tokenize(char *line);
t_command				*parse_commands(t_token *tokens);
void					free_tokens(t_token *tokens);
void					free_commands(t_command *commands);

/* Built-in commands */
int						is_builtin(char *cmd);
int						execute_builtin(t_command *cmd, t_shell *shell);
int						builtin_echo(char **args);
int						builtin_cd(char **args, t_shell *shell);
int						builtin_pwd(void);
int						builtin_export(char **args, t_shell *shell);
int						builtin_unset(char **args, t_shell *shell);
int						builtin_env(t_shell *shell);
int						builtin_exit(char **args, t_shell *shell);

/* Execution */
int						execute_command(t_command *cmd, t_shell *shell);
int						execute_pipeline(t_command *commands, t_shell *shell);
int						execute_commands(t_command *commands, t_shell *shell);
char					*find_command_path(char *cmd, t_shell *shell);

/* Environment */
t_env					*init_env(char **envp);
char					*get_env_value(t_shell *shell, char *key);
void					set_env_value(t_shell *shell, char *key, char *value);
void					unset_env_value(t_shell *shell, char *key);
char					**env_to_array(t_shell *shell);
void					free_env(t_env *env);

/* Signal handling */
void					setup_signals(void);
void					handle_sigint(int sig);
void					handle_sigquit(int sig);

/* Redirections */
int						setup_redirections(t_redir *redir);
void					restore_redirections(t_shell *shell);
int						handle_heredoc(char *delimiter);

/* Utils */
char					*expand_variables(char *str, t_shell *shell);
char					*process_quotes_and_variables(char *str,
							t_shell *shell);
char					**split_string(char *str, char delimiter);
char					*join_strings(char *s1, char *s2);
char					*trim_quotes(char *str);
void					*ft_malloc(size_t size);
int						ft_strcmp(char *s1, char *s2);

#endif
