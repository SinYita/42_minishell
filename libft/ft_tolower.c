/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:35:40 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/12 23:44:02 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	int	temp;

	temp = c;
	if (temp >= 'A' && temp <= 'Z')
	{
		temp = temp - 'A' + 'a';
	}
	return (temp);
}
// #include<ctype.h>
// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	char s[] = "31231ASDASDASDASDq";
// 	for(int i = 0; i <(int)strlen(s);i ++)
// 	{
// 		s[i] = ft_tolower(s[i]);
// 	}
// 	printf("%s",s);
// }
