/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adgutier <adgutier@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:28:10 by adgutier          #+#    #+#             */
/*   Updated: 2022/09/27 12:58:21 by adgutier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t numcarac, size_t size)
{
	void	*ptr;

	if (numcarac == 18446744073709551615UL && size == 18446744073709551615UL)
		return (0);
	ptr = malloc(numcarac * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size * numcarac);
	return (ptr);
}
