/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:40:21 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/21 16:16:40 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (s < d && d < s + n)
	{
		while (n--)
			d[n] = s[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	b[] = "12345";
// 	size_t	n;
// 	char	d[] = "12345";

// 	n = 2;
// 	memmove(b, b + 1, n);
// 	printf("%s\n%s\n", b, b);
// 	ft_memmove(d, d + 1, n);
// 	printf("%s\n%s\n", d, d);
// }
