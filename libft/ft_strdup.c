/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:43:14 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/19 16:34:41 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	dup = (char *)malloc((len + 1));
	if (!dup)
		return (0);
	while (i < len)
	{
		*(dup + i) = *(s1 + i);
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	const char str[] = "";
// 	char *s;
// 	char *p;

// 	s = strdup(str);
// 	printf("%s",s);
// 	p = ft_strdup(str);
// 	printf("\n%s",p);
// 	return 0;
// }
