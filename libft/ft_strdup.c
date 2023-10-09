/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:13:03 by adgutier          #+#    #+#             */
/*   Updated: 2022/09/23 15:26:38 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*mem;
	int		i;
	int		tam;

	i = 0;
	tam = ft_strlen(src);
	mem = malloc(sizeof(char) * (tam + 1));
	if (!mem)
		return (0);
	while (src[i])
	{
		mem[i] = src[i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}
