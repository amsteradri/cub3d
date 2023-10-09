/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 09:59:03 by adgutier          #+#    #+#             */
/*   Updated: 2022/09/30 09:59:26 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*haystack, const char	*needle, size_t len)
{
	unsigned int	c;

	if (!*needle)
		return ((char *)haystack);
	else if (!len)
		return (0);
	if (*needle == 0 || haystack == needle)
		return ((char *)haystack);
	c = ft_strlen((char *)needle);
	while (*haystack && c <= len--)
	{
		if (!(ft_strncmp((char *)haystack, (char *)needle, c)))
			return ((char *)haystack);
		haystack++;
	}
	return (0);
}

/*
 int main () {
    const char haystack[20] = "TutorialsPoint";
    const char needle[10] = "to";
    char *result;

    result = ft_strnstr(haystack, needle, 4);
    printf("The substring is: %s\n", result);
    return(0);
 }*/