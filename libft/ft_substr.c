/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:43:12 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/21 17:37:49 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check(size_t len, char const *s, unsigned int start)
{
	if (ft_strlen(s) == 0)
		return (0);
	if (len > ft_strlen(s + start))
		return (ft_strlen(s + start));
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
	{
		res = (char *)malloc(1 * sizeof(char));
		if (!res)
			return (0);
		res[0] = '\0';
		return (res);
	}
	i = 0;
	len = check(len, s, start);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	while (*(s + start) && len--)
	{
		*(res + i) = s[start++];
		i++;
	}
	res[i] = '\0';
	return (res);
}

// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	char s[11] = "afadfa";

// 	char *d = ft_substr("",1,1);

// 	printf("%s",d);
// }
