/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:50:20 by adgutier          #+#    #+#             */
/*   Updated: 2022/09/27 12:59:49 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int		i;
	unsigned int		j;
	char				*substr;

	i = 0;
	j = 0;
	if (len > ft_strlen((char *)s) - start - 1)
		len = ft_strlen((char *)s) - start;
	if (start > ft_strlen((char *)s))
		return (ft_strdup(""));
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!(substr))
		return (0);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			substr[j] = s[i];
			j++;
		}
		i++;
	}
	substr[j] = 0;
	return (substr);
}

/*int main()
{
	char* str;

	str = ft_substr("Hello, 42Seoul!", 7, 2);
	printf("%s\n", str);

	return 0;
}*/