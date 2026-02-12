/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:57:44 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/21 16:28:11 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in(char const *set, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(set);
	while (i < len)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	len;
	int	start;
	int	end;

	if (!set)
		return ((char *)s1);
	if (!s1)
		return (0);
	len = ft_strlen(s1);
	if (len == 0)
		return (ft_strdup(""));
	start = 0;
	while (start < len && ft_in(set, s1[start]))
		start++;
	if (start == len)
		return (ft_strdup(""));
	end = len - 1;
	while (end >= 0 && ft_in(set, s1[end]))
		end--;
	return (ft_substr(s1, (unsigned int)start, end - start + 1));
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char s1[] = "";
// 	char	set[] = "ab";
// 	char	*res;

// 	res = ft_strtrim(s1, "");
// 	printf("%s", res);
// }
