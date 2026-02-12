/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:46:20 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/21 14:24:29 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_icount(long n)
{
	int	cnt;

	cnt = 0;
	if (n <= 0)
	{
		cnt++;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

void	dfs(char *res, long n, int i)
{
	if (n < 10)
	{
		*(res + i) = (char)(n + '0');
		return ;
	}
	else
	{
		dfs(res, n / 10, i - 1);
		*(res + i) = (char)(n % 10 + '0');
	}
}

char	*ft_itoa(int n)
{
	int		num;
	char	*res;
	long	long_n;

	long_n = n;
	num = ft_icount(long_n);
	res = (char *)malloc((num + 1) * sizeof(char));
	if (!res)
		return (0);
	if (long_n < 0)
	{
		res[0] = '-';
		dfs(res, -long_n, num - 1);
	}
	else
		dfs(res, long_n, num - 1);
	res[num] = '\0';
	return (res);
}
// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	int		n;
// 	char	*res;

// 	n = 2147483647;
// 	res = ft_itoa(n);
// 	printf("%s", res);
// }
