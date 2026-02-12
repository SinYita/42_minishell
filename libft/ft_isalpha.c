/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:45:22 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/14 18:49:48 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
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
// 	int (*f1)(int) = &ft_isalpha;
// 	int (*f2)(int) = &isalpha;
// 	for(int i =range_up;i < range_down;i ++)
// 	{
// 		if(f1(i) != f2(i))
// 		{
// 			printf("No !!!!!");
// 		}
// 	}
// 	printf("Yes !!!");
// }
