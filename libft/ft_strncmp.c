/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:37:30 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/20 17:35:19 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	s;
	unsigned char	t;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		s = (unsigned char)s1[i];
		t = (unsigned char)s2[i];
		if (s != t)
			return (s - t);
		i++;
	}
	return (0);
}
// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	char s[] = "ac ";
// 	char d[] = "acbde";

// 	printf("%d\n",strncmp(s,d,3));
// 	printf("%d\n",ft_strncmp(s,d,3));
// 	return (0);
// }
