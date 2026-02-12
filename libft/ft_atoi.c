/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:00:16 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/21 16:24:31 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v')
		return (1);
	else if (c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	res;
	int		neg;
	int		i;

	res = 0;
	neg = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i ++;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((int)res * neg);
}
// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	char	n[40] = "+ 22323aa34";

// 	int		i1 = atoi(n);
// 	printf("%d\n",i1);
// 	int		i2 = ft_atoi(n);
// 	printf("%d\n", i1 == i2);

// }
