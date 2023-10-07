/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 10:04:10 by adgutier          #+#    #+#             */
/*   Updated: 2022/09/23 15:56:07 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
int main() 
{
    char    s1[] = "test\200";
    char    s2[] = "test\0";
    unsigned int  n;

    n = 6;
    printf("Result: %d", ft_strncmp(s1, s2, n));
	printf("Result: %d", strncmp(s1, s2, n));
    return (0);
}*/
