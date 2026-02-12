/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedu <wedu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:30:00 by wedu              #+#    #+#             */
/*   Updated: 2026/02/12 17:36:22 by wedu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*new_node;
	t_env	*current;
	char	*equals;
	int		i;

	env = NULL;
	current = NULL;
	i = 0;
	while (envp[i])
	{
		equals = ft_strchr(envp[i], '=');
		if (equals)
		{
			new_node = ft_malloc(sizeof(t_env));
			*equals = '\0';
			new_node->key = ft_strdup(envp[i]);
			new_node->value = ft_strdup(equals + 1);
			*equals = '=';
			new_node->next = NULL;
			if (!env)
			{
				env = new_node;
				current = new_node;
			}
			else
			{
				current->next = new_node;
				current = new_node;
			}
		}
		i++;
	}
	return (env);
}

char	*get_env_value(t_shell *shell, char *key)
{
	t_env	*current;
	char	*status;

	if (!key)
		return (NULL);
	if (ft_strcmp(key, "?") == 0)
	{
		status = ft_itoa(shell->exit_status);
		return (status);
	}
	current = shell->env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	set_env_value(t_shell *shell, char *key, char *value)
{
	t_env	*current;
	t_env	*new_node;

	current = shell->env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = value ? ft_strdup(value) : NULL;
			return ;
		}
		current = current->next;
	}
	new_node = ft_malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	new_node->value = value ? ft_strdup(value) : NULL;
	new_node->next = shell->env;
	shell->env = new_node;
}

void	unset_env_value(t_shell *shell, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = shell->env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				shell->env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

char	**env_to_array(t_shell *shell)
{
	t_env	*current;
	char	**envp;
	char	*temp;
	int		count;
	int		i;

	count = 0;
	current = shell->env;
	while (current)
	{
		if (current->value)
			count++;
		current = current->next;
	}
	envp = ft_malloc(sizeof(char *) * (count + 1));
	i = 0;
	current = shell->env;
	while (current)
	{
		if (current->value)
		{
			temp = ft_strjoin(current->key, "=");
			envp[i] = ft_strjoin(temp, current->value);
			free(temp);
			i++;
		}
		current = current->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	free_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}
