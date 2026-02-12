/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:46:20 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/21 17:33:32 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	size_t	len;
	size_t	i;
	size_t	j;
	size_t	cnt;

	cnt = 0;
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (i + j < len && s[i + j] != c)
			j++;
		if (j > 0)
			cnt++;
		i = i + j;
	}
	return (cnt);
}

static void	free_all(char **res, int k)
{
	while (k > 0)
		free(res[--k]);
	free(res);
}

static void	helper(int *i, int *j, char const *s, char c)
{
	*j = 0;
	while (s[*i] == c)
		(*i)++;
	while (s[*i + *j] && s[*i + *j] != c)
		(*j)++;
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;
	int		k;
	char	*temp;

	i = 0;
	res = (char **)malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!res)
		return (0);
	k = 0;
	while (i < (int)ft_strlen(s))
	{
		helper(&i, &j, s, c);
		if (j > 0)
		{
			temp = ft_substr(s, i, j);
			if (!temp)
				return (free_all(res, k), NULL);
			res[k++] = temp;
		}
		i = i + j;
	}
	res[k] = 0;
	return (res);
}

// #include <stdio.h>
// #include <string.h>s

// int	main(void)
// {
// 	char	a[] = "hello!zzzzzzzz";
// 	int		cnt;
// 	char	**output;

// 	cnt = ft_count(a, 'z');
// 	printf("%d\n", cnt);
// 	output = ft_split(a, 'z');
// 	for (int i = 0; output[i]; i++)
// 	{
// 		printf("%s\n", output[i]);
// 	}
// }
