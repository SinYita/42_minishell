/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:20:07 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/14 18:29:35 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp;
	size_t			i;

	i = 0;
	temp = (unsigned char *)s;
	while (i < n)
	{
		if (temp[i] == (unsigned char)c)
		{
			return ((void *)temp + i);
		}
		i++;
	}
	return (0);
}
// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	s[] = "adfadfad\0\0\0fdafds\t";

// 	printf("%d\n", (unsigned char *)memchr(s, 'a',
			// 13) == (unsigned char *)ft_memchr(s, 'a', 13));
// }
