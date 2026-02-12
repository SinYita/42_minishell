/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiyuandu <weiyuandu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:11:07 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/21 00:36:59 by weiyuandu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (dst == 0 && src == 0)
		return (0);
	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	char s[] = "123";
// 	char d[] = "abc";

// 	// printf("%s",(unsigned char *)ft_memcpy(d,s,3));
// 	// printf("%s",d);
// 	printf("%s",(unsigned char *)memcpy(d,s,3));
// 	printf("%s",d);
// }
