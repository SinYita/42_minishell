/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:03:34 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/14 18:52:42 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
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
// 	int (*f1)(int) = &ft_isascii;
// 	int (*f2)(int) = &isascii;
// 	for(int i =range_up;i < range_down;i ++)
// 	{
// 		if(f1(i) != f2(i))
// 		{
// 			printf("No !!!!!");
// 		}
// 	}
// 	printf("Yes !!!");
// }
