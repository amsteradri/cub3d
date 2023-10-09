/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:39:36 by adgutier          #+#    #+#             */
/*   Updated: 2022/09/23 13:21:48 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memcpy(void *dest, const void *tocpy, int sizetocpy)
{
	int	i;

	i = 0;
	if (!dest && !tocpy)
		return (0);
	while (i < sizetocpy)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)tocpy)[i];
		i++;
	}
	return (dest);
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
	

	ft_memcpy(str, str1, 3);
	ft_putstr(str);
}
*/