/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:54:23 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/20 15:20:47 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c < 32)
		return (0);
	else if (c < 127)
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
// 	int (*f1)(int) = &ft_isprint;
// 	int (*f2)(int) = &isprint;
// 	for(int i =range_up;i < range_down;i ++)
// 	{
// 		if(f1(i) != f2(i))
// 		{
// 			printf("No !!!!!");
// 		}
// 	}
// 	printf("Yes !!!");
// }
