/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:34:37 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/18 13:47:26 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*res;

	len = ft_strlen(s);
	i = 0;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	while (i < len)
	{
		res[i] = f((unsigned int)i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
// char test_toupper(unsigned int idx, char c)
// {
// 	char b;
// 	b = c - 'a' + 'A';
// 	return (b);
// }

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	char s[] = "abcdefg";

// 	char *res;

// 	res = ft_strmapi(s,&test_toupper);

// 	printf("%s",res);

// }
