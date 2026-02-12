/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:48:47 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/19 16:35:08 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		f((unsigned int)i, &s[i]);
		i++;
	}
}
// void test_toupper(unsigned int idx, char *c)
// {
// 	*c = *c - 'a' + 'A';
// }

// #include <stdio.h>
// #include <string.h>

// int main()
// {
// 	char s[] = "abcdefg";

// 	ft_striteri(s,&test_toupper);

// 	printf("%s",s);

// }
