/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Weiyuan Du <wedu@42heilbronn.student.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:07:53 by Weiyuan Du        #+#    #+#             */
/*   Updated: 2025/07/18 14:18:27 by Weiyuan Du       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = (int)ft_strlen(s);
	write(fd, s, len);
}

// #include <stdio.h>

// int main()
// {
// 	char s[] = "adad";
// 	ft_putstr_fd(s,1);
// }
