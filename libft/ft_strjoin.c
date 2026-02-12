/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:50:31 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/19 16:35:27 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_1;
	size_t	len_2;
	size_t	len;
	char	*res;

	len = 0;
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	res = (char *)malloc((len_1 + len_2 + 1));
	if (!res)
		return (0);
	while (len < len_1)
	{
		res[len] = s1[len];
		len++;
	}
	while (len < len_1 + len_2)
	{
		res[len] = s2[len - len_1];
		len++;
	}
	res[len_1 + len_2] = '\0';
	return (res);
}
// #include<stdio.h>
// #include<string.h>

// int main()
// {
// 	char a[] = "abcde";
// 	char b[] = "12312";

// 	char *s;
// 	s = ft_strjoin(a,b);
// 	printf("%s",s);
// }
