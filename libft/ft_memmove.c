/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:53:40 by adgutier          #+#    #+#             */
/*   Updated: 2022/09/23 13:22:15 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, int len)
{
	char	*deesti;
	char	*source;

	deesti = (char *)dst;
	source = (char *)src;
	if (deesti > source)
	{
		while (len--)
			deesti[len] = source[len];
	}
	else if (deesti < source)
		ft_memcpy(dst, src, len);
	return (dst);
}

/*
#include <unistd.h>

void	*ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int		count;

	count = 0;
	while (str[count] != '\0')
	{
		ft_putchar(str[count]);
		count++;
	}
}


int main(void)
{
	char str[50]="bferfcwefwfw";
	char str1[50]="basic la chupa";
	

	ft_memmove(str, str1, 3);
	ft_putstr(str);
}*/