/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:58:42 by adgutier          #+#    #+#             */
/*   Updated: 2022/09/26 12:51:30 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str && *str != (unsigned char) c)
		str++;
	if ((unsigned char) c == *str)
		return (str);
	return (0);
}

/*
#include <stdio.h>

int main() 
{
   const char str[] = "tripouille";
   char *ret;

   ret = ft_strchr(str, 't' + 256);

   printf(" %s, |%c| \n", ret, 't' + 256);
   
   return(0);
}*/