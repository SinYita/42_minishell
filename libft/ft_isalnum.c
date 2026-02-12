/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:58:05 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/14 18:51:38 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
// #include<stdio.h>
// #include <string.h>
// #include<ctype.h>
// int main()
// {
// 	int range_up = 1e8;
// 	int range_down = -range_up;
// 	int (*f1)(int) = &ft_isalnum;
// 	int (*f2)(int) = &isalnum;
// 	for(int i =range_up;i < range_down;i ++)
// 	{
// 		if(f1(i) != f2(i))
// 		{
// 			printf("No !!!!!");
// 		}
// 	}
// 	printf("Yes !!!");
// }
