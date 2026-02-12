/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:18:33 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/19 15:54:46 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	size_t	i;

	i = 0;
	p = (char *)malloc(count * size);
	if (!p)
		return (0);
	while (i < count * size)
	{
		*(p + i) = 0;
		i++;
	}
	return ((void *)p);
}
// #include <stdio.h>

// int	main(void)
// {
// 	void	*p;
// 	char	*t;
// 	int		cnt;
// 	void	*p2;
// 	char	*t2;

// 	p = ft_calloc(5, 4);
// 	t = (char *)p;
// 	cnt = 5 * 4;
// 	for (int i = 0; i < cnt; i++)
// 	{
// 		printf("%d", *(t + i));
// 	}
// 	printf("\n");
// 	free(p);
// 	p2 = calloc(5, 4);
// 	t2 = (char *)p2;
// 	for (int i = 0; i < (int)cnt; i++)
// 	{
// 		printf("%d", *(t2 + i));
// 	}
// 	printf("\n");
// 	free(p2);
// }
