/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:07:07 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/20 17:22:21 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (i + j < len && needle[j] && haystack[i + j] == needle[j])
			j++;
		if (j >= ft_strlen(needle))
		{
			return ((char *)haystack + i);
		}
		i++;
	}
	return (0);
}
// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	char s[] = "abcfgfg";
// 	char t[] = "fg";
// 	printf("%s\n",strnstr(s,t,7));
// 	printf("%s\n",ft_strnstr(s,t,7));
// }
