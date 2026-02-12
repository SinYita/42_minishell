/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:29:11 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/20 16:46:13 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < dstsize && dst[i])
		i ++;
	while ((i + j + 1) < dstsize && src[j])
	{
		dst[i + j] = src[j];
		j ++;
	}
	if (i != dstsize)
	{
		dst[i + j] = '\0';
	}
	return (i + ft_strlen(src));
}

// this should be i + j + 1, or it will get negative for dstsize.
// unless implement this function seperately, which is too complicate.
// #include <string.h>
// #include<stdio.h>
// int	main(void)
// {
// 	char	s[] = "123123";
// 	char	d[] = "abc     ";
// 	char	s1[] = "123123";
// 	char	d1[] = "abc     ";

// 	printf("%s\n", d);
// 	printf("%d\n", (int)strlcat(d, s, sizeof(d)));
// 	printf("%s\n", d);
// 	printf("%d\n", (int)ft_strlcat(d1, s1, sizeof(d1)));
// }
