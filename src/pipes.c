/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyuandu <weiyuandu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:30:00 by wedu              #+#    #+#             */
/*   Updated: 2026/02/13 12:57:51 by weiyuandu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//这个文件使用pipe进行命名不合适，查看一下实际的内容

#include "minishell.h"

//这里就是ft_split，用来将一维字符串分割为二维的数组
char	**split_string(char *str, char delimiter)
{
	char	**result;
	int		count;
	int		i;
	int		j;
	int		start;
	int		len;

	if (!str)
		return (NULL);
	count = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == delimiter)
			count++;
		i++;
	}
	result = ft_malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == delimiter || str[i + 1] == '\0')
		{
			len = i - start;
			if (str[i + 1] == '\0' && str[i] != delimiter)
				len++;
			result[j] = ft_malloc(sizeof(char) * (len + 1));
			ft_strlcpy(result[j], str + start, len + 1);
			result[j][len] = '\0';
			j++;
			start = i + 1;
		}
		i++;
	}
	result[j] = NULL;
	return (result);
}
//多此一举，可以进行删除
char	*join_strings(char *s1, char *s2)
{
	return (ft_strjoin(s1, s2));
}
//用来去除字符串最外围的匹配引号
//里面的\没有用，可以直接删除掉（没有要求）
char	*trim_quotes(char *str)
{
	int		len;
	char	*trimmed;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\''
				&& str[len - 1] == '\'')))
	{
		trimmed = ft_malloc(sizeof(char) * (len - 1));
		ft_strlcpy(trimmed, str + 1, len - 1);
		trimmed[len - 2] = '\0';
		return (trimmed);
	}
	return (ft_strdup(str));
}
//这个部分太过度工程了，需要大量简化
//不需要考虑\符号，此外里面的很多内容可以使用isalpha或者isnum进行简化
char	*process_quotes_and_variables(char *str, t_shell *shell)
{
	char	*result;
	char	*temp;
	int		i;
	int		j;
	int		in_single_quotes;
	int		in_double_quotes;
	char	*var_name;
	char	*var_value;
	int		start;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			i++;
		}
		else if (str[i] == '"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			i++;
		}
		else if (str[i] == '$' && !in_single_quotes && str[i + 1] && (str[i
				+ 1] == '?' || (str[i + 1] >= 'A' && str[i + 1] <= 'Z')
				|| (str[i + 1] >= 'a' && str[i + 1] <= 'z') || str[i
				+ 1] == '_'))
		{
			i++;
			start = i;
			if (str[i] == '?')
				i++;
			else
			{
				while (str[i] && ((str[i] >= 'A' && str[i] <= 'Z')
						|| (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0'
							&& str[i] <= '9') || str[i] == '_'))
					i++;
			}
			var_name = ft_malloc(sizeof(char) * (i - start + 1));
			j = 0;
			while (start < i)
				var_name[j++] = str[start++];
			var_name[j] = '\0';
			var_value = get_env_value(shell, var_name);
			if (var_value)
			{
				temp = result;
				result = ft_strjoin(temp, var_value);
				free(temp);
				if (ft_strcmp(var_name, "?") == 0)
					free(var_value);
			}
			free(var_name);
		}
		else
		{
			temp = ft_malloc(sizeof(char) * (ft_strlen(result) + 2));
			j = 0;
			while (result[j])
			{
				temp[j] = result[j];
				j++;
			}
			temp[j] = str[i];
			temp[j + 1] = '\0';
			free(result);
			result = temp;
			i++;
		}
	}
	return (result);
}
