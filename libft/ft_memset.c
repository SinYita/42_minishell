/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:24:49 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/19 16:09:13 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*temp;

	temp = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		*(temp + i) = (unsigned char)c;
		i ++;
	}
	return (b);
}
// #include <stdio.h>

// int main()
// {
// 	char c[] = "123123123";
// 	ft_memset(c,'0',5);
// 	printf("%s",c);
// }
