/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:24:27 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/20 17:07:44 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (*(s + i) == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	const char	c[] = "fdafdfaf";

// 	printf("%s\n",strchr(c,'\0'));
// 	printf("%s\n",ft_strchr(c,'\0'));
// 	return (0);
// }
