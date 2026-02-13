/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyuandu <weiyuandu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:30:00 by wedu              #+#    #+#             */
/*   Updated: 2026/02/13 12:51:28 by weiyuandu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

//用来输出错误信息
static void	put_err_parts(const char *a, const char *b, const char *c)
{
	if (a)
		ft_putstr_fd((char *)a, STDERR_FILENO);
	if (b)
		ft_putstr_fd((char *)b, STDERR_FILENO);
	if (c)
		ft_putstr_fd((char *)c, STDERR_FILENO);
}

//atoi，但是比atoi更严格的转换，确保str完全是数字才可以
static int	parse_long_strict(const char *str, long *out)
{
	unsigned long long	res;
	unsigned long long	limit;
	int					sign;
	int					i;
	int					digit;

	if (!str || !str[0])
		return (0);
	res = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		return (0);
	limit = (sign == 1) ? (unsigned long long)LONG_MAX : (unsigned long long)LONG_MAX
		+ 1ULL;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (res > (limit - (unsigned long long)digit) / 10ULL)
			return (0);
		res = res * 10ULL + (unsigned long long)digit;
		i++;
	}
	if (str[i] != '\0')
		return (0);
	if (sign == 1)
		*out = (long)res;
	else
		*out = -(long)res;
	return (1);
}

int	builtin_cd(char **args, t_shell *shell)
{
	char	*path;
	char	*home;
	char	*oldpwd;
	char	*cwd;

	if (args[1] && args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (!args[1])
	{
		home = get_env_value(shell, "HOME");
		path = home ? home : "/";
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		path = get_env_value(shell, "OLDPWD");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
			return (1);
		}
		ft_putendl_fd(path, STDOUT_FILENO);
	}
	else
		path = args[1];
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		perror("cd");
		if (oldpwd)
			free(oldpwd);
		return (1);
	}
	if (oldpwd)
	{
		set_env_value(shell, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		set_env_value(shell, "PWD", cwd);
		free(cwd);
	}
	return (0);
}

//用来检测是否是合法的标志符
// export MY_VAR=value      # MY_VAR ✓
// export _private=secret   # _private ✓  
// export ABC123=test       # ABC123 ✓
// unset HOME               # HOME ✓
// export 123VAR=value      # ❌ 数字开头
// export MY-VAR=value      # ❌ 包含连字符
// export MY VAR=value      # ❌ 包含空格
// export @SPECIAL=value    # ❌ 特殊字符开头
static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(str[0] >= 'a' && str[0] <= 'z') && !(str[0] >= 'A' && str[0] <= 'Z')
		&& str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A'
				&& str[i] <= 'Z') && !(str[i] >= '0' && str[i] <= '9')
			&& str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
//用来数envp中的env个数，可以使用listcount替换
static int	count_env_vars(t_env *env)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
//使用export的时候，必须按照字母顺序输出
static void	sort_env_array(t_env **array, int count)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (ft_strcmp(array[j]->key, array[j + 1]->key) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
//输出格式 将envp进行排序然后格式化输出
//可以使用list直接进行排序
static void	print_export_format(t_shell *shell)
{
	t_env	*current;
	t_env	**env_array;
	int		count;
	int		i;

	count = count_env_vars(shell->env);
	if (count == 0)
		return ;
	env_array = ft_malloc(sizeof(t_env *) * count);
	current = shell->env;
	i = 0;
	while (current && i < count)
	{
		env_array[i] = current;
		current = current->next;
		i++;
	}
	sort_env_array(env_array, count); //这部分多余了
	i = 0;
	while (i < count)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_array[i]->key, STDOUT_FILENO);
		if (env_array[i]->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env_array[i]->value, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		else
			ft_putendl_fd("", STDOUT_FILENO);
		i++;
	}
	free(env_array);
}

int	builtin_export(char **args, t_shell *shell)
{
	int		i;
	char	*key;
	char	*value;
	char	*equals;

	if (!args[1])
	{
		print_export_format(shell);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			put_err_parts("minishell: export: `", args[i],
				"': not a valid identifier\n");
			return (1);
		}
		equals = ft_strchr(args[i], '=');
		if (equals)
		{
			*equals = '\0';
			key = args[i];
			value = equals + 1;
			set_env_value(shell, key, value);
			*equals = '=';
		}
		else
			set_env_value(shell, args[i], NULL);
		i++;
	}
	return (0);
}

int	builtin_unset(char **args, t_shell *shell)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			put_err_parts("minishell: unset: `", args[i],
				"': not a valid identifier\n");
			continue ;
		}
		unset_env_value(shell, args[i]);
		i++;
	}
	return (0);
}

int	builtin_exit(char **args, t_shell *shell)
{
	int		exit_code;
	long	num;

	ft_putendl_fd("exit", STDOUT_FILENO);
	exit_code = shell->exit_status;
	if (args[1])
	{
		if (args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return (1);
		}
		if (!parse_long_strict(args[1], &num))
		{
			put_err_parts("minishell: exit: ", args[1],
				": numeric argument required\n");
			exit(2);
		}
		exit_code = (unsigned char)num;
	}
	exit(exit_code);
}
