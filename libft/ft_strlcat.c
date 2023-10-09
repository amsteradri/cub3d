/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:27:02 by adgutier          #+#    #+#             */
/*   Updated: 2022/09/30 13:23:29 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	londest;
	unsigned int	lonsrc;

	lonsrc = ft_strlen(src);
	if (!dest && !size)
		return (lonsrc);
	i = ft_strlen(dest);
	j = 0;
	londest = ft_strlen(dest);
	if (size <= 0)
		return (lonsrc);
	if (size > 0 && size - 1 > londest)
	{
		while (src[j] && i < size - 1)
			dest[i++] = src[j++];
		dest[i] = '\0';
	}
	if (size < londest)
		return (lonsrc + size);
	else
		return (londest + lonsrc);
}
/*
int main(void)
{
	char	*dest = "rrrrrrrrrrrrrrr";

	printf("%zu\n", ft_strlcat(dest, "lorem ipsum dolor sit amet", 15));
	write(1, "\n", 1);
	write(1, dest, 15);
	return (0);
}*/
