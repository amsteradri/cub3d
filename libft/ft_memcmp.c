/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:09:37 by adgutier          #+#    #+#             */
/*   Updated: 2022/09/23 10:03:36 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*pstr1;
	unsigned char	*pstr2;

	pstr1 = (unsigned char *)str1;
	pstr2 = (unsigned char *)str2;
	i = 0;
	if (n == 0)
		return (0);
	while (*pstr1 == *pstr2 && ++i < n)
	{
		pstr1++;
		pstr2++;
	}
	return ((int)(*pstr1 - *pstr2));
}

/*
#include <unistd.h>

#include <stdio.h>

int main(void)
{
	char s1[] = "42cadet";
	char s2[] = "42cadetabc";
	printf("%d\n", ft_memcmp(s1, s2, 3));
	printf("%d\n", ft_memcmp(s1, s2, 8));

	return (0);
}
*/