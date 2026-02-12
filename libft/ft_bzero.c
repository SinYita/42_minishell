/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:49:56 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/19 15:53:07 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	char	*temp;

	temp = (char *) s;
	while (n --)
	{
		*(temp ++) = 0;
	}
}

// #include<stdio.h>
// #include<string.h>

// int main()
// {
// 	char c[] = "tstsststfdaf";
// 	printf("%d-----",(int)strlen(c));
// 	ft_bzero(c,2);
// 	printf("%d-----",(int)strlen(c));
// 	for(int i = 0 ;i < (int)strlen(c);i ++)
// 	{
// 		printf("%c ",c[i]);
// 	}
// }
