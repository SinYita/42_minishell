/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:23:06 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/20 16:46:29 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_s;

	i = 0;
	len_s = ft_strlen(src);
	while ((i + 1) < dstsize && i < len_s)
	{
		dst[i] = src[i];
		i ++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (len_s);
}
// #include<stdio.h>
// #include<string.h>

// int main()
// {
// 	char d[] = "123              ";
// 	char s[] = "1";
// 	char d2[] = "123              ";
// 	char s2[] = "1";
// 	printf("%d\n",(int)strlcpy(d,s,sizeof(d)));
// 	printf("%s\n",d);
// 	printf("%d\n",(int)ft_strlcpy(d2,s2,sizeof(d2)));
// 	printf("%s\n",d2);
// }
