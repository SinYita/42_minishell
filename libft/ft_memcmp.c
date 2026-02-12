/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:39:10 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/14 18:19:56 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_temp;
	unsigned char	*s2_temp;

	i = 0;
	s1_temp = (unsigned char *)s1;
	s2_temp = (unsigned char *)s2;
	while (i < n)
	{
		if (s1_temp[i] != s2_temp[i])
		{
			return ((int)s1_temp[i] - (int)s2_temp[i]);
		}
		i++;
	}
	return (0);
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char s[] = "fadfdf\0ff\tff\0   dfafd\v\v\t";
// 	char d[] = "fadfdf\0fff\0ff\0   dfafd\v\v\t";
// 	printf("%d\n",memcmp(s,d,13));
// 	printf("%d\n",ft_memcmp(s,d,13));
// }
