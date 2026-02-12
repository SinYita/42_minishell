/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 21:28:27 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/19 15:40:00 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	int	temp;

	temp = c;
	if (temp >= 'a' && temp <= 'z')
	{
		temp = temp - 'a' + 'A';
	}
	return (temp);
}

// #include<ctype.h>
// #include<stdio.h>
// #include<string.h>
// int main()
// {
// 	char s[] = "31231abcafdafdfoqrueqprqrzzaq";
// 	for(int i = 0; i <(int)strlen(s);i ++)
// 	{
// 		s[i] = ft_toupper(s[i]);
// 	}
// 	printf("%s",s);
// }
