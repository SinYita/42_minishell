/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:59:37 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/14 19:07:14 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*(str + len))
		len ++;
	return (len);
}
// #include<stdio.h>
// #include <string.h>
// #include<ctype.h>
// #include<stdlib.h>
// #include <time.h>
// int main()
// {
// 	int range_up = 1e8;
// 	int range_down = -range_up;

// 	size_t (*f1)(const char *) = &ft_strlen;
// 	size_t (*f2)(const char *) = &strlen;
// 	for(int i =range_up;i < range_down;i ++)
// 	{
// 		char *r = generate_random_string(generate_random_number(666));
// 		if(f1((const char *)r) != f2((const char *)r))
// 		{
// 			printf("No !!!!!");
// 		}
// 	}
// 	printf("Yes !!!");
// }
// int generate_random_number(int max) {
//     return rand() % max;
// }
// char *generate_random_string(int length) {
//     char *random_string = (char *)malloc((length + 1) * sizeof(char));
//     if (random_string == NULL) {
//         printf("failed to generate");
//         exit(1);
//     }
//     for (int i = 0; i < length; i++) {
//         random_string[i] = '0' + generate_random_number(300);
//     }
//     random_string[length] = '\0';
//     return random_string;
// }
